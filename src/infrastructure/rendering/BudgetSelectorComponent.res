open Encounter
open Belt

type budget = {
  value: int,
  difficulty: difficulty,
}

let getBudgetValue = (budget: budget): int => {
  budget.value
}

let initialBudget = {value: 80, difficulty: Moderate}

@react.component
let make = (~currentBudget: budget, ~setBudget: budget => unit) => {
  let onDifficultySelect = (e: ReactEvent.Form.t, _r: Js.t<'a>): unit => {
    let value = ReactEvent.Form.target(e)["value"]
    let difficulty = difficultyFromString(value)
    setBudget({
      difficulty: difficulty,
      value: Option.getWithDefault(
        experiencePointsForPredefinedDifficulty(difficulty),
        currentBudget.value,
      ),
    })
  }
  let onCustomBudgetChange = (e: ReactEvent.Form.t): unit => {
    let value = ReactEvent.Form.target(e)["value"]
    setBudget({...currentBudget, value: value})
  }
  let difficultySelect = {
    <MaterialUi_Select
      value={MaterialUi_Select.Value.string(difficultyToString(currentBudget.difficulty))}
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
    {if currentBudget.difficulty == Custom {
      <MaterialUi_TextField
        _type="number"
        value={MaterialUi_TextField.Value.int(currentBudget.value)}
        onChange=onCustomBudgetChange
      />
    } else {
      React.null
    }}
  </MaterialUi_Grid>
}
