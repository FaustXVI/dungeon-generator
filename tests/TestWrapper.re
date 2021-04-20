let addTestId = (testId, re) =>
  ReasonReact.cloneElement(re, ~props={"data-testid": testId}, [||]);

[@react.component]
let make = (~children, ~testId="wrapper") => {
  <div> children </div> |> addTestId(testId);
};
