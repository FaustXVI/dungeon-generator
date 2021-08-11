{
  webserver =
    { config, pkgs, ... }: { 
      deployment= {
        targetEnv = "virtualbox";
        virtualbox = {
          memorySize = 1024; # megabytes
          vcpu = 1; # number of cpus
          headless = true;
        };
      };
    };
  }
