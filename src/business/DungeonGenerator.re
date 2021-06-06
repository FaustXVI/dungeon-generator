open Belt.List;
open Belt;

type level =
  | GroupLevelMinus1
  | GroupLevel;

type peril_type =
  | Creature2
  | SimpleDanger2
  | ComplexDanger2;

type peril2 = { peril_type: peril_type, level: level };

type peril =
  | Creature(level)
  | SimpleDanger(level)
  | ComplexDanger(level);

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

module PerilComparator2 =
  Id.MakeComparable({
    type t = peril2;
    let cmp = (a: peril2, b: peril2) =>
      switch (a, b) {
          | ({ peril_type: Creature2, level: level_a }, { peril_type: Creature2, level: level_b })
          | ({ peril_type: SimpleDanger2, level: level_a }, { peril_type: SimpleDanger2, level: level_b })
          | ({ peril_type: ComplexDanger2, level: level_a }, { peril_type: ComplexDanger2, level:  level_b }) => compare (level_a, level_b)
          | ({ peril_type: Creature2, _ }, _ ) => (-1)
          | ({ peril_type: SimpleDanger2, _ }, { peril_type: Creature2, _ }) => 1
          | ({ peril_type: SimpleDanger2, _ }, { peril_type: ComplexDanger2, _ }) => (-1)
          | ({ peril_type: ComplexDanger2, _ },_ ) => 1
      };
  });
type encounter = {perils: Map.t(peril, int, PerilComparator.identity)};
type encounter2= {perils2: Map.t(peril2, int, PerilComparator2.identity)};


let newEncounter: encounter = {
  perils: Map.make(~id=(module PerilComparator)),
};

let newEncounter2: encounter2 = {
  perils2: Map.make(~id=(module PerilComparator2)),
};
let containing = (encounter: encounter, peril: peril, number: int): encounter => {
  {perils: encounter.perils->Map.set(peril, number) };
};

let containing2 = (encounter2: encounter2, peril2: peril2, number: int): encounter2 => {
  {perils2: encounter2.perils2->Map.set(peril2, number) };
};
let reduce =
    (encounter: encounter, accumulator: 'a, f: ('a, peril, int) => 'a): 'a => {
  encounter.perils->Map.reduce(accumulator, f);
};

let reduce2 =
    (encounter2: encounter2, accumulator: 'a, f: ('a, peril2, int) => 'a): 'a => {
  encounter2.perils2->Map.reduce(accumulator, f);
};
let perilLevel = (peril: peril) =>
  switch (peril) {
  | SimpleDanger(level) => level
  | ComplexDanger(level) => level
  | Creature(level) => level
  };

type chooser = list(peril) => option(peril);
type chooser2 = list(peril2) => option(peril2);

let pickRandom = (perils: list(peril)) => head(shuffle(perils));
let pickRandom2 = (perils2: list(peril2)) => head(shuffle(perils2));

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

let experiencePointForPeril2 = (peril2: peril2) => {
  switch (peril2) {
  | { peril_type: SimpleDanger2, level: GroupLevelMinus1 } => 6
  | { peril_type: SimpleDanger2, level: GroupLevel } => 8
  | { peril_type: Creature2, _ }
  | { peril_type: ComplexDanger2, _ } => 40
  };
};
let experiencePoints2 = (~encounter2: encounter2) => {
  Map.reduce(encounter2.perils2, 0, (acc, p, n) =>
    acc + n * experiencePointForPeril2(p)
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

let upToGoal2 = (perils2: list(peril2), goal: int): list(peril2) => {
  keep(perils2, p => experiencePointForPeril2(p) <= goal);
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

let rec addPeril2 =
        (
          chooser2: chooser2,
          perils2: list(peril2),
          building: Map.t(peril2, int, PerilComparator2.identity),
          goal: int,
        )
        : Map.t(peril2, int, PerilComparator2.identity) =>
  if (goal > 0) {
    switch (chooser2(perils2->upToGoal2(goal))) {
    | None => building->Map.update( { peril_type: SimpleDanger2, level: GroupLevelMinus1 }, increment)
    | Some(peril2) =>
      addPeril2(
        chooser2,
        perils2,
        building->Map.update(peril2, increment),
        goal - experiencePointForPeril2(peril2),
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
  {perils: perils };
};

let generateEncounter2 = (~chooser2: chooser2, ~perils2: array(peril2)): encounter2 => {
  let perils2 =
    addPeril2(
      chooser2,
      fromArray(perils2),
      Map.make(~id=(module PerilComparator2)),
      80,
    );
  {perils2: perils2 };
};

let possiblePerils = [|
  Creature(GroupLevel),
  SimpleDanger(GroupLevel),
  ComplexDanger(GroupLevel),
  SimpleDanger(GroupLevelMinus1),
  Creature(GroupLevelMinus1),
  ComplexDanger(GroupLevelMinus1),
|];
