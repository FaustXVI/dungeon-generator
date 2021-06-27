open Jest;
open ReactTestUtils;
open DOMHelpers;

describe("My basic test", () => {
  let refContainer = ref(None);

  beforeEach(prepareContainer(refContainer));
  afterEach(cleanupContainer(refContainer));

  Skip.test("can render DOM elements", () => {
    // au départ pas de dungeon , j'appuie sur généré, j'ai un dungeon
    // je change la valeur de budget, j'ai un nouveau dungeon
    // je change la valeur à 0 => pas d'affichage (bug)
    // TODO : la valeur de budget est supérieur strict à 1 et au maximum à 800

    let container = getContainer(refContainer);
    act(() => {ReactDOMRe.render(<DungeonGeneratorGui />, container)});
    let content = querySelector(container, "[data-testid='dungeon']");
    switch (content) {
    | None => fail("dungeon should be defined")
    | Some(_) => pass
    };
  });
});
