with import ./nix/channel.nix;
let
  dependencies = import ./nix/dependencies.nix;
  nodeModules = stdenv.mkDerivation {
    name = "dungeon-generator-node-modules";
    buildInputs = dependencies.devTools;
    outputHashAlgo = "sha256";
    outputHashMode = "recursive";
    outputHash = "1m0h4km3bbj31dcwns0ir0773vdva45rry4b9lhacjyxr3k5h67z";
    src = nix-gitignore.gitignoreSource [] ./. ;
    installPhase = ''
      export HOME=$(mktemp -d)
      mkdir $out
      npm ci
      mv node_modules $out
    '';
  };
in nodeModules

