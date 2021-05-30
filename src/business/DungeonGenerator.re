open Belt.List;
open Belt;

type level =
  | GroupLevel
  | GroupLevelMinus1;

type peril =
  | Creature(level)
  | SimpleDanger(level)
  | ComplexDanger(level);

module PerilComparator =
  Id.MakeComparable({
    type t = peril;
    let cmp = (a: peril, b: peril) =>
      switch (a, b) {
      | (Creature(_), Creature(_))
      | (SimpleDanger(_), SimpleDanger(_))
      | (ComplexDanger(_), ComplexDanger(_)) => 0
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
  | SimpleDanger(_) => 8
  | Creature(_)
  | ComplexDanger(_) => 40
  };
};
let experiencePoints = (~encounter: encounter) => {
  Map.reduce(encounter.perils, 0, (acc, p, n) =>
    acc + n * experiencePointForPeril(p)
  );
};

exception Peril_Not_Found;

let increment = (value: option(int)): option(int) =>
  switch (value) {
  | None => Some(1)
  | Some(n) => Some(n + 1)
  };

let upToGoal = (perils: list(peril), goal: int): list(peril) => {
  keep(perils, p => experiencePointForPeril(p) <= goal);
};

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
    | None => raise(Peril_Not_Found)
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
  Creature(GroupLevel),
  SimpleDanger(GroupLevel),
  ComplexDanger(GroupLevel),
  Creature(GroupLevelMinus1),
  SimpleDanger(GroupLevelMinus1),
  ComplexDanger(GroupLevelMinus1),
|];
