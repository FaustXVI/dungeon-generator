open Belt;
open Peril;

type difficulty = Weak | Moderate | Custom;

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

let experiencePoints = (~encounter: encounter) => {
  Map.reduce(encounter.perils, 0, (acc, p, n) =>
    acc + n * experiencePointForPeril(p)
  );
};

let experiencePointsForPredefinedDifficulty = (difficulty: difficulty): option(int) => {
    switch(difficulty) {
    | Weak => Some(60)
    | Moderate => Some(80)
    | Custom => None
    }
};

let difficultyToString = (difficulty: difficulty): string => {
    switch(difficulty) {
    | Weak => "Weak"
    | Moderate => "Moderate"
    | Custom => "Custom"
    }
}

// switch to an Option output type
let difficultyFromString = (string: string): difficulty => {
    switch(string) {
    | "Weak" => Weak
    | "Moderate" => Moderate
    | _ => Custom
    }
}