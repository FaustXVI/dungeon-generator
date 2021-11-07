open Peril
open Belt
open LevelSelector
open StringRenderer

@react.component
let make = (
  ~currentLevels: Map.t<level, bool, LevelComparator.identity>,
  ~switchLevel: level => unit,
) => {
  <MaterialUi_Grid container={true}>
    {React.array(
      Array.map(levels, l =>
        <MaterialUi_Grid item={true} xs={MaterialUi.Grid.Xs._12} key={renderLevel(l)}>
          <MaterialUi_FormControlLabel
            control={<MaterialUi_Switch
              checked={Option.getWithDefault(Map.get(currentLevels, l), false)}
              onChange={_ => switchLevel(l)}
            />}
            label={React.string(renderLevel(l))}
          />
        </MaterialUi_Grid>
      ),
    )}
  </MaterialUi_Grid>
}
