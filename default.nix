with import ./nix/channel.nix;
let
  dependencies = import ./nix/dependencies.nix;
#  nodeDependencies = (pkgs.callPackage ./nix/composition.nix {inherit pkgs system nodejs;}).package;
  #{

  #      # Fix paths so we can use a cached Ninja, instead of compiling it
  #      preInstall = ''
  #        echo prebuild
  #        pwd
  #        sed -i 's:./configure.py --bootstrap:python3 ./configure.py --bootstrap:' ./scripts/install.js
  #        fail
  #      '';

  #  };
    nodeModules = stdenv.mkDerivation {
      name = "dungeon-generator";
      buildInputs = dependencies.devTools;
      #src = nix-gitignore.gitignoreSource [] ./. ;
      src =  ./. ;
        #ln -s ${nodeDependencies}/lib/node_modules ./node_modules
        #export PATH="${nodeDependencies}/bin:$PATH"
        #echo "${nodeDependencies}"
        #export HOME=$(mktemp -d)
        #mkdir $out
        #npm run build
      installPhase = ''
        mkdir -p $out
        cp -r dist/* $out
      '';
    };
in nodeModules

