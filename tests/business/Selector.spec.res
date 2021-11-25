open Jest
open Expect
open Peril
open Belt
open Selector

describe("Selector", () => {
  test("can set a unique desired value (for instance level)", () => {
    let levelMap = Map.fromArray([(GroupLevelMinus3, 1)], ~id=module(LevelComparator))
    let levels = selector(levelMap)
    expect(levels) |> toEqual([GroupLevelMinus3])
  })
  test("can set two desired values", () => {
    let levelMap = Map.fromArray(
      [(Creature, 1), (SimpleDanger, 1)],
      ~id=module(PerilTypeComparator),
    )
    let levels = selector(levelMap)
    expect(levels) |> toEqual([Creature, SimpleDanger])
  })
  test("can set one of two values", () => {
    let levelMap = Map.fromArray(
      [(GroupLevelMinus3, 0), (GroupLevelPlus3, 1)],
      ~id=module(LevelComparator),
    )
    let levels = selector(levelMap)
    expect(levels) |> toEqual([GroupLevelPlus3])
  })
})
