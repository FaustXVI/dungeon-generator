open Jest;
open ReactTestUtils;
open Expect;

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
      ReactDOMRe.render(<div> "Hello world!"->React.string </div>, container)
    });

    expect(
      container
      // We also provide some basic DOM querying utilities
      // to ease your tests
      ->DOM.findBySelectorAndTextContent("div", "Hello world!")
      ->Js_option.isSome,
    )
    |> toBe(true);
  });
});
//
//describe("Expect", () => {
//  Expect.(test("toBe", () =>
//            expect(1 + 2) |> toBe(3)
//          ))
//});
//
//describe("Expect.Operators", () => {
//  open Expect;
//  open! Expect.Operators;
//
//  test("==", () =>
//    expect(1 + 2) === 3
//  );
//});
