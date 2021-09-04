open Jest
open Expect
open Peril
open Belt
open LevelSelector

describe("Level Selector", () => {
  test("can set a unique desired level for encounter generation", () => {
    let levelMap = Map.set(Map.make(~id=module(LevelComparator)), GroupLevelMinus3, 1)
    let levels = levelSelector(levelMap)
    expect(levels) |> toEqual([GroupLevelMinus3])
  })
  test("can set two desired levels for encounter generation", () => {
    let levelMap = Map.set(
      Map.set(Map.make(~id=module(LevelComparator)), GroupLevelMinus3, 1),
      GroupLevelPlus3,
      1,
    )
    let levels = levelSelector(levelMap)
    expect(levels) |> toEqual([GroupLevelMinus3, GroupLevelPlus3])
  })
  test("can set one of two levels for encounter generation", () => {
    let levelMap = Map.set(
      Map.set(Map.make(~id=module(LevelComparator)), GroupLevelMinus3, 0),
      GroupLevelPlus3,
      1,
    )
    let levels = levelSelector(levelMap)
    expect(levels) |> toEqual([GroupLevelPlus3])
  })
})
