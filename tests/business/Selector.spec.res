open Jest
open Expect
open Peril
open Belt
open Selector

describe("Level Selector", () => {
  test("can set a unique desired level for encounter generation", () => {
    let levelMap = Map.fromArray([(GroupLevelMinus3, 1)], ~id=module(LevelComparator))
    let levels = selector(levelMap)
    expect(levels) |> toEqual([GroupLevelMinus3])
  })
  test("can set two desired levels for encounter generation", () => {
    let levelMap = Map.fromArray(
      [(GroupLevelMinus3, 1), (GroupLevelPlus3, 1)],
      ~id=module(LevelComparator),
    )
    let levels = selector(levelMap)
    expect(levels) |> toEqual([GroupLevelMinus3, GroupLevelPlus3])
  })
  test("can set one of two levels for encounter generation", () => {
    let levelMap = Map.fromArray(
      [(GroupLevelMinus3, 0), (GroupLevelPlus3, 1)],
      ~id=module(LevelComparator),
    )
    let levels = selector(levelMap)
    expect(levels) |> toEqual([GroupLevelPlus3])
  })
})
