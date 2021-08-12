{pkgs, system, nodejs}:
let
  nodeNix = (import ./composition.nix {inherit pkgs system nodejs;});
in
  nodeNix // { 
    nodeDependencies = nodeNix.nodeDependencies.override {
      buildInputs = with pkgs; [
        pkgs.nodePackages.node-gyp-build
        pkgconfig
      ];
      preRebuild = ''
        echo preRebuild
          sed -i 's:./configure.py --bootstrap:python3 ./configure.py --bootstrap:' node_modules/rescript/scripts/install.js
      '';
    };
  }
