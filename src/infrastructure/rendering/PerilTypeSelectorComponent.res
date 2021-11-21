open Peril
open Belt
open StringRenderer
open PerilTypeSelector

@react.component
let make = (
  ~currentPerilTypes: Map.t<perilType, int, PerilTypeComparator.identity>,
  ~setPerilType: (perilType, int) => unit,
) => {
  <MaterialUi_Grid container={true}>
    {React.array(
      Array.map(perilTypes, p =>
        <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12} key={renderPerilType(p)}>
          <MaterialUi_FormControlLabel
            control={<MaterialUi_Switch
              checked={Option.getWithDefault(Map.get(currentPerilTypes, p), 0) == 1}
              onChange={_ =>
                setPerilType(p, 1 - Option.getWithDefault(Map.get(currentPerilTypes, p), 1))}
            />}
            label={React.string(renderPerilType(p))}
          />
        </MaterialUi_Grid>
      ),
    )}
  </MaterialUi_Grid>
}
