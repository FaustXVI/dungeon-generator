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
        <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
          <MaterialUi_Grid container={true} xs={MaterialUi.Grid.Xs._12} spacing={#V3}>
            <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._3}>
              <MaterialUi_Slider
                value={MaterialUi_Slider.Value.int(
                  Option.getWithDefault(Map.get(currentPerilTypes, p), 0),
                )}
                onChange={(_, n) => setPerilType(p, n)}
                min={MaterialUi_Types.Number.int(0)}
                max={MaterialUi_Types.Number.int(1)}
                marks={MaterialUi_Slider.Marks.bool(true)}
                valueLabelDisplay={#On}
              />
            </MaterialUi_Grid>
            <MaterialUi_Grid item={true}> {React.string(renderPerilType(p))} </MaterialUi_Grid>
          </MaterialUi_Grid>
        </MaterialUi_Grid>
      ),
    )}
  </MaterialUi_Grid>
}
