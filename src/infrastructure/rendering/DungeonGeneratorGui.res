open DungeonGenerator
open Encounter
open Peril
open StringRenderer
open Belt
open LevelSelector

type state = {
  budget: int,
  difficulty: difficulty,
  isCustom: bool,
  encounter: option<encounter>,
  levels: Map.t<level, int, LevelComparator.identity>,
}

type action =
  | BudgetChange(int)
  | SwitchLevel(level)
  | SetDifficulty(difficulty)
  | Generate

let generateNewEncounter = (budget, levels) => {
  Some(generateEncounter(~perils=createPerils(levelSelector(levels)), ~chooser=pickRandom, ~budget))
}

let initialState = {
  budget: Option.getWithDefault(experiencePointsForPredefinedDifficulty(Moderate), 80),
  difficulty: Moderate,
  isCustom: false,
  encounter: None,
  levels: Map.fromArray(Array.map(levels, l => (l, 1)), ~id=module(LevelComparator)),
}

let reducer = (state: state, action: action): state => {
  switch action {
  | Generate => {...state, encounter: generateNewEncounter(state.budget, state.levels)}
  | SetDifficulty(difficulty) =>
    switch experiencePointsForPredefinedDifficulty(difficulty) {
    | Some(budget) => {
        ...state,
        difficulty: difficulty,
        budget: budget,
        encounter: None,
        isCustom: false,
      }
    | None => {...state, difficulty: difficulty, encounter: None, isCustom: true}
    }
  | BudgetChange(budget) => {...state, budget: budget, encounter: None}
  | SwitchLevel(level) => {
      ...state,
      levels: Map.update(state.levels, level, v => Some(1 - Option.getWithDefault(v, 1))),
    }
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
  let onLevelSwitchChange = (l: level, _e: ReactEvent.Form.t): unit => {
    dispatch(SwitchLevel(l))
  }
  <MaterialUi_Grid container={true}>
    {React.array(
      Array.map(levels, l =>
        <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
          <MaterialUi_FormControlLabel
            control={<MaterialUi_Switch
              checked={Option.getWithDefault(Map.get(state.levels, l), 0) == 1}
              onChange={onLevelSwitchChange(l)}
            />}
            label={React.string(renderLevel(l))}
          />
        </MaterialUi_Grid>
      ),
    )}
    <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
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
    </MaterialUi_Grid>
    <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
      <MaterialUi_Button variant=#Contained color={#Primary} onClick={_event => dispatch(Generate)}>
        {React.string("Generate")}
      </MaterialUi_Button>
    </MaterialUi_Grid>
    <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
      {switch state.encounter {
      | None => React.null
      | Some(encounter) =>
        <ul>
          {StringRenderer.renderEncounter(encounter)
          ->Array.map(s => <li key=s> {React.string(s)} </li>)
          ->React.array}
        </ul>
      }}
    </MaterialUi_Grid>
  </MaterialUi_Grid>
}
