let
  generator = import ../..;
in {
  network.description = "Web server";

  webserver =
    { config, pkgs, ... }: {
      services = {
        httpd = {
          enable = true;
          adminAddr = "xavier@example.org";
          virtualHosts.localhost.documentRoot = "${generator}";
        };
      };
      networking.firewall.allowedTCPPorts = [ 80 ];
    };
  }
