{
  description = "Timely watchface for Pebble - SDK dev shell + host unit tests";

  inputs = {
    pebble.url = "github:pebble-dev/pebble.nix";
    flake-utils.url = "github:numtide/flake-utils";
    # Reuse pebble.nix's pinned nixpkgs (no extra fetch) for host tooling/tests.
    nixpkgs.follows = "pebble/nixpkgs";
  };

  # Usage (official Pebble SDK flow, https://developer.repebble.com/sdk/):
  #   nix develop
  #   pebble sdk install latest          # first time only; caches in ~/.pebble-sdk
  #   pebble build                       # produces build/Timely.pbw
  #   pebble install --emulator basalt   # run in the QEMU emulator
  #   pebble login && pebble install --cloudpebble   # push to a paired watch
  # Host unit tests (pure logic in src/, no Pebble SDK):
  #   nix flake check                          # reproducible, CI
  #   nix develop .#test --command just test   # or: make test
  # Tests live in a SEPARATE shell on purpose: a host C compiler in the pebble
  # shell hijacks the ARM cross-build ("gcc: unrecognized option -mthumb").
  outputs =
    { nixpkgs, pebble, flake-utils, ... }:
    # Restrict to the systems pebble.nix actually builds for (no aarch64-linux),
    # otherwise per-system access to pebble.* errors out on unsupported hosts.
    flake-utils.lib.eachSystem [
      "x86_64-linux"
      "x86_64-darwin"
      "aarch64-darwin"
    ]
      (
        system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in
        {
          # Pebble SDK shell: pebble CLI + ARM toolchain + QEMU emulator, plus
          # just/make task runners. No host cc here: it would hijack the ARM
          # cross-build. Run the unit tests from devShells.test instead.
          devShells.default = pebble.pebbleEnv.${system} {
            emulatorTarget = "basalt";
            packages = [
              pkgs.just
              pkgs.gnumake
            ];
          };

          # Host shell for the unit tests: C compiler + just/make.
          devShells.test = pkgs.mkShell {
            packages = [
              pkgs.gcc
              pkgs.gnumake
              pkgs.just
            ];
          };

          # Reproducible host run of the pure-logic unit tests (no Pebble SDK).
          checks.default = pkgs.runCommandCC "timefmt-tests" { } ''
            mkdir -p src tests
            cp ${./src/timefmt.c} src/timefmt.c
            cp ${./src/timefmt.h} src/timefmt.h
            cp ${./tests/test_timefmt.c} tests/test_timefmt.c
            cp ${./tests/utest.h} tests/utest.h
            cc -I src -I tests -Wall -Wextra -std=c11 \
              tests/test_timefmt.c src/timefmt.c -o test_timefmt
            ./test_timefmt
            touch $out
          '';
        }
      );
}
