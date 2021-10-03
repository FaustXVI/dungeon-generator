open Jest
open Expect
open Peril
open Belt
open LevelSelector

describe("Level Selector", () => {
  test("can set a unique desired level for encounter generation", () => {
    let levelMap = Map.fromArray([(GroupLevelMinus3, true)], ~id=module(LevelComparator))
    let levels = levelSelector(levelMap)
    expect(levels) |> toEqual([GroupLevelMinus3])
  })
  test("can set two desired levels for encounter generation", () => {
    let levelMap = Map.fromArray(
      [(GroupLevelMinus3, true), (GroupLevelPlus3, true)],
      ~id=module(LevelComparator),
    )
    let levels = levelSelector(levelMap)
    expect(levels) |> toEqual([GroupLevelMinus3, GroupLevelPlus3])
  })
  test("can set one of two levels for encounter generation", () => {
    let levelMap = Map.fromArray(
      [(GroupLevelMinus3, false), (GroupLevelPlus3, true)],
      ~id=module(LevelComparator),
    )
    let levels = levelSelector(levelMap)
    expect(levels) |> toEqual([GroupLevelPlus3])
  })
})
