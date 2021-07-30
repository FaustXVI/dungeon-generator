switch ReactDOM.querySelector("#root") {
| Some(root) => ReactDOM.render(<DungeonGeneratorGui />, root)
| None => () // do nothing
}