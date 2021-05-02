open DungeonGenerator;

type state = {generatedAdventure: encounter };

type action =
  | Generate;

let initialState = {generatedAdventure: generateEncounter() };

let reducer = (_, s, _) => {
    s
};

[@react.component]
let make = (~randomInt=Random.int) => {
  let (state, _) =
    React.useReducer(reducer(randomInt), initialState);
  <div>
       { <p> {React.string(string_of_int(state.generatedAdventure.creaturesAtGroupLevel)
                 ++ " creatures at Group Level")} </p>
       |> TestId.testId("dungeon") }
  </div>;
};
