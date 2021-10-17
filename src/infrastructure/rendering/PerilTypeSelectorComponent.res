open Peril
open Belt
open StringRenderer
open PerilTypeSelector

@react.component
let make = (
  ~currentPerilTypes: Map.t<perilType, bool, PerilTypeComparator.identity>,
  ~switchPerilType: perilType => unit,
) => {
  <MaterialUi_Grid container={true}>
    {React.array(
      Array.map(perilTypes, p =>
        <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
          <MaterialUi_FormControlLabel
            control={<MaterialUi_Switch
              checked={Option.getWithDefault(Map.get(currentPerilTypes, p), false)}
              onChange={_ => switchPerilType(p)}
            />}
            label={React.string(renderPerilType(p))}
          />
        </MaterialUi_Grid>
      ),
    )}
  </MaterialUi_Grid>
}
