with import ./nix/channel.nix;

let
  dependencies = import ./nix/dependencies.nix;
in stdenv.mkDerivation {
  name = "dungeon-env";
  buildInputs = dependencies.all;
}
