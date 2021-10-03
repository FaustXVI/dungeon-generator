open DungeonGenerator
open Encounter
open Peril
open StringRenderer
open Belt
open LevelSelector
open PerilTypeSelector

type state = {
  budget: int,
  difficulty: difficulty,
  isCustomDifficulty: bool,
  generatedEncounter: option<encounter>,
  levels: Map.t<level, bool, LevelComparator.identity>,
  perilTypes: Map.t<perilType, bool, PerilTypeComparator.identity>,
}

type action =
  | BudgetChange(int)
  | SwitchLevel(level)
  | SwitchPerilType(perilType)
  | SetDifficulty(difficulty)
  | Generate

let generateNewEncounter = (
  budget: int,
  levels: Map.t<level, bool, LevelComparator.identity>,
  perilTypes: Map.t<perilType, bool, PerilTypeComparator.identity>,
): option<encounter> => {
  Some(
    generateEncounter(
      ~perils=createPerils(levelSelector(levels), perilTypeSelector(perilTypes)),
      ~chooser=pickRandom,
      ~budget,
    ),
  )
}

let initialState = {
  budget: Option.getWithDefault(experiencePointsForPredefinedDifficulty(Moderate), 80),
  difficulty: Moderate,
  isCustomDifficulty: false,
  generatedEncounter: None,
  levels: Map.fromArray(Array.map(levels, l => (l, true)), ~id=module(LevelComparator)),
  perilTypes: Map.fromArray(Array.map(perilTypes, l => (l, true)), ~id=module(PerilTypeComparator)),
}

let reducer = (state: state, action: action): state => {
  switch action {
  | Generate => {
      ...state,
      generatedEncounter: generateNewEncounter(state.budget, state.levels, state.perilTypes),
    }
  | SetDifficulty(difficulty) =>
    switch experiencePointsForPredefinedDifficulty(difficulty) {
    | Some(budget) => {
        ...state,
        difficulty: difficulty,
        budget: budget,
        generatedEncounter: None,
        isCustomDifficulty: false,
      }
    | None => {...state, difficulty: difficulty, generatedEncounter: None, isCustomDifficulty: true}
    }
  | BudgetChange(budget) => {...state, budget: budget, generatedEncounter: None}
  | SwitchLevel(level) => {
      ...state,
      levels: Map.update(state.levels, level, v => Some(!Option.getWithDefault(v, true))),
    }
  | SwitchPerilType(perilType) => {
      ...state,
      perilTypes: Map.update(state.perilTypes, perilType, v => Some(
        !Option.getWithDefault(v, true),
      )),
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
  let onPerilTypeSwitchChange = (p: perilType, _e: ReactEvent.Form.t): unit => {
    dispatch(SwitchPerilType(p))
  }
  <MaterialUi_Grid container={true}>
    {React.array(
      Array.map(levels, l =>
        <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
          <MaterialUi_FormControlLabel
            control={<MaterialUi_Switch
              checked={Option.getWithDefault(Map.get(state.levels, l), false)}
              onChange={onLevelSwitchChange(l)}
            />}
            label={React.string(renderLevel(l))}
          />
        </MaterialUi_Grid>
      ),
    )}
    {React.array(
      Array.map(perilTypes, p =>
        <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
          <MaterialUi_FormControlLabel
            control={<MaterialUi_Switch
              checked={Option.getWithDefault(Map.get(state.perilTypes, p), false)}
              onChange={onPerilTypeSwitchChange(p)}
            />}
            label={React.string(renderPerilType(p))}
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
      {if state.isCustomDifficulty {
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
      {switch state.generatedEncounter {
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
