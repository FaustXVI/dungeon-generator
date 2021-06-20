open Belt;
open DungeonGenerator;
open Encounter;

type state = {generatedAdventure: encounter};

type action =
  | Generate;

let initialState = {
  generatedAdventure:
    generateEncounter(~perils=possiblePerils, ~chooser=pickRandom),
};

let reducer = (_, s, _) => {
  s;
};

[@react.component]
let make = (~randomInt=Random.int) => {
  let (state, _) = React.useReducer(reducer(randomInt), initialState);
  <div>
    {<ul>
       {let strings =
          Encounter.reduce(state.generatedAdventure, [], (acc, p, n) =>
            acc->List.add(
              string_of_int(n) ++ " " ++ StringRenderer.render(p),
            )
          )
          ->List.toArray;
        strings
        ->Array.map(s => <li key=s> {React.string(s)} </li>)
        ->React.array}
     </ul>
     ->TestId.testId(~testId="dungeon")}
  </div>;
};
