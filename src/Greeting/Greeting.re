[@react.component]
let make = (~name) =>
  <button> {ReasonReact.string("Greetings " ++ name ++ "!")} </button>;
