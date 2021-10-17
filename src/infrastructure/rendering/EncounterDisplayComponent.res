open Encounter
open Belt
open StringRenderer

@react.component
let make = (~generatedEncounter: option<encounter>) => {
  <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
    {switch generatedEncounter {
    | None => React.null
    | Some(encounter) =>
      <div>
        <p>
          {React.string("Encounter with ")}
          {React.int(experiencePoints(encounter))}
          {React.string(" experience points")}
        </p>
        <ul>
          {renderEncounter(encounter)
          ->Array.map(s => <li key=s> {React.string(s)} </li>)
          ->React.array}
        </ul>
      </div>
    }}
  </MaterialUi_Grid>
}
