open Encounter

type state = {
  difficulty: difficulty,
  isCustomDifficulty: bool,
}

type action = SetDifficulty(difficulty)

let initialState = {
  difficulty: Moderate, // TODO if the user gives something else than 80 at first => bug
  isCustomDifficulty: false,
}

@react.component
let make = (~currentBudget: int, ~setBudget: int => unit) => {
  let setDifficulty = (difficulty: difficulty): state => {
    switch experiencePointsForPredefinedDifficulty(difficulty) {
    | Some(budget) => {
        setBudget(budget)
        {difficulty: difficulty, isCustomDifficulty: false}
      }
    | None => {difficulty: difficulty, isCustomDifficulty: true}
    }
  }

  let transit = (_state: state, action: action): state => {
    switch action {
    | SetDifficulty(difficulty) => setDifficulty(difficulty)
    }
  }

  let (state, dispatch) = React.useReducer(transit, initialState)

  let onDifficultySelect = (e: ReactEvent.Form.t, _r: Js.t<'a>): unit => {
    let value = ReactEvent.Form.target(e)["value"]
    let difficulty = difficultyFromString(value)
    dispatch(SetDifficulty(difficulty))
  }
  let onCustomBudgetChange = (e: ReactEvent.Form.t): unit => {
    let value = ReactEvent.Form.target(e)["value"]
    setBudget(value)
  }
  let difficultySelect = {
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
  }

  <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
    <MaterialUi_FormControlLabel
      labelPlacement={#Start} control=difficultySelect label={React.string("Predefined budget : ")}
    />
    {if state.isCustomDifficulty {
      <MaterialUi_TextField
        _type="number"
        value={MaterialUi_TextField.Value.int(currentBudget)}
        onChange=onCustomBudgetChange
      />
    } else {
      React.null
    }}
  </MaterialUi_Grid>
}
