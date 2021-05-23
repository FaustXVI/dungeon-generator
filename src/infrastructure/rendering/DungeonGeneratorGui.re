open Belt;
open DungeonGenerator;

type state = {generatedAdventure: encounter};

type action =
  | Generate;

let initialState = {
  generatedAdventure:
    generateEncounter(
      ~perils=[|Creature, SimpleDanger, ComplexDanger|],
      ~chooser=pickRandom,
    ),
};

let reducer = (_, s, _) => {
  s;
};

[@react.component]
let make = (~randomInt=Random.int) => {
  let (state, _) = React.useReducer(reducer(randomInt), initialState);
  <div>
    {<p>
       {let strings =
          DungeonGenerator.reduce(state.generatedAdventure, [], (acc, p, n) =>
            acc->List.add(
              string_of_int(n) ++ " " ++ StringRenderer.render(p),
            )
          );
        React.string(Js.Array.joinWith(", ", List.toArray(strings)))}
     </p>
     ->TestId.testId(~testId="dungeon")}
  </div>;
};
