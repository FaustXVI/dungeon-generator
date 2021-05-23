open DungeonGenerator;

let render = (peril: peril): string => {
  switch (peril) {
  | Creature => "Creature"
  | SimpleDanger => "Simple Danger"
  | ComplexDanger => "Complex Danger"
  };
};
