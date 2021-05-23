open Jest;
open Expect;
open StringRenderer;
open Belt.List;
open DungeonGenerator;

describe("String renderer", () => {
  [
    (Creature, "Creature"),
    (SimpleDanger, "Simple Danger"),
    (ComplexDanger, "Complex Danger"),
  ]
  ->forEach(((peril, label)) => {
      test("provide a string for any peril value", () => {
        expect(render(peril)) |> toEqual(label)
      })
    })
});
