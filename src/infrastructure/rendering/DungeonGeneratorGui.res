open DungeonGenerator
open Encounter
open Peril
open Belt
open LevelSelector
open PerilTypeSelector

type state = {
  budget: int,
  difficulty: difficulty,
  levels: Map.t<level, bool, LevelComparator.identity>,
  perilTypes: Map.t<perilType, bool, PerilTypeComparator.identity>,
  generatedEncounter: option<encounter>,
}

type action =
  | BudgetChange(int)
  | DifficultyChange(difficulty)
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
  difficulty: Moderate,
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
  {...state, budget: budget}
}

let difficultyChange = (state: state, difficulty: difficulty): state => {
  {
    ...state,
    difficulty: difficulty,
    budget: Option.getWithDefault(
      experiencePointsForPredefinedDifficulty(difficulty),
      state.budget,
    ),
  }
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

let resetGeneratedEncounter = (state: state): state => {
  {...state, generatedEncounter: None}
}

let transit = (state: state, action: action): state => {
  switch action {
  | Generate => generate(state)
  | BudgetChange(budget) => resetGeneratedEncounter(budgetChange(state, budget))
  | DifficultyChange(difficulty) => resetGeneratedEncounter(difficultyChange(state, difficulty))
  | SwitchLevel(level) => resetGeneratedEncounter(switchLevel(state, level))
  | SwitchPerilType(perilType) => resetGeneratedEncounter(switchPerilType(state, perilType))
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
      currentBudget={state.budget}
      setBudget={budget => dispatch(BudgetChange(budget))}
      currentDifficulty={state.difficulty}
      setDifficulty={difficulty => dispatch(DifficultyChange(difficulty))}
    />
    <GenerateButtonComponent generate={() => dispatch(Generate)} />
    <EncounterDisplayComponent generatedEncounter={state.generatedEncounter} />
  </MaterialUi_Grid>
}
