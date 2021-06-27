open Belt;
open DungeonGenerator;
open Encounter;

type state = option(encounter);

type action =
  | Generate(int);

let generateNewEncounter = budget =>
  Some(
    generateEncounter(~perils=possiblePerils, ~chooser=pickRandom, ~budget),
  );

let initialState = None;

let reducer = (_: state, action: action): state => {
  switch (action) {
  | Generate(budget) => generateNewEncounter(budget)
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  <div>
    <button onClick={_event => dispatch(Generate(80))}>
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
