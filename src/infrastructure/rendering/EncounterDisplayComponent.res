open Encounter
open Belt
open StringRenderer

@react.component
let make = (~encounter: encounter) => {
  <div>
    <p>
      {React.string("Encounter with ")}
      {React.int(experiencePoints(encounter))}
      {React.string(" experience points")}
    </p>
    <ul>
      {renderEncounter(encounter)->Array.map(s => <li key=s> {React.string(s)} </li>)->React.array}
    </ul>
  </div>
}
