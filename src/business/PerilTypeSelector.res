open Belt
open Peril

module PerilTypeComparator = Id.MakeComparable({
  type t = perilType
  let cmp = (a: perilType, b: perilType) => compare(a, b)
})

let rec repeat = (perilType: perilType, n: int): array<perilType> => {
  if n == 0 {
    []
  } else {
    Array.concat([perilType], repeat(perilType, n - 1))
  }
}

let perilTypeSelector = (perilTypeMap: Map.t<perilType, int, PerilTypeComparator.identity>): array<
  perilType,
> => {
  Map.reduce(perilTypeMap, [], (acc, key, value) => Array.concat(acc, repeat(key, value)))
}
