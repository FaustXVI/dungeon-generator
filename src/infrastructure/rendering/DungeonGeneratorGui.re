open Belt;
open DungeonGenerator;
open Encounter;

type state = {generatedAdventure: encounter};

type action =
  | Generate;

let initialState = {
  generatedAdventure:
    generateEncounter(
      ~perils=possiblePerils,
      ~chooser=pickRandom,
      ~budget=80,
    ),
};

let reducer = (_, s, _) => {
  s;
};

[@react.component]
let make = (~randomInt=Random.int) => {
  let (state, _) = React.useReducer(reducer(randomInt), initialState);
  <div>
    {<ul>
       {StringRenderer.renderEncounter(state.generatedAdventure)
        ->Array.map(s => <li key=s> {React.string(s)} </li>)
        ->React.array}
     </ul>
     ->TestId.testId(~testId="dungeon")}
  </div>;
};
