open Belt
open Peril

module PerilTypeComparator = Id.MakeComparable({
  type t = perilType
  let cmp = (a: perilType, b: perilType) => compare(a, b)
})

let perilTypeSelector = (perilTypeMap: Map.t<perilType, bool, PerilTypeComparator.identity>): array<perilType> => {
  Map.reduce(perilTypeMap, [], (acc, key, value) =>
    if value {
      Array.concat(acc, [key])
    } else {
      acc
    }
  )
}
