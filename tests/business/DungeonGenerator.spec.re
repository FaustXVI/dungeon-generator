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

module LevelComparator =
  Id.MakeComparable({
    type t = level;
    let cmp = (a: level, b: level) => compare(a, b);
  });

describe("Encounter Generator", () => {
  describe("unit tests", () => {
    describe("reduce on encounter's perils", () => {
      test("can reduce encounter's perils with any reducer function", () => {
        expect(
          newEncounter
          ->containing(Creature(GroupLevel), 2)
          ->containing(SimpleDanger(GroupLevel), 3)
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
          ->containing(Creature(GroupLevel), 2)
          ->containing(SimpleDanger(GroupLevel), 3)
          ->reduce(0, (acc, _, n) => acc + n),
        )
        |> toEqual(5)
      });
    });
    describe("generate encounter", () => {
      test("can generate a moderate encounter with creatures only", () => {
        expect(
          generateEncounter(
            ~perils=[|Creature(GroupLevel)|],
            ~chooser=pickRandom,
          ),
        )
        |> toEqual(newEncounter->containing(Creature(GroupLevel), 2))
      });

      test(
        "can generate a moderate encounter with creatures and dangers chosen via specific criteria",
        () => {
          let pickFirst = alist => List.head(alist);
          let tenSimpleDangers =
            newEncounter->containing(SimpleDanger(GroupLevel), 10);
          expect(
            generateEncounter(
              ~perils=[|SimpleDanger(GroupLevel), Creature(GroupLevel)|],
              ~chooser=pickFirst,
            ),
          )
          |> toEqual(tenSimpleDangers);
        },
      );

      test(
        "can generate a moderate encounter with a bit more XP than necessary",
        () => {
        let pickFirst = alist => List.head(alist);
        let tenSimpleDangers =
          newEncounter->containing(SimpleDanger(GroupLevelMinus1), 14);
        expect(
          generateEncounter(
            ~perils=[|SimpleDanger(GroupLevelMinus1)|],
            ~chooser=pickFirst,
          ),
        )
        |> toEqual(tenSimpleDangers);
      });
    });
    describe("peril level", () => {
      [GroupLevel, GroupLevelMinus1]
      ->List.forEach(level => {
          test("gives a simple danger's level", () => {
            expect(perilLevel(SimpleDanger(level))) |> toEqual(level)
          });
          test("gives a complex danger's level", () => {
            expect(perilLevel(ComplexDanger(level))) |> toEqual(level)
          });
          test("gives a creature's level", () => {
            expect(perilLevel(Creature(level))) |> toEqual(level)
          });
        })
    });
    describe("experience points", () => {
      test(
        "experience points of an encounter with 1 creature only is 40 points",
        () => {
        expect(
          experiencePoints(
            newEncounter->containing(Creature(GroupLevel), 1),
          ),
        )
        |> toEqual(40)
      });
      test(
        "experience points of an encounter with 1 complex danger only is 40 points",
        () => {
        expect(
          experiencePoints(
            newEncounter->containing(ComplexDanger(GroupLevel), 1),
          ),
        )
        |> toEqual(40)
      });
      test(
        "experience points of an encounter with 1 simple danger  only is 8 points",
        () => {
        expect(
          experiencePoints(
            newEncounter->containing(SimpleDanger(GroupLevel), 1),
          ),
        )
        |> toEqual(8)
      });
      test(
        "experience points of an encounter with 1 simple danger level -1 only is 6 points",
        () => {
        expect(
          experiencePoints(
            newEncounter->containing(SimpleDanger(GroupLevelMinus1), 1),
          ),
        )
        |> toEqual(6)
      });
      test(
        "experience points of an encounter with 2 simple danger only is 16 points",
        () => {
        expect(
          experiencePoints(
            newEncounter->containing(SimpleDanger(GroupLevel), 2),
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
            ->containing(SimpleDanger(GroupLevel), 1)
            ->containing(Creature(GroupLevel), 1),
          ),
        )
        |> toEqual(48)
      });
    });
  });

  describe("acceptance tests", () => {
    test("moderate encounter represents 80 experience points", () => {
      let result =
        experiencePoints(
          generateEncounter(~perils=possiblePerils, ~chooser=pickRandom),
        );
      expect(result >= 80 && result <= 86) |> toBe(true);
    });
    test("two moderate encounters are potentially distinct", () => {
      // generate a dozen of encouters (with a fixed seed)
      let encounters =
        [|1, 2, 3, 4, 5, 6, 7, 8, 9, 10|]
        ->Array.map(_ =>
            generateEncounter(~perils=possiblePerils, ~chooser=pickRandom)
          );
      let set = Set.fromArray(encounters, ~id=(module EncounterComparator));

      expect(Set.size(set)) |> toBeGreaterThan(1);
    });
    test("two moderate encounters may contain different peril level", () => {
      // generate a dozen of encouters (with a fixed seed)
      let encounters =
        [|1, 2, 3, 4, 5, 6, 7, 8, 9, 10|]
        ->Array.map(_ =>
            generateEncounter(~perils=possiblePerils, ~chooser=pickRandom)
            ->reduce([], (acc, p, _) => List.add(acc, perilLevel(p)))
            ->List.toArray
          )
        ->Array.concatMany;
      let set = Set.fromArray(encounters, ~id=(module LevelComparator));

      expect(Set.size(set)) |> toBeGreaterThan(1);
    });
  });
});
