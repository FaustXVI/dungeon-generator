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
  | GroupLevel => "at group level"
  | GroupLevelMinus1 => "-1"
  };
};

let render = (peril: peril): string => {
  renderPerilType(perilTypeOf(peril)) ++ " " ++ renderLevel(levelOf(peril));
};
