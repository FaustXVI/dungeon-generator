open Jest;
open ReactTestUtils;
open DOMHelpers;

describe("My basic test", () => {
  let refContainer = ref(None);

  beforeEach(prepareContainer(refContainer));
  afterEach(cleanupContainer(refContainer));

  test("can render DOM elements", () => {
    let container = getContainer(refContainer);
    act(() => {
      ReactDOMRe.render(
        <DungeonGeneratorGui randomInt={_ => 10} />,
        container,
      )
    });
    let button = querySelector(container, "[data-testid='refresh_button']");
    switch (button) {
    | None => fail("Refresh button not found")
    | Some(button) =>
      act(() => Simulate.click(button));
      let content = querySelector(container, "[data-testid='dungeon']");
      switch (content) {
      | None => fail("dungeon should be defined")
      | Some(_) => pass
      };
    };
  });
});
