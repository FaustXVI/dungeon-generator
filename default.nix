with import ./nix/channel.nix;
let
  dependencies = import ./nix/dependencies.nix;
  nodeNix = (import ./nix/composition.nix {inherit pkgs system nodejs;});
    nodeDependencies = nodeNix.package;
    nodeModules = stdenv.mkDerivation {
      name = "dungeon-generator";
      buildInputs = dependencies.devTools;
      src = nix-gitignore.gitignoreSource [] ./. ;
      installPhase = ''
          mkdir -p $out
          cp -r ${nodeDependencies}/lib/node_modules/my-react-app/node_modules ./node_modules
          chmod 777 -R ./node_modules
          export PATH="./node_modules/.bin:$PATH"
          export HOME=$(mktemp -d)
          npm run buildProd
          cp -r dist/* $out
      '';
    };
in nodeModules

