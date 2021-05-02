type dungeon =
  | Square
  | Rectangle;

let dungeonToString = (~dungeon: dungeon): string =>
  switch (dungeon) {
  | Square => "Square"
  | Rectangle => "Rectangle"
  };

let generateDungeon = randomInt =>
  if (randomInt(2) == 0) {
    Square;
  } else {
    Rectangle;
  };
