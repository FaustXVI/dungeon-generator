open DungeonGenerator;

type state = {generatedMap: string};

type action =
  | Generate;

let initialState = {generatedMap: generateEncounter() };

let reducer = (_, s, _) => {
    s
};

[@react.component]
let make = (~randomInt=Random.int) => {
  let (state, _) =
    React.useReducer(reducer(randomInt), initialState);
  <div>
       { <p> {React.string(state.generatedMap)} </p>
       |> TestId.testId("dungeon") }
  </div>;
};
