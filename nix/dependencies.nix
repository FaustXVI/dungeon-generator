with import ./channel.nix;
let
  tcrdd = callPackage (fetchFromGitHub {
    owner = "FaustXVI";
    repo = "tcrdd";
    rev= "fa03c75921e2b628a8da4a9ec8bfe02e300500fd";
    sha256 = "036i40r7qp1ncsb9zr2pbpfwq1blbg2fpn5qcsr64952nh788nx3";
    fetchSubmodules = true;
  }) { nixpkgs = import ./channel.nix; };
  dependencies = rec {
    devTools = [ 
      tcrdd
      git
      nixops
      nodejs
      nodePackages.node2nix
    ];
    runtime = [
      nodejs
    ];
    all = dependencies.devTools
    ++ dependencies.runtime
    ;
  };
in dependencies
