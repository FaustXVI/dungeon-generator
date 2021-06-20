open Jest;
open Belt;
open Expect;
open Peril;
open Encounter;
open StringRenderer;
open PerilExperiencePointsTable;

module EncounterComparator =
  Id.MakeComparable({
    type t = encounter;
    let cmp = (a, b) =>
      Map.cmp(a.perils, b.perils, (n1, n2) => compare(n1, n2));
  });

module LevelComparator =
  Id.MakeComparable({
    type t = level;
    let cmp = (a: level, b: level) => compare(a, b);
  });

describe("Encounter Generator", () => {
  describe("peril level", () => {
    [GroupLevel, GroupLevelMinus1]
    ->List.forEach(level => {
        test("gives a simple danger's level", () => {
          expect(levelOf(aPeril(SimpleDanger, level))) |> toEqual(level)
        });
        test("gives a complex danger's level", () => {
          expect(levelOf(aPeril(ComplexDanger, level))) |> toEqual(level)
        });
        test("gives a creature's level", () => {
          expect(levelOf(aPeril(Creature, level))) |> toEqual(level)
        });
      })
  });
  describe("experience points for peril", () => {
    perilExperiencePointsTable->List.forEach(((peril, expectedExperience)) => {
      test("experience points for " ++ render(peril), () => {
        expect(experiencePointForPeril(peril))
        |> toEqual(expectedExperience)
      })
    })
  });
});
