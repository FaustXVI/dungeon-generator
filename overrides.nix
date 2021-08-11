{pkgs, system, nodejs}:
let
  dependencies = import ./nix/dependencies.nix;
  nodeNix = (import ./nix/composition.nix {inherit pkgs system nodejs;});
in
  nodeNix // { 
    "@parcel" = nodeNix."@parcel".override(oldAttrs: {
      buildInputs = oldAttrs.buildInputs ++ [nodepackages.node-gyp-build];
    });
    rescript = nodeNix.rescript.override(oldAttrs: {
      preRebuild = ''
          sed -i 's:./configure.py --bootstrap:python3 ./configure.py --bootstrap:' ./scripts/install.js
      '';
    }); };

