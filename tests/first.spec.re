open Jest;
open ReactTestUtils;

let findBySelector = (element, selector): option(Dom.element) => {
  DOM.findBySelector(element, selector)
  ->Js.Nullable.fromOption
  ->Js.Nullable.toOption;
};

describe("My basic test", () => {
  let refContainer = ref(None);

  beforeEach(prepareContainer(refContainer));
  afterEach(cleanupContainer(refContainer));

  test("can render DOM elements", () => {
    let container = getContainer(refContainer);
    act(() => {
      ReactDOMRe.render(<Greeting randomInt={_ => 10} />, container)
    });
    let button = findBySelector(container, "[data-testid='refresh_button']");
    switch (button) {
    | None => fail("Refresh button not found")
    | Some(button) =>
      act(() => Simulate.click(button));
      let content = findBySelector(container, "[data-testid='dungeon']");
      switch (content) {
      | None => fail("dungeon should be defined")
      | Some(_) => pass
      };
    };
  });
});
