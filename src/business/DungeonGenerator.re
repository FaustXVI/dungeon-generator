open Belt.List;
open Belt;
open Peril;
open Encounter;

type chooser = list(peril) => option(peril);

let pickRandom = (perils: list(peril)) => head(shuffle(perils));

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
    | None =>
      building->Map.update(aPeril(SimpleDanger, GroupLevelMinus1), increment)
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
