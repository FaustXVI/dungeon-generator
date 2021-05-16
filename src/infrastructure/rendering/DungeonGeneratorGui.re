open DungeonGenerator;

type state = {generatedAdventure: encounter};

type action =
  | Generate;

let initialState = {
  generatedAdventure:
    generateEncounter(~perils=[|Creature, SimpleDanger, ComplexDanger|], ()),
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
          Belt.List.map(state.generatedAdventure.perils, p => {
            switch (p) {
            | Creature => "Creature"
            | SimpleDanger => "Simple Danger"
            | ComplexDanger => "Complex Danger"
            }
          });
        React.string(Js.Array.joinWith(", ", Belt.List.toArray(strings)))}
     </p>
     ->TestId.testId(~testId="dungeon")}
  </div>;
};
