let generateDungeon = randomInt =>
  if (randomInt(2) == 0) {
    (-1);
  } else {
    1;
  };

type state = {generatedMap: option(int)};

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
      <button onClick={_event => dispatch(Generate)}>
        {React.string("Refresh")}
      </button>
    </div>
    {switch (state) {
     | {generatedMap: Some(i)} => <p> {React.string(string_of_int(i))} </p>
     | _ => React.null
     }}
  </div>;
};
