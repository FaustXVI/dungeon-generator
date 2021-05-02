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

type state = {generatedMap: option(dungeon)};

type action =
  | Generate;

let initialState = {generatedMap: None};

let reducer = (randomInt, _, action) => {
  switch (action) {
  | Generate => {generatedMap: Some(generateDungeon(randomInt))}
  };
};

[@react.component]
let make = (~randomInt=Random.int) => {
  let (state, dispatch) =
    React.useReducer(reducer(randomInt), initialState);
  <div>
    <div>
      {<button onClick={_event => dispatch(Generate)}>
         {React.string("Refresh")}
       </button>
       |> TestId.testId("refresh_button")}
    </div>
    {switch (state) {
     | {generatedMap: Some(dungeon)} =>
       <p> {React.string(dungeonToString(~dungeon))} </p>
       |> TestId.testId("dungeon")
     | _ => React.null
     }}
  </div>;
};
