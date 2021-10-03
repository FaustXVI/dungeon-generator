open Belt
open Peril

module LevelComparator = Id.MakeComparable({
  type t = level
  let cmp = (a: level, b: level) => compare(a, b)
})

let levelSelector = (levelMap: Map.t<level, bool, LevelComparator.identity>): array<level> => {
  Map.reduce(levelMap, [], (acc, key, value) =>
    if value {
      Array.concat(acc, [key])
    } else {
      acc
    }
  )
}
