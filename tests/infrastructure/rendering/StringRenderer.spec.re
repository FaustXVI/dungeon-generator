open Jest;
open Expect;
open StringRenderer;
open Belt.List;
open DungeonGenerator;

describe("String renderer", () => {
  [
    (Creature(GroupLevel), "Creature at group level"),
    (SimpleDanger(GroupLevel), "Simple Danger at group level"),
    (ComplexDanger(GroupLevel), "Complex Danger at group level"),
    (Creature(GroupLevelMinus1), "Creature -1"),
    (SimpleDanger(GroupLevelMinus1), "Simple Danger -1"),
    (ComplexDanger(GroupLevelMinus1), "Complex Danger -1"),
  ]
  ->forEach(((peril, label)) => {
      test("provide a string for any peril value", () => {
        expect(render(peril)) |> toEqual(label)
      })
    })
});
