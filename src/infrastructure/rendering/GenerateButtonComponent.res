@react.component
let make = (~generate: unit => unit) => {
  <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
    <MaterialUi_Button variant=#Contained color={#Primary} onClick={_event => generate()}>
      {React.string("Generate")}
    </MaterialUi_Button>
  </MaterialUi_Grid>
}
