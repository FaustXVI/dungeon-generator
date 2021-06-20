open Jest;
open Belt;
open Expect;
open DungeonGenerator;
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
  describe("unit tests", () => {
    describe("generate encounter", () => {
      test("can generate a moderate encounter with creatures only", () => {
        expect(
          generateEncounter(
            ~perils=[|aPeril(Creature, GroupLevel)|],
            ~chooser=pickRandom,
          ),
        )
        |> toEqual(
             newEncounter->containing(aPeril(Creature, GroupLevel), 2),
           )
      });

      test(
        "can generate a moderate encounter with creatures and dangers chosen via specific criteria",
        () => {
          let pickFirst = alist => List.head(alist);
          let tenSimpleDangers =
            newEncounter->containing(aPeril(SimpleDanger, GroupLevel), 10);
          expect(
            generateEncounter(
              ~perils=[|
                aPeril(SimpleDanger, GroupLevel),
                aPeril(Creature, GroupLevel),
              |],
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
          newEncounter->containing(
            aPeril(SimpleDanger, GroupLevelMinus1),
            14,
          );
        expect(
          generateEncounter(
            ~perils=[|aPeril(SimpleDanger, GroupLevelMinus1)|],
            ~chooser=pickFirst,
          ),
        )
        |> toEqual(tenSimpleDangers);
      });
    });
    test(
      "possible perils at a minimum all the combinations of peril type with level",
      () => {
      expect(possiblePerils)
      |> toEqual([|
           aPeril(Creature, GroupLevel),
           aPeril(Creature, GroupLevelMinus1),
           aPeril(SimpleDanger, GroupLevel),
           aPeril(SimpleDanger, GroupLevelMinus1),
           aPeril(ComplexDanger, GroupLevel),
           aPeril(ComplexDanger, GroupLevelMinus1),
         |])
    });
  });

  describe("acceptance tests", () => {
    test("moderate encounter represents 80 experience points", () => {
      let encounter =
        generateEncounter(~perils=possiblePerils, ~chooser=pickRandom);
      let result = experiencePoints(encounter);
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
            ->reduce([], (acc, p, _) => List.add(acc, levelOf(p)))
            ->List.toArray
          )
        ->Array.concatMany;
      let set = Set.fromArray(encounters, ~id=(module LevelComparator));

      expect(Set.size(set)) |> toBeGreaterThan(1);
    });
  });
});
