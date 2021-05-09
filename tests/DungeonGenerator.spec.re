open Jest;
open Expect;
open DungeonGenerator;

module EncounterComparator =
  Belt.Id.MakeComparable({
    type t = encounter
    let cmp = (a,b) => Belt.List.cmp(a.perils, b.perils, (elem1,elem2) => compare(elem1,elem2))
  });

describe("Encounter Generator", () => {
        describe("unit tests", () => {
                test("can generate a moderate encounter with creatures only", () => {
                        expect(generateEncounter(~perils=[|Creature|], ()))
                        |> toEqual({ perils : [Creature, Creature] })
                        });
                test("experience points of an encounter with 1 creature only is 40 points", () => {
                        expect(experiencePoints(~encounter={ perils: [Creature] }))
                        |> toEqual (40);
                        });
                test("can generate a moderate encounter with creatures and dangers chosen via specific criteria", () => {
                        let pickFirst = (alist => Belt.List.head(alist));
                        expect(generateEncounter(~perils=[|SimpleDanger,Creature|],~choose = pickFirst,()))
                        |> toEqual({ perils : Belt.List.map([1,2,3,4,5,6,7,8,9,10], _ => SimpleDanger)});
                });
        });

        describe("acceptance tests", () => {
                test("moderate encounter represents 80 experience points", () => {
                        expect(experiencePoints(~encounter=generateEncounter(~perils=[|Creature, SimpleDanger|],())))
                        |> toEqual(80);
                        });
                test("two moderate encounters are potentially distinct", () => {
                        // generate a dozen of encouters (with a fixed seed)
                        let encounters = [|1,2,3,4,5,6,7,8,9,10|]
                            -> Belt.Array.map(_ => generateEncounter(~perils=[|Creature,SimpleDanger|],()));
                        let set = Belt.Set.fromArray(encounters, ~id=(module EncounterComparator));

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
