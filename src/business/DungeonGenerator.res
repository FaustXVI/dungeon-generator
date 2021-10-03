open Belt.List
open Belt
open Peril
open Encounter

type chooser = list<peril> => option<peril>

let pickRandom = (perils: list<peril>) => head(shuffle(perils))

let increment = (value: option<int>): option<int> =>
  switch value {
  | None => Some(1)
  | Some(n) => Some(n + 1)
  }

let upToGoal = (perils: list<peril>, goal: int): list<peril> => {
  keep(perils, p => experiencePointForPeril(p) <= goal)
}

let rec addPeril = (
  chooser: chooser,
  perils: list<peril>,
  building: Map.t<peril, int, PerilComparator.identity>,
  goal: int,
): Map.t<peril, int, PerilComparator.identity> =>
  if goal > 0 {
    switch chooser(perils->upToGoal(goal)) {
    | None => building->Map.update(smallestPeril(perils), increment)
    | Some(peril) =>
      addPeril(
        chooser,
        perils,
        building->Map.update(peril, increment),
        goal - experiencePointForPeril(peril),
      )
    }
  } else {
    building
  }

let generateEncounter = (~chooser: chooser, ~perils: array<peril>, ~budget: int): encounter => {
  let perils = addPeril(chooser, fromArray(perils), Map.make(~id=module(PerilComparator)), budget)
  {perils: perils}
}

let createPerils = (selectedLevels: array<level>): array<peril> =>
  toArray(
    flatten(
      map(fromArray(perilTypes), perilType => {
        map(fromArray(selectedLevels), level => {aPeril(perilType, level)})
      }),
    ),
  )

let possiblePerils = createPerils(levels)
