open Jest;
open Expect;
open StringRenderer;
open Belt.List;
open DungeonGenerator;

describe("String renderer", () => {
  [
    (Creature(0), "Creature"),
    (SimpleDanger(0), "Simple Danger"),
    (ComplexDanger(0), "Complex Danger"),
  ]
  ->forEach(((peril, label)) => {
      test("provide a string for any peril value", () => {
        expect(render(peril)) |> toEqual(label)
      })
    })
});
