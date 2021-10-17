open DungeonGenerator
open Encounter
open Peril
open Belt
open LevelSelector
open PerilTypeSelector

type state = {
  budget: int,
  levels: Map.t<level, bool, LevelComparator.identity>,
  perilTypes: Map.t<perilType, bool, PerilTypeComparator.identity>,
  generatedEncounter: option<encounter>,
}

type action =
  | BudgetChange(int)
  | SwitchLevel(level)
  | SwitchPerilType(perilType)
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
  levels: Map.fromArray(Array.map(levels, l => (l, true)), ~id=module(LevelComparator)),
  perilTypes: Map.fromArray(Array.map(perilTypes, l => (l, true)), ~id=module(PerilTypeComparator)),
  generatedEncounter: None,
}

let generate = (state: state): state => {
  {
    ...state,
    generatedEncounter: generateNewEncounter(state.budget, state.levels, state.perilTypes),
  }
}

let budgetChange = (state: state, budget: int): state => {
  {...state, budget: budget, generatedEncounter: None}
}

let switchLevel = (state: state, level: level): state => {
  {
    ...state,
    levels: Map.update(state.levels, level, v => Some(!Option.getWithDefault(v, true))),
  }
}
let switchPerilType = (state, perilType: perilType): state => {
  {
    ...state,
    perilTypes: Map.update(state.perilTypes, perilType, v => Some(!Option.getWithDefault(v, true))),
  }
}

let transit = (state: state, action: action): state => {
  switch action {
  | Generate => generate(state)
  | BudgetChange(budget) => budgetChange(state, budget)
  | SwitchLevel(level) => switchLevel(state, level)
  | SwitchPerilType(perilType) => switchPerilType(state, perilType)
  }
}

@react.component
let make = () => {
  let (state, dispatch) = React.useReducer(transit, initialState)

  <MaterialUi_Grid container={true}>
    <LevelSelectorComponent
      currentLevels={state.levels} switchLevel={l => dispatch(SwitchLevel(l))}
    />
    <PerilTypeSelectorComponent
      currentPerilTypes={state.perilTypes} switchPerilType={p => dispatch(SwitchPerilType(p))}
    />
    <BudgetSelectorComponent
      currentBudget={state.budget} setBudget={budget => dispatch(BudgetChange(budget))}
    />
    <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
      <MaterialUi_Button variant=#Contained color={#Primary} onClick={_event => dispatch(Generate)}>
        {React.string("Generate")}
      </MaterialUi_Button>
    </MaterialUi_Grid>
    <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
      {switch state.generatedEncounter {
      | None => React.null
      | Some(encounter) => <EncounterDisplayComponent encounter={encounter} />
      }}
    </MaterialUi_Grid>
  </MaterialUi_Grid>
}
