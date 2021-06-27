open Jest;
open ReactTestUtils;
open DOMHelpers;

describe("My basic test", () => {
  let refContainer = ref(None);

  beforeEach(prepareContainer(refContainer));
  afterEach(cleanupContainer(refContainer));

  test("can render DOM elements", () => {
    let container = getContainer(refContainer);
    act(() => {ReactDOMRe.render(<DungeonGeneratorGui />, container)});
    let content = querySelector(container, "[data-testid='dungeon']");
    switch (content) {
    | None => fail("dungeon should be defined")
    | Some(_) => pass
    };
  });
});
