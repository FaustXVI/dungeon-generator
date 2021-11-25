open Belt

let rec repeat = (element: 'a, n: int): array<'a> => {
  if n == 0 {
    []
  } else {
    Array.concat([element], repeat(element, n - 1))
  }
}

let selector = (elementMap: Map.t<'a, int, 'id>): array<'a> => {
  Map.reduce(elementMap, [], (acc, key, value) => Array.concat(acc, repeat(key, value)))
}
