#!/usr/bin/env bash
node2nix -l package-lock.json --development --output ./nix/registry.nix --composition ./nix/composition.nix --node-env ./nix/node-env.nix
