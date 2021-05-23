open Belt.List;
open Belt;

type peril =
  | Creature
  | SimpleDanger
  | ComplexDanger;

module PerilComparator =
  Id.MakeComparable({
    type t = peril;
    let cmp = (a: peril, b: peril) => compare(a, b);
  });

type encounter = {perils: list((peril, int))};

type chooser = list(peril) => option(peril);

let pickRandom = (perils: list(peril)) => head(shuffle(perils));

let experiencePointForPeril = (peril: peril) => {
  switch (peril) {
  | SimpleDanger => 8
  | Creature
  | ComplexDanger => 40
  };
};
let experiencePoints = (~encounter: encounter) => {
  map(encounter.perils, ((p, n)) => n * experiencePointForPeril(p))
  ->reduce(0, (a, b) => a + b);
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

let generateEncounter =
    (~perils: array(peril), ~chooser: chooser=pickRandom, ()): encounter => {
  let perils =
    addPeril(
      chooser,
      fromArray(perils),
      Map.make(~id=(module PerilComparator)),
      80,
    );
  {perils: Map.toList(perils)};
};
