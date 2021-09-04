open Belt
open Peril

module LevelComparator = Id.MakeComparable({
  type t = level
  let cmp = (a: level, b: level) => compare(a, b)
})

let levelSelector = (levelMap: Map.t<level, int, LevelComparator.identity>): array<level> => {
  Map.reduce(levelMap, [], (acc, key, value) =>
    if value == 1 {
      Array.concat(acc, [key])
    } else {
      acc
    }
  )
}
