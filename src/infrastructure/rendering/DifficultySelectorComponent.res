open Encounter

@react.component
let make = (
  ~currentDifficulty: difficulty,
  ~isCustomDifficulty: bool,
  ~currentBudget: int,
  ~difficultySelect: difficulty => unit,
  ~setBudget: int => unit,
) => {
  let onDifficultySelect = (e: ReactEvent.Form.t, _r: Js.t<'a>): unit => {
    let value = ReactEvent.Form.target(e)["value"]
    let difficulty = difficultyFromString(value)
    difficultySelect(difficulty)
  }
  let onCustomBudgetChange = (e: ReactEvent.Form.t): unit => {
    let value = ReactEvent.Form.target(e)["value"]
    setBudget(value)
  }
  <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
    <MaterialUi_Select
      value={MaterialUi_Select.Value.string(difficultyToString(currentDifficulty))}
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
    {if isCustomDifficulty {
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
