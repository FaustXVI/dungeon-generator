open Jest;
open Expect;
open DungeonGenerator;

describe("Encounter Generator", () => {
        describe("unit tests", () => {
                test("can generate a moderate encounter with creatures only", () => {
                        expect(generateEncounter(~perils=[|Creature|]))
                        |> toEqual({ perils : [Creature, Creature] })
                        });
                test("experience points of an encounter with 1 creature only is 40 points", () => {
                    expect(experiencePoints(~encounter={ perils: [Creature] }))
                    |> toEqual (40);
                });
                });

        describe("acceptance tests", () => {
            test("moderate encounter represents 80 experience points", () => {
                expect(experiencePoints(~encounter=generateEncounter(~perils=[|Creature|])))
                |> toEqual(80);
            });
        });

//    test("can generate a moderate encouter with creatures and simple dangers", () => {
//        let result = generateEncounter(~perils[|Creature,SimpleDanger|]);
//        sorted result is one of 
//        [Creature, Creature]
//        [Creature, SimpleDanger * 5]
//        [SimpleDanger*10]
//
// Product Owner's test:
//  the app can generate a moderate encounter with creatures and simple dangers
//  the resulting list should be chosen at random
//  the sum of XP from these perils should match the experience level (80 XP)
});

// TODO : add the notion of group level to all of this
