open DungeonGenerator;

let render = (peril: peril): string => {
  switch (peril) {
  | Creature(_) => "Creature"
  | SimpleDanger(_) => "Simple Danger"
  | ComplexDanger(_) => "Complex Danger"
  };
};
