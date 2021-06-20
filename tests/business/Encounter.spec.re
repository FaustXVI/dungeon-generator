open Jest;
open Belt;
open Expect;
open Peril;
open Encounter;

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
  describe("reduce on encounter's perils", () => {
    test("can reduce encounter's perils with any reducer function", () => {
      expect(
        newEncounter
        ->containing(aPeril(Creature, GroupLevel), 2)
        ->containing(aPeril(SimpleDanger, GroupLevel), 3)
        ->reduce("", (acc, p, n) =>
            acc
            ++ (
              switch (perilTypeOf(p)) {
              | Creature => "Creature"
              | SimpleDanger => "Simple Danger"
              | ComplexDanger => "Complex Danger"
              }
            )
            ++ " "
            ++ string_of_int(n)
            ++ " "
          ),
      )
      |> toEqual("Creature 2 Simple Danger 3 ")
    });
    test("can reduce encounter's perils so that we can count perils", () => {
      expect(
        newEncounter
        ->containing(aPeril(Creature, GroupLevel), 2)
        ->containing(aPeril(SimpleDanger, GroupLevel), 3)
        ->reduce(0, (acc, _, n) => acc + n),
      )
      |> toEqual(5)
    });
  });
  describe("experience points", () => {
    test(
      "experience points of an encounter with 1 creature only is 40 points", () => {
      expect(
        experiencePoints(
          newEncounter->containing(aPeril(Creature, GroupLevel), 1),
        ),
      )
      |> toEqual(40)
    });
    test(
      "experience points of an encounter with 1 complex danger only is 40 points",
      () => {
      expect(
        experiencePoints(
          newEncounter->containing(aPeril(ComplexDanger, GroupLevel), 1),
        ),
      )
      |> toEqual(40)
    });
    test(
      "experience points of an encounter with 1 simple danger  only is 8 points",
      () => {
      expect(
        experiencePoints(
          newEncounter->containing(aPeril(SimpleDanger, GroupLevel), 1),
        ),
      )
      |> toEqual(8)
    });
    test(
      "experience points of an encounter with 1 simple danger level -1 only is 6 points",
      () => {
      expect(
        experiencePoints(
          newEncounter->containing(
            aPeril(SimpleDanger, GroupLevelMinus1),
            1,
          ),
        ),
      )
      |> toEqual(6)
    });
    test(
      "experience points of an encounter with 2 simple danger only is 16 points",
      () => {
      expect(
        experiencePoints(
          newEncounter->containing(aPeril(SimpleDanger, GroupLevel), 2),
        ),
      )
      |> toEqual(16)
    });
    test(
      "experience points of an encounter with 1 simple danger and 1 creature is 48 points",
      () => {
      expect(
        experiencePoints(
          newEncounter
          ->containing(aPeril(SimpleDanger, GroupLevel), 1)
          ->containing(aPeril(Creature, GroupLevel), 1),
        ),
      )
      |> toEqual(48)
    });
  });
});
