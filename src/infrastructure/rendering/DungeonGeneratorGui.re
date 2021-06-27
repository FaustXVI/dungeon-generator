open Belt;
open DungeonGenerator;
open Encounter;

type state = option(encounter);

type action =
  | Generate;

let generateNewEncounter = () =>
  Some(
    generateEncounter(
      ~perils=possiblePerils,
      ~chooser=pickRandom,
      ~budget=80,
    ),
  );

let initialState = None;

let reducer = (_: state, action: action): state => {
  switch (action) {
  | Generate => generateNewEncounter()
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  <div>
    <button onClick={_event => dispatch(Generate)}>
      {React.string("Generate")}
    </button>
    {switch (state) {
     | None => React.string("")
     | Some(encounter) =>
       <ul>
         {StringRenderer.renderEncounter(encounter)
          ->Array.map(s => <li key=s> {React.string(s)} </li>)
          ->React.array}
       </ul>
       ->TestId.testId(~testId="dungeon")
     }}
  </div>;
};
