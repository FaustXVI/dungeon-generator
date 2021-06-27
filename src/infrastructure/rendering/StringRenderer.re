open Peril;
open Encounter;
open Belt;

let renderPerilType = (perilType: perilType): string => {
  switch (perilType) {
  | Creature => "Creature"
  | SimpleDanger => "Simple Danger"
  | ComplexDanger => "Complex Danger"
  };
};

let renderLevel = (level: level): string => {
  switch (level) {
  | GroupLevelMinus4 => "-4"
  | GroupLevelMinus3 => "-3"
  | GroupLevelMinus2 => "-2"
  | GroupLevelMinus1 => "-1"
  | GroupLevel => "at group level"
  | GroupLevelPlus1 => "+1"
  | GroupLevelPlus2 => "+2"
  | GroupLevelPlus3 => "+3"
  | GroupLevelPlus4 => "+4"
  };
};

let render = (peril: peril): string => {
  renderPerilType(perilTypeOf(peril)) ++ " " ++ renderLevel(levelOf(peril));
};

let renderEncounter = (encounter: encounter): array(string) => {
  Encounter.reduce(encounter, [], (acc, p, n) =>
    acc->List.add(string_of_int(n) ++ " " ++ render(p))
  )
  ->List.toArray;
};
