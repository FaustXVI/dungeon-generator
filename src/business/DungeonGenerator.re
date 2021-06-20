open Belt.List;
open Belt;

type level =
  | GroupLevelMinus1
  | GroupLevel;

type perilType =
  | Creature
  | SimpleDanger
  | ComplexDanger;

type peril =
  | Creature(level)
  | SimpleDanger(level)
  | ComplexDanger(level);

let aPeril = (perilType: perilType, level: level): peril => {
  switch (perilType) {
  | Creature => Creature(level)
  | SimpleDanger => SimpleDanger(level)
  | ComplexDanger => ComplexDanger(level)
  };
};

let perilTypeOf = (peril: peril): perilType => {
  switch (peril) {
  | Creature(_) => Creature
  | SimpleDanger(_) => SimpleDanger
  | ComplexDanger(_) => ComplexDanger
  };
};

let levelOf = (peril: peril): level => {
  switch (peril) {
  | Creature(lvl)
  | SimpleDanger(lvl)
  | ComplexDanger(lvl) => lvl
  };
};

module PerilComparator =
  Id.MakeComparable({
    type t = peril;
    let cmp = (a: peril, b: peril) =>
      switch (a, b) {
      | (Creature(lvla), Creature(lvlb))
      | (SimpleDanger(lvla), SimpleDanger(lvlb))
      | (ComplexDanger(lvla), ComplexDanger(lvlb)) => compare(lvla, lvlb)
      | (Creature(_), _) => (-1)
      | (SimpleDanger(_), Creature(_)) => 1
      | (SimpleDanger(_), ComplexDanger(_)) => (-1)
      | (ComplexDanger(_), _) => 1
      };
  });

type encounter = {perils: Map.t(peril, int, PerilComparator.identity)};

let newEncounter: encounter = {
  perils: Map.make(~id=(module PerilComparator)),
};

let containing = (encounter: encounter, peril: peril, number: int): encounter => {
  {perils: encounter.perils->Map.set(peril, number)};
};

let reduce =
    (encounter: encounter, accumulator: 'a, f: ('a, peril, int) => 'a): 'a => {
  encounter.perils->Map.reduce(accumulator, f);
};

let perilLevel = (peril: peril) =>
  switch (peril) {
  | SimpleDanger(level) => level
  | ComplexDanger(level) => level
  | Creature(level) => level
  };

type chooser = list(peril) => option(peril);

let pickRandom = (perils: list(peril)) => head(shuffle(perils));

let experiencePointForPeril = (peril: peril) => {
  switch (peril) {
  | SimpleDanger(GroupLevelMinus1) => 6
  | SimpleDanger(GroupLevel) => 8
  | Creature(_)
  | ComplexDanger(_) => 40
  };
};
let experiencePoints = (~encounter: encounter) => {
  Map.reduce(encounter.perils, 0, (acc, p, n) =>
    acc + n * experiencePointForPeril(p)
  );
};

let increment = (value: option(int)): option(int) =>
  switch (value) {
  | None => Some(1)
  | Some(n) => Some(n + 1)
  };

let upToGoal = (perils: list(peril), goal: int): list(peril) => {
  keep(perils, p => experiencePointForPeril(p) <= goal);
};

exception TODO(string);

let todo = (message: string) => raise(TODO(message));

let rec addPeril =
        (
          chooser: chooser,
          perils: list(peril),
          building: Map.t(peril, int, PerilComparator.identity),
          goal: int,
        )
        : Map.t(peril, int, PerilComparator.identity) =>
  if (goal > 0) {
    switch (chooser(perils->upToGoal(goal))) {
    | None => building->Map.update(SimpleDanger(GroupLevelMinus1), increment)
    | Some(peril) =>
      addPeril(
        chooser,
        perils,
        building->Map.update(peril, increment),
        goal - experiencePointForPeril(peril),
      )
    };
  } else {
    building;
  };

let generateEncounter = (~chooser: chooser, ~perils: array(peril)): encounter => {
  let perils =
    addPeril(
      chooser,
      fromArray(perils),
      Map.make(~id=(module PerilComparator)),
      80,
    );
  {perils: perils};
};

let possiblePerils = [|
  aPeril(Creature, GroupLevel),
  aPeril(SimpleDanger, GroupLevel),
  aPeril(ComplexDanger, GroupLevel),
  aPeril(SimpleDanger, GroupLevelMinus1),
  aPeril(Creature, GroupLevelMinus1),
  aPeril(ComplexDanger, GroupLevelMinus1),
|];
