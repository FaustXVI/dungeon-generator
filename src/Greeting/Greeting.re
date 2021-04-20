[@react.component]
let make = (~name) =>
  <p> {ReasonReact.string("Greetings " ++ name ++ "!")} </p>;
