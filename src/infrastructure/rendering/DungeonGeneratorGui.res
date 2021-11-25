open DungeonGenerator
open Encounter
open Peril
open Belt
open LevelSelector
open PerilTypeSelector
open BudgetSelectorComponent

type state = {
  budget: budget,
  levels: Map.t<level, bool, LevelComparator.identity>,
  perilTypes: Map.t<perilType, int, PerilTypeComparator.identity>,
  generatedEncounter: option<encounter>,
}

type action =
  | BudgetChange(budget)
  | SwitchLevel(level)
  | SetPerilType(perilType, int)
  | Generate

let generateNewEncounter = (
  budget: int,
  levels: Map.t<level, bool, LevelComparator.identity>,
  perilTypes: Map.t<perilType, int, PerilTypeComparator.identity>,
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
  budget: initialBudget,
  levels: Map.fromArray(Array.map(levels, l => (l, true)), ~id=module(LevelComparator)),
  perilTypes: Map.fromArray(Array.map(perilTypes, l => (l, 1)), ~id=module(PerilTypeComparator)),
  generatedEncounter: None,
}

let generate = (state: state): state => {
  {
    ...state,
    generatedEncounter: generateNewEncounter(
      getBudgetValue(state.budget),
      state.levels,
      state.perilTypes,
    ),
  }
}

let budgetChange = (state: state, budget: budget): state => {
  {...state, budget: budget}
}

let switchLevel = (state: state, level: level): state => {
  {
    ...state,
    levels: Map.update(state.levels, level, v => Some(!Option.getWithDefault(v, true))),
  }
}

let setPerilType = (state, perilType: perilType, weight: int): state => {
  {
    ...state,
    perilTypes: Map.update(state.perilTypes, perilType, _ => Some(weight)),
  }
}

let resetGeneratedEncounter = (state: state): state => {
  {...state, generatedEncounter: None}
}

let transit = (state: state, action: action): state => {
  switch action {
  | Generate => generate(state)
  | BudgetChange(budget) => resetGeneratedEncounter(budgetChange(state, budget))
  | SwitchLevel(level) => resetGeneratedEncounter(switchLevel(state, level))
  | SetPerilType(perilType, weight) =>
    resetGeneratedEncounter(setPerilType(state, perilType, weight))
  }
}

@react.component
let make = () => {
  let (state, dispatch) = React.useReducer(transit, initialState)

  <MaterialUi_Grid container={true}>
    <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
      <LevelSelectorComponent
        currentLevels={state.levels} switchLevel={l => dispatch(SwitchLevel(l))}
      />
    </MaterialUi_Grid>
    <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
      <PerilTypeSelectorComponent
        currentPerilTypes={state.perilTypes} setPerilType={(p, w) => dispatch(SetPerilType(p, w))}
      />
    </MaterialUi_Grid>
    <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
      <BudgetSelectorComponent
        currentBudget={state.budget} setBudget={budget => dispatch(BudgetChange(budget))}
      />
    </MaterialUi_Grid>
    <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
      <GenerateButtonComponent generate={() => dispatch(Generate)} />
    </MaterialUi_Grid>
    <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
      <EncounterDisplayComponent generatedEncounter={state.generatedEncounter} />
    </MaterialUi_Grid>
  </MaterialUi_Grid>
}
