open Jest;
open Belt;
open Expect;
open DungeonGenerator;

module EncounterComparator =
  Id.MakeComparable({
    type t = encounter;
    let cmp = (a, b) =>
      Map.cmp(a.perils, b.perils, (n1, n2) => compare(n1, n2));
  });

let emptyPerils = Map.make(~id=(module PerilComparator));

describe("Encounter Generator", () => {
  describe("unit tests", () => {
    describe("generate encounter", () => {
      test("can generate a moderate encounter with creatures only", () => {
        expect(
          generateEncounter(~perils=[|Creature|], ~chooser=pickRandom).
            perils,
        )
        |> toEqual(emptyPerils->Map.set(Creature, 2))
      });

      test(
        "can generate a moderate encounter with creatures and dangers chosen via specific criteria",
        () => {
          let pickFirst = alist => List.head(alist);
          let tenSimpleDangers = emptyPerils->Map.set(SimpleDanger, 10);
          expect(
            generateEncounter(
              ~perils=[|SimpleDanger, Creature|],
              ~chooser=pickFirst,
            ).
              perils,
          )
          |> toEqual(tenSimpleDangers);
        },
      );
    });
    describe("experience points", () => {
      test(
        "experience points of an encounter with 1 creature only is 40 points",
        () => {
        expect(
          experiencePoints({perils: emptyPerils->Map.set(Creature, 1)}),
        )
        |> toEqual(40)
      });
      test(
        "experience points of an encounter with 1 complex danger only is 40 points",
        () => {
        expect(
          experiencePoints({perils: emptyPerils->Map.set(ComplexDanger, 1)}),
        )
        |> toEqual(40)
      });
      test(
        "experience points of an encounter with 1 simple danger  only is 8 points",
        () => {
        expect(
          experiencePoints({perils: emptyPerils->Map.set(SimpleDanger, 1)}),
        )
        |> toEqual(8)
      });
      test(
        "experience points of an encounter with 2 simple danger only is 16 points",
        () => {
        expect(
          experiencePoints({perils: emptyPerils->Map.set(SimpleDanger, 2)}),
        )
        |> toEqual(16)
      });
      test(
        "experience points of an encounter with 1 simple danger and 1 creature is 48 points",
        () => {
        expect(
          experiencePoints({
            perils:
              emptyPerils->Map.set(SimpleDanger, 1)->Map.set(Creature, 1),
          }),
        )
        |> toEqual(48)
      });
    });
  });

  describe("acceptance tests", () => {
    test("moderate encounter represents 80 experience points", () => {
      expect(
        experiencePoints(
          generateEncounter(
            ~perils=[|Creature, SimpleDanger|],
            ~chooser=pickRandom,
          ),
        ),
      )
      |> toEqual(80)
    });
    test("two moderate encounters are potentially distinct", () => {
      // generate a dozen of encouters (with a fixed seed)
      let encounters =
        [|1, 2, 3, 4, 5, 6, 7, 8, 9, 10|]
        ->Array.map(_ =>
            generateEncounter(
              ~perils=[|Creature, SimpleDanger|],
              ~chooser=pickRandom,
            )
          );
      let set = Set.fromArray(encounters, ~id=(module EncounterComparator));

      expect(Set.size(set)) |> toBeGreaterThan(1);
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
