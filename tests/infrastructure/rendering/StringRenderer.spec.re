open Jest;
open Expect;
open StringRenderer;
open Belt.List;
open DungeonGenerator;

describe("String renderer", () => {
  [
    (Creature(GroupLevel), "Creature"),
    (SimpleDanger(GroupLevel), "Simple Danger"),
    (ComplexDanger(GroupLevel), "Complex Danger"),
  ]
  ->forEach(((peril, label)) => {
      test("provide a string for any peril value", () => {
        expect(render(peril)) |> toEqual(label)
      })
    })
});
