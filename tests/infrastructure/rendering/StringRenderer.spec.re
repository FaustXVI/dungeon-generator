open Jest;
open Expect;
open StringRenderer;
open Belt.List;
open PerilsDescription;

describe("String renderer", () => {
  perilLabelsTable->forEach(((peril, label)) => {
    test("provide a string for any peril value " ++ label, () => {
      expect(render(peril)) |> toEqual(label)
    })
  })
});
