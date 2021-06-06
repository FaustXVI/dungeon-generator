open DungeonGenerator;

let render = (peril: peril): string => {
  switch (peril) {
  | Creature(GroupLevel) => "Creature at group level"
  | SimpleDanger(GroupLevel) => "Simple Danger at group level"
  | ComplexDanger(GroupLevel) => "Complex Danger at group level"
  | Creature(GroupLevelMinus1) => "Creature -1"
  | SimpleDanger(GroupLevelMinus1) => "Simple Danger -1"
  | ComplexDanger(GroupLevelMinus1) => "Complex Danger -1"
  };
};
