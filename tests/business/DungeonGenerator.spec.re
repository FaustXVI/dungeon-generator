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

describe("Encounter Generator", () => {
  describe("unit tests", () => {
    describe("reduce on encounter's perils", () => {
      test("can reduce encounter's perils with any reducer function", () => {
        expect(
          newEncounter
          ->containing(Creature, 2)
          ->containing(SimpleDanger, 3)
          ->reduce("", (acc, p, n) =>
              acc
              ++ StringRenderer.render(p)
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
          ->containing(Creature, 2)
          ->containing(SimpleDanger, 3)
          ->reduce(0, (acc, _, n) => acc + n),
        )
        |> toEqual(5)
      });
    });
    describe("generate encounter", () => {
      test("can generate a moderate encounter with creatures only", () => {
        expect(generateEncounter(~perils=[|Creature|], ~chooser=pickRandom))
        |> toEqual(newEncounter->containing(Creature, 2))
      });

      test(
        "can generate a moderate encounter with creatures and dangers chosen via specific criteria",
        () => {
          let pickFirst = alist => List.head(alist);
          let tenSimpleDangers = newEncounter->containing(SimpleDanger, 10);
          expect(
            generateEncounter(
              ~perils=[|SimpleDanger, Creature|],
              ~chooser=pickFirst,
            ),
          )
          |> toEqual(tenSimpleDangers);
        },
      );
    });
    describe("experience points", () => {
      test(
        "experience points of an encounter with 1 creature only is 40 points",
        () => {
        expect(experiencePoints(newEncounter->containing(Creature, 1)))
        |> toEqual(40)
      });
      test(
        "experience points of an encounter with 1 complex danger only is 40 points",
        () => {
        expect(experiencePoints(newEncounter->containing(ComplexDanger, 1)))
        |> toEqual(40)
      });
      test(
        "experience points of an encounter with 1 simple danger  only is 8 points",
        () => {
        expect(experiencePoints(newEncounter->containing(SimpleDanger, 1)))
        |> toEqual(8)
      });
      test(
        "experience points of an encounter with 2 simple danger only is 16 points",
        () => {
        expect(experiencePoints(newEncounter->containing(SimpleDanger, 2)))
        |> toEqual(16)
      });
      test(
        "experience points of an encounter with 1 simple danger and 1 creature is 48 points",
        () => {
        expect(
          experiencePoints(
            newEncounter
            ->containing(SimpleDanger, 1)
            ->containing(Creature, 1),
          ),
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
