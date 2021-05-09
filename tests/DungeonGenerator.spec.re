open Jest;
open Expect;
open DungeonGenerator;

describe("Encounter Generator", () => {
    test("can generate a moderate encounter", () => {
        expect(generateEncounter())|> toEqual({ perils : [Creature, Creature] })
    });

});
