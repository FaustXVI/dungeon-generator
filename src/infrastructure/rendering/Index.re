[@bs.val] external document: Js.t({..}) = "document";

let makeContainer = () => {
  let container = document##createElement("div");
  container##className #= "container";
  let () = document##body##appendChild(container);
  container;
};

ReactDOMRe.render(<DungeonGeneratorGui />, makeContainer());
