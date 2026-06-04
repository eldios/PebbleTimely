# Design: Pebble SDK flake + republish path for Timely watchface

Date: 2026-06-04
Status: approved (design), pending implementation
Scope of this spec: **Phase 1 — `flake.nix`**. Phases 2–3 are sketched for
context and get their own spec/plan before implementation.

## Problem

`PebbleTimely` (the "Timely" watchface) is an old Pebble SDK 3 project using the
legacy build format (`wscript` + `appinfo.json`), targeting `aplite` + `basalt`.
It no longer builds on a modern machine because the original Pebble SDK is gone.
We want a reproducible, NixOS-friendly SDK environment, then to modernise the
code and **republish the updated app to the Rebble app store**, including the new
Core Devices hardware.

## Verified ecosystem state (mid-2026)

- **Core Devices** is the canonical, actively-maintained source after Google
  open-sourced PebbleOS in 2025. CLI: `coredevices/pebble-tool` (PyPI
  `pebble-tool`, latest 5.0.36), Python 3.10–3.13. Docs: developer.repebble.com.
- The current SDK is a Python-3-packaged **SDK 4.3**; it still builds the legacy
  `appinfo.json` + `wscript` format, so no migration is required just to compile.
- Canonical Nix integration: **`github:pebble-dev/pebble.nix`** (Sorixelle),
  updated 2026-06-01, already migrated to Core Devices' pebble-tool. It pins:
  - `pebble-tool` 5.0.35, ARM toolchain `arm-none-eabi` 4.9.169
    (`sdk.repebble.com`), a Pebble-patched QEMU, and `sdk-core-4.3`
    (`binaries.rebble.io`).
  - Exposes `pebbleEnv` (dev shell) and `buildPebbleApp` (reproducible
    app-store build).
- Platforms: `aplite`, `basalt`, `chalk`, `diorite`, `emery`.

Sources: github.com/coredevices/pebble-tool, pypi.org/project/pebble-tool,
developer.repebble.com/sdk, github.com/Sorixelle/pebble.nix.

## Decisions

- Consume `pebble.nix` rather than hand-rolling toolchain/QEMU derivations.
- The flake provides **both** an interactive dev shell and a reproducible build.
- Final target hardware includes the **new Pebbles (diorite/emery)** in addition
  to the legacy aplite/basalt — this is Phase 2 work (lives in `appinfo.json`/
  `package.json`, not the flake).
- We will **republish** to the Rebble app store, so the reproducible build uses
  the app-store-oriented `buildPebbleApp` (which mandates store metadata),
  not a bare `.pbw` derivation.

## Phase 1 architecture — `flake.nix`

Single new file `flake.nix` at repo root. Per-system via `flake-utils`.

### Inputs
```nix
pebble.url      = "github:pebble-dev/pebble.nix";
flake-utils.url = "github:numtide/flake-utils";
```

### Outputs (per system, `flake-utils.lib.eachDefaultSystem`)

1. `devShells.default = pebble.pebbleEnv.${system} { emulatorTarget = "basalt"; };`
   - Brings `pebble-tool`, ARM toolchain, QEMU, nodejs onto PATH.
   - Enables `pebble build`, `pebble install --emulator basalt`, `pebble login`,
     `pebble screenshot`. This is the Phase 2 development driver.

2. `packages.default = pebble.buildPebbleApp.${system} { ... };`
   Required metadata supplied:
   - `name = "Timely"`
   - `type = "watchface"`
   - `src = ./.`
   - `description` = paragraph from `README`
   - `releaseNotes` = current release summary (from git history / version 2.6)
   - `screenshots = { all = [ "resources/images/menu_icon_timely.png" ]; };`
     — **bootstrap placeholder** (an existing repo file) to satisfy the
     `≥1 screenshot` assertion so `nix build` works today. Replaced with a real
     emulator screenshot in Phase 3 before publishing.
   Produces `$out/Timely.pbw`, `$out/meta.yml`, `$out/appstore-bundle.tar.gz`.

### `flake.lock`
Committed, pinning the full toolchain transitively via `pebble.nix` for
bit-reproducible builds across machines.

### Why this split
`targetPlatforms` and the `sdkVersion 3→4` bump live in `appinfo.json`, not the
flake. The flake supplies the toolchain for all platforms regardless; keeping the
platform list out of the flake keeps Phase 1 independent of Phase 2.

## Phase 1 — components / boundaries

| Unit | Purpose | Depends on |
|------|---------|------------|
| `flake.nix` inputs | pin pebble.nix + flake-utils | upstream flakes |
| `devShells.default` | interactive SDK shell | `pebble.pebbleEnv` |
| `packages.default` | reproducible app-store build | `pebble.buildPebbleApp`, repo metadata |
| `flake.lock` | reproducibility pin | all inputs |

## Phase 1 — testing / verification

- `nix flake check` parses and evaluates.
- `nix develop` enters the shell; `pebble --version` resolves; `pebble build`
  runs against the existing source (legacy format) and produces a `.pbw` for the
  currently-listed platforms.
- `nix build` produces `result/Timely.pbw` (+ `meta.yml`, bundle).
- All heavy nix commands run under `nice -n 19`.

Note: the existing C source may not compile cleanly under SDK 4.x without Phase 2
fixes. If `pebble build` surfaces source errors, Phase 1 is still complete once
the SDK/flake plumbing is proven (shell loads, toolchain resolves, build reaches
the compiler); source fixes belong to Phase 2. This boundary is recorded so a
non-clean `pebble build` of legacy code is not mistaken for a flake failure.

## Phase 2 (sketch — separate spec/plan)

Adapt the code to SDK 4.x and new hardware: bump `sdkVersion 3→4` (or convert to
`package.json` via `pebble convert-project`), add `diorite`/`emery` to
`targetPlatforms`, fix compilation under modern toolchain, handle display size /
color differences for the new screens. Iterated in the dev shell.

## Phase 3 (sketch — separate spec/plan)

Republish: capture real per-platform screenshots from the emulator, finalise
app-store metadata (description, releaseNotes, icons, banner), bump version, and
upload the `appstore-bundle.tar.gz`.

## Out of scope (Phase 1)

- Any change to C source, resources, or `appinfo.json`.
- Adding new target platforms (that is `appinfo.json`, Phase 2).
- Real screenshots / final store metadata (Phase 3).
