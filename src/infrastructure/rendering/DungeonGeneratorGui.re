open Belt;
open DungeonGenerator;
open Encounter;

type state = {
  budget: int,
  isCustom: bool,
  encounter: option(encounter),
};

type action =
  | BudgetChange(int)
  | SetCustom(bool)
  | Generate;

let generateNewEncounter = budget => {
  Some(
    generateEncounter(~perils=possiblePerils, ~chooser=pickRandom, ~budget),
  );
};

let initialState = {budget: 80, isCustom: false, encounter: None};

let reducer = (state: state, action: action): state => {
  switch (action) {
  | Generate => {
      ...state,
      encounter: generateNewEncounter(state.budget),
    }
  | SetCustom(isCustom) => {...state, isCustom:isCustom }
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
    if (value == "moderate") {
        dispatch(BudgetChange(80));
        dispatch(SetCustom(false));
    }
    else {
        dispatch(SetCustom(true))
    }
  };
  <div>
    <select name="difficulty" onChange=onSelect>
        <option value="moderate">{React.string("Moderate")}</option>
        <option value="custom">{React.string("Custom")}</option>
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
