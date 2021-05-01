open Jest;
open ReactTestUtils;

describe("My basic test", () => {
  let container = ref(None);

  beforeEach(prepareContainer(container));
  afterEach(cleanupContainer(container));

  test("can render DOM elements", () => {
    let container = getContainer(container);
    act(() => {
      ReactDOMRe.render(<Greeting randomInt={_ => 10} />, container)
    });
    let button =
      DOM.findBySelector(container, "[data-testid='refresh_button']");
    switch (button) {
    | None => ()
    | Some(button) => Simulate.click(button)
    };
    let content =
      DOM.findBySelector(container, "[data-testid='dungeon']")
      ->Js.Nullable.fromOption
      ->Js.Nullable.toOption;

    switch (content) {
    | None => fail("dungeon should be defined")
    | Some(_) => pass
    };
  });
});
