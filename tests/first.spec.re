open Jest;
open Expect;
open ReactTestingLibrary;
open Webapi;

describe("My basic test", () => {
  test("can render DOM elements", () => {
    <TestWrapper testId="greet"> <Greeting name="Commander" /> </TestWrapper>
    |> render
    |> getByTestId(~matcher=`Str("greet"))
    |> Dom.Element.textContent
    |> expect
    |> toBe("Greetings Commander!")
  })
});
