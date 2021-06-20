open Peril;

let renderPerilType = (perilType: perilType): string => {
  switch (perilType) {
  | Creature => "Creature"
  | SimpleDanger => "Simple Danger"
  | ComplexDanger => "Complex Danger"
  };
};

let renderLevel = (level: level): string => {
  switch (level) {
  | GroupLevelMinus3 => "-3"
  | GroupLevelMinus2 => "-2"
  | GroupLevelMinus1 => "-1"
  | GroupLevel => "at group level"
  | GroupLevelPlus1 => "+1"
  | GroupLevelPlus2 => "+2"
  };
};

let render = (peril: peril): string => {
  renderPerilType(perilTypeOf(peril)) ++ " " ++ renderLevel(levelOf(peril));
};
