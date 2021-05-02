open Jest;
open Expect;
open DungeonGenerator;

describe("Encounter Generator", () => {
    test("can generate a moderate encounter", () => {
        expect(generateEncounter())|> toBe("2 creatures at Group Level");
    });

});
