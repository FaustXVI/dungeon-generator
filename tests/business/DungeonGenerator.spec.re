open Jest;
open Expect;
open DungeonGenerator;

module EncounterComparator =
  Belt.Id.MakeComparable({
    type t = encounter;
    let cmp = (a, b) =>
      Belt.List.cmp(
        a.perils, b.perils, ((elem1: peril, _), (elem2: peril, _)) =>
        compare(elem1, elem2)
      );
  });

describe("Encounter Generator", () => {
  describe("unit tests", () => {
    describe("generate encounter", () => {
      test("can generate a moderate encounter with creatures only", () => {
        expect(generateEncounter(~perils=[|Creature|], ()))
        |> toEqual({perils: [(Creature, 2)]})
      });

      test(
        "can generate a moderate encounter with creatures and dangers chosen via specific criteria",
        () => {
          let pickFirst = alist => Belt.List.head(alist);
          let tenSimpleDangers = [(SimpleDanger, 10)];
          let expected = {perils: tenSimpleDangers};
          expect(
            generateEncounter(
              ~perils=[|SimpleDanger, Creature|],
              ~chooser=pickFirst,
              (),
            ),
          )
          |> toEqual(expected);
        },
      );
    });
    describe("experience points", () => {
      test(
        "experience points of an encounter with 1 creature only is 40 points",
        () => {
        expect(experiencePoints({perils: [(Creature, 1)]})) |> toEqual(40)
      });
      test(
        "experience points of an encounter with 1 complex danger only is 40 points",
        () => {
        expect(experiencePoints({perils: [(ComplexDanger, 1)]}))
        |> toEqual(40)
      });
      test(
        "experience points of an encounter with 1 simple danger  only is 8 points",
        () => {
        expect(experiencePoints({perils: [(SimpleDanger, 1)]}))
        |> toEqual(8)
      });
      test(
        "experience points of an encounter with 2 simple danger only is 16 points",
        () => {
        expect(experiencePoints({perils: [(SimpleDanger, 2)]}))
        |> toEqual(16)
      });
      test(
        "experience points of an encounter with 1 simple danger and 1 creature is 48 points",
        () => {
        expect(
          experiencePoints({perils: [(SimpleDanger, 1), (Creature, 1)]}),
        )
        |> toEqual(48)
      });
    });
  });

  describe("acceptance tests", () => {
    test("moderate encounter represents 80 experience points", () => {
      expect(
        experiencePoints(
          generateEncounter(~perils=[|Creature, SimpleDanger|], ()),
        ),
      )
      |> toEqual(80)
    });
    test("two moderate encounters are potentially distinct", () => {
      // generate a dozen of encouters (with a fixed seed)
      let encounters =
        [|1, 2, 3, 4, 5, 6, 7, 8, 9, 10|]
        ->Belt.Array.map(_ =>
            generateEncounter(~perils=[|Creature, SimpleDanger|], ())
          );
      let set =
        Belt.Set.fromArray(encounters, ~id=(module EncounterComparator));

      expect(Belt.Set.size(set)) |> toBeGreaterThan(1);
    });
  });
});

// Product Owner's test:
//  the app can generate a moderate encounter with creatures and simple dangers
//  the resulting list should be chosen at random
//  the sum of XP from these perils should match the experience level (80 XP)

//    test("can generate a moderate encouter with creatures and simple dangers", () => {
//        let result = generateEncounter(~perils[|Creature,SimpleDanger|]);
//        sorted result is one of
//        [Creature, Creature]
//        [Creature, SimpleDanger * 5]
//        [SimpleDanger*10]
//

// TODO : add the notion of group level to all of this
