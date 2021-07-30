open Belt
open DungeonGenerator
open Encounter

type state = {
  budget: int,
  difficulty: difficulty,
  isCustom: bool,
  encounter: option<encounter>,
}

type action =
  | BudgetChange(int)
  | SetDifficulty(difficulty)
  | Generate

let generateNewEncounter = budget => {
  Some(generateEncounter(~perils=possiblePerils, ~chooser=pickRandom, ~budget))
}

let initialState = {
  budget: Option.getWithDefault(experiencePointsForPredefinedDifficulty(Moderate), 80),
  difficulty: Moderate,
  isCustom: false,
  encounter: None,
}

let reducer = (state: state, action: action): state => {
  switch action {
  | Generate => {...state, encounter: generateNewEncounter(state.budget)}
  | SetDifficulty(difficulty) =>
    switch experiencePointsForPredefinedDifficulty(difficulty) {
    | Some(budget) => {difficulty: difficulty, budget: budget, encounter: None, isCustom: false}
    | None => {...state, difficulty: difficulty, encounter: None, isCustom: true}
    }
  | BudgetChange(budget) => {...state, budget: budget, encounter: None}
  }
}

@react.component
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState)
  let onCustomBudgetChange = (e: ReactEvent.Form.t): unit => {
    let value = ReactEvent.Form.target(e)["value"]
    dispatch(BudgetChange(value))
  }
  let onDifficultySelect = (e: ReactEvent.Form.t, _r: Js.t<'a>): unit => {
    let value = ReactEvent.Form.target(e)["value"]
    let difficulty = difficultyFromString(value)
    dispatch(SetDifficulty(difficulty))
  }
  <div>
    <MaterialUi_Select
      value={MaterialUi_Select.Value.string(difficultyToString(state.difficulty))}
      name="difficulty"
      onChange=onDifficultySelect>
      {React.array(
        Belt.Array.map(difficulties, difficulty => {
          <MaterialUi_MenuItem
            value={MaterialUi_MenuItem.Value.string(difficultyToString(difficulty))}>
            {React.string(difficultyToString(difficulty))}
          </MaterialUi_MenuItem>
        }),
      )}
    </MaterialUi_Select>
    {if state.isCustom {
      <MaterialUi_TextField
        _type="number"
        value={MaterialUi_TextField.Value.int(state.budget)}
        onChange=onCustomBudgetChange
      />
    } else {
      React.null
    }}
    <MaterialUi_Button variant=#Contained onClick={_event => dispatch(Generate)}>
      {React.string("Generate")}
    </MaterialUi_Button>
    {switch state.encounter {
    | None => React.null
    | Some(encounter) =>
      <ul>
        {StringRenderer.renderEncounter(encounter)
        ->Array.map(s => <li key=s> {React.string(s)} </li>)
        ->React.array}
      </ul>
    }}
  </div>
}