open Peril
open Belt
open StringRenderer

@react.component
let make = (
  ~currentLevels: Map.t<level, int, LevelComparator.identity>,
  ~setLevel: (level, int) => unit,
) => {
  <MaterialUi_Grid container={true}>
    {React.array(
      Array.map(levels, l =>
        <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12}>
          <MaterialUi_Box paddingTop={MaterialUi_Box.Value.int(5)}>
            <MaterialUi_Grid container={true} xs={MaterialUi.Grid.Xs._12} spacing={#V3}>
              <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._3}>
                <MaterialUi_Slider
                  value={MaterialUi_Slider.Value.int(
                    Option.getWithDefault(Map.get(currentLevels, l), 0),
                  )}
                  onChange={(_, n) => setLevel(l, n)}
                  min={MaterialUi_Types.Number.int(0)}
                  max={MaterialUi_Types.Number.int(10)}
                  marks={MaterialUi_Slider.Marks.bool(true)}
                  valueLabelDisplay={#On}
                />
              </MaterialUi_Grid>
              <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs.auto}>
                {React.string(renderLevel(l))}
              </MaterialUi_Grid>
            </MaterialUi_Grid>
          </MaterialUi_Box>
        </MaterialUi_Grid>
      ),
    )}
  </MaterialUi_Grid>
}
