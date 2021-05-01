type state = {generatedMap: option(int)};

type action =
  | Generate;

let initialState = {generatedMap: None};

let reducer = (randomInt, _, action) => {
  switch (action) {
  | Generate => {generatedMap: Some(randomInt(10))}
  };
};

[@react.component]
let make = (~randomInt=Random.int) => {
  let (state, dispatch) =
    React.useReducer(reducer(randomInt), initialState);
  let print =
    switch (state) {
    | {generatedMap: Some(i)} => string_of_int(i)
    | _ => ""
    };
  <div>
    <div>
      <button onClick={_event => dispatch(Generate)}>
        {React.string("Refresh")}
      </button>
    </div>
    <p> {React.string(print)} </p>
  </div>;
};
