open Belt;
open Jest;
open ReactTestUtils;
open Expect;
open Webapi;

describe("My basic test", () => {
  // Here, we prepare an empty ref that will eventually be
  // the root node for our test
  let container = ref(None);

  // Before each test, creates a new div root
  beforeEach(prepareContainer(container));
  // After each test, removes the div
  afterEach(cleanupContainer(container));

  test("can render DOM elements", () => {
    // The following function gives us the div
    let container = getContainer(container);

    // Most of the ReactTestUtils API is there
    act(() => {
      ReactDOMRe.render(<div> <Greeting name="Commander" /> </div>, container)
    });

    expect(
      Option.map(
        container->DOM.findBySelector("div"),
        Dom.Element.textContent,
      ),
    )
    |> toBe(Some("Greetings Commander!"));
  });
});
