{
  description = "Timely watchface for Pebble - SDK dev shell (official pebble CLI)";

  inputs = {
    pebble.url = "github:pebble-dev/pebble.nix";
    flake-utils.url = "github:numtide/flake-utils";
  };

  # Usage (official Pebble SDK flow, https://developer.repebble.com/sdk/):
  #   nix develop
  #   pebble sdk install latest          # first time only; caches in ~/.pebble-sdk
  #   pebble build                       # produces build/Timely.pbw
  #   pebble install --emulator basalt   # run in the QEMU emulator
  #   pebble login && pebble install --cloudpebble   # push to a paired watch
  outputs =
    { pebble, flake-utils, ... }:
    # Restrict to the systems pebble.nix actually builds for (no aarch64-linux),
    # otherwise per-system access to pebble.* errors out on unsupported hosts.
    flake-utils.lib.eachSystem [
      "x86_64-linux"
      "x86_64-darwin"
      "aarch64-darwin"
    ]
      (system: {
        # Interactive SDK shell: pebble-tool + ARM toolchain + QEMU emulator.
        # Inside it you run the official `pebble` commands listed above.
        devShells.default = pebble.pebbleEnv.${system} {
          emulatorTarget = "basalt";
        };
      });
}
