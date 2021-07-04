open Belt;
open DungeonGenerator;
open Encounter;


type state = {
  budget: int,
  difficulty: difficulty,
  isCustom: bool,
  encounter: option(encounter),
};

type action =
  | BudgetChange(int)
  | SetDifficulty(difficulty)
  | Generate;

let generateNewEncounter = budget => {
  Some(
    generateEncounter(~perils=possiblePerils, ~chooser=pickRandom, ~budget),
  );
};

let initialState = { budget: Option.getWithDefault(experiencePointsForPredefinedDifficulty(Moderate),80)
                   , difficulty: Moderate
                   , isCustom: false
                   , encounter: None};

let reducer = (state: state, action: action): state => {
  switch (action) {
  | Generate => {
      ...state,
      encounter: generateNewEncounter(state.budget),
    }
  | SetDifficulty(difficulty) => {
    switch(experiencePointsForPredefinedDifficulty(difficulty)) {
    | Some(budget) => {...state, budget:budget, encounter: None, isCustom:false }
    | None => {...state, encounter: None, isCustom:true }
    }
  }
  | BudgetChange(budget) => {...state, budget: budget, encounter: None}
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let onChange = (e: ReactEvent.Form.t): unit => {
    let value = e->ReactEvent.Form.target##value;
    dispatch(BudgetChange(value));
  };
  let onSelect = (e: ReactEvent.Form.t): unit => {
    let value = e->ReactEvent.Form.target##value;
    let difficulty = difficultyFromString(value);
    dispatch(SetDifficulty(difficulty))
  };
  <div>
    <select name="difficulty" onChange=onSelect>
        { React.array(Belt.Array.map([|Weak, Moderate, Custom|], difficulty =>
            {<option value=difficultyToString(difficulty) selected={difficulty==state.difficulty}>{React.string(difficultyToString(difficulty))}</option>}
            ))
        }
   </select>

    {if (state.isCustom) {<input type_="number" value={string_of_int(state.budget)} onChange />}
    else React.string("")
    }
    <button onClick={_event => dispatch(Generate)}>
      {React.string("Generate")}
    </button>

    {switch (state.encounter) {
     | None => React.string("")
     | Some(encounter) =>
       <ul>
         {StringRenderer.renderEncounter(encounter)
          ->Array.map(s => <li key=s> {React.string(s)} </li>)
          ->React.array}
       </ul>
     }}
  </div>;
};
