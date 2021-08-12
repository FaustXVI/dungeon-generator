with import ./nix/channel.nix;
let
  dependencies = import ./nix/dependencies.nix;
  nodeModules = (import ./nix/overrides.nix {inherit pkgs system nodejs;}).nodeDependencies;
in stdenv.mkDerivation {
  name = "dungeon-generator";
  buildInputs = dependencies.devTools;
  src = nix-gitignore.gitignoreSource [] ./. ;
  installPhase = ''
          mkdir -p $out
          cp -r ${nodeModules}/lib/node_modules ./node_modules
          chmod 700 -R ./node_modules
          export HOME=$(mktemp -d)
          npm run buildProd
          cp -r dist/* $out
  '';
}

