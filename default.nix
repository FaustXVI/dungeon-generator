with import ./nix/channel.nix;
let
  dependencies = import ./nix/dependencies.nix;
  nodeNix = (import ./nix/composition.nix {inherit pkgs system nodejs;});
  test =  nodeNix // { 
    shell = nodeNix.shell.override {
      buildInputs = with pkgs; [
        pkgs.nodePackages.node-gyp-build
        pkgconfig
      ];
      preRebuild = ''
        echo preRebuild
          sed -i 's:./configure.py --bootstrap:python3 ./configure.py --bootstrap:' node_modules/rescript/scripts/install.js
      '';
    };
  };
  nodeDependencies = test.shell.nodeDependencies;
  nodeModules = stdenv.mkDerivation {
    name = "dungeon-generator";
    buildInputs = dependencies.devTools;
    src = nix-gitignore.gitignoreSource [] ./. ;
    installPhase = ''
          mkdir -p $out
          cp -r ${nodeDependencies}/lib/node_modules ./node_modules
          chmod 777 -R ./node_modules
          export PATH="./node_modules/.bin:$PATH"
          export HOME=$(mktemp -d)
          npm run buildProd
          cp -r dist/* $out
    '';
  };
in nodeModules

