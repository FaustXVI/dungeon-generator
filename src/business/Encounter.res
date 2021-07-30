open Belt
open Peril

type difficulty =
  | Trivial
  | Weak
  | Moderate
  | Serious
  | Extreme
  | Custom

let difficulties = [Trivial, Weak, Moderate, Serious, Extreme, Custom]

type encounter = {perils: Map.t<peril, int, PerilComparator.identity>}

let newEncounter: encounter = {
  perils: Map.make(~id=module(PerilComparator)),
}

let containing = (encounter: encounter, peril: peril, number: int): encounter => {
  {perils: encounter.perils->Map.set(peril, number)}
}

let reduce = (encounter: encounter, accumulator: 'a, f: ('a, peril, int) => 'a): 'a => {
  encounter.perils->Map.reduce(accumulator, f)
}

let experiencePoints = (~encounter: encounter) => {
  Map.reduce(encounter.perils, 0, (acc, p, n) => acc + n * experiencePointForPeril(p))
}

let experiencePointsForPredefinedDifficulty = (difficulty: difficulty): option<int> => {
  switch difficulty {
  | Trivial => Some(40)
  | Weak => Some(60)
  | Moderate => Some(80)
  | Serious => Some(120)
  | Extreme => Some(160)
  | Custom => None
  }
}

let difficultyToString = (difficulty: difficulty): string => {
  switch difficulty {
  | Trivial => "Trivial"
  | Weak => "Weak"
  | Moderate => "Moderate"
  | Serious => "Serious"
  | Extreme => "Extreme"
  | Custom => "Custom"
  }
}

let difficultyFromString = (string: string): difficulty => {
  switch string {
  | "Trivial" => Trivial
  | "Weak" => Weak
  | "Moderate" => Moderate
  | "Serious" => Serious
  | "Extreme" => Extreme
  | _ => Custom
  }
}