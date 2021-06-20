open Jest;
open Expect;
open StringRenderer;
open Belt.List;
open Peril;

describe("String renderer", () => {
  [
    (aPeril(Creature, GroupLevel), "Creature at group level"),
    (aPeril(SimpleDanger, GroupLevel), "Simple Danger at group level"),
    (aPeril(ComplexDanger, GroupLevel), "Complex Danger at group level"),
    (aPeril(Creature, GroupLevelMinus1), "Creature -1"),
    (aPeril(SimpleDanger, GroupLevelMinus1), "Simple Danger -1"),
    (aPeril(ComplexDanger, GroupLevelMinus1), "Complex Danger -1"),
  ]
  ->forEach(((peril, label)) => {
      test("provide a string for any peril value", () => {
        expect(render(peril)) |> toEqual(label)
      })
    })
});
