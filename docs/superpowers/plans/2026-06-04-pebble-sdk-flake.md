# Pebble SDK flake (Phase 1) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a `flake.nix` that provides a working Pebble SDK dev shell and a reproducible app-store build for the Timely watchface.

**Architecture:** Consume `github:pebble-dev/pebble.nix` (canonical, Core Devices-based). Expose `devShells.default` via its `pebbleEnv` and `packages.default` via its `buildPebbleApp`, restricted to the systems pebble.nix supports. Pin everything in `flake.lock`.

**Tech Stack:** Nix flakes, flake-utils, pebble.nix (pebble-tool 5.x, arm-none-eabi 4.9.169, Pebble-patched QEMU, sdk-core-4.3).

> **Revision 2026-06-04 — implemented as dev-shell-only.** Tasks 1–2's
> `packages.default` / `buildPebbleApp` were dropped: the official Pebble guide
> builds via the `pebble` CLI (not Nix), and `buildPebbleApp` is broken at
> pebble.nix HEAD (`51f2a26` references the removed `python-libs.nix`). The
> shipped `flake.nix` exposes only `devShells.default`. Task 4's reproducible
> `nix build` is replaced by the official `pebble build` inside `nix develop`,
> which was verified to compile the source (failing only on `-Werror`
> `-Wformat-truncation` warnings in `src/Timely.c` — Phase 2 scope). See the
> design doc's "Revision 2026-06-04" section.

---

### Task 1: Create `flake.nix`

**Files:**
- Create: `flake.nix`

- [ ] **Step 1: Write `flake.nix`**

```nix
{
  description = "Timely watchface for Pebble - SDK dev shell and reproducible build";

  inputs = {
    pebble.url = "github:pebble-dev/pebble.nix";
    flake-utils.url = "github:numtide/flake-utils";
  };

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
        # Drives Phase 2 development (`pebble build`, `pebble install --emulator`).
        devShells.default = pebble.pebbleEnv.${system} {
          emulatorTarget = "basalt";
        };

        # Reproducible app-store build: produces Timely.pbw + meta.yml +
        # appstore-bundle.tar.gz. Screenshot is a bootstrap placeholder
        # (an existing repo asset) until a real emulator screenshot is added
        # in Phase 3 before publishing.
        packages.default = pebble.buildPebbleApp.${system} {
          name = "Timely";
          type = "watchface";
          src = ./.;

          description = ''
            A watchface for the Pebble. It shows the current date and time in the
            top half, optionally with weather conditions and temperature, and a
            small 3-week calendar in the bottom half. The status bar shows
            connection, charging and battery level. Text and date formats are
            fully localizable through the configuration screen, with options such
            as per-hour and link-lost/regained vibration.
          '';

          releaseNotes = ''
            2.6 rebuilt against the modern Pebble SDK. Includes the leap-year
            day-of-year fix, weather battery-usage improvements, and
            OpenWeatherMap appid support.
          '';

          screenshots = {
            all = [ "resources/images/menu_icon_timely.png" ];
          };
        };
      });
}
```

- [ ] **Step 2: Commit**

```bash
git add flake.nix
git commit --no-gpg-sign -m "build(nix): add flake for Pebble SDK dev shell and reproducible build"
```

---

### Task 2: Generate and commit `flake.lock`, validate evaluation

**Files:**
- Create: `flake.lock`

- [ ] **Step 1: Generate the lock file**

Run: `nice -n 19 nix flake lock`
Expected: creates `flake.lock` pinning `pebble`, `flake-utils`, and the transitive `nixpkgs`.

- [ ] **Step 2: Evaluate the flake**

Run: `nice -n 19 nix flake check 2>&1 | tail -30`
Expected: no evaluation errors. (Build of `packages.default` is exercised in Task 4, not here.)

- [ ] **Step 3: Commit the lock**

```bash
git add flake.lock
git commit --no-gpg-sign -m "build(nix): pin flake inputs (pebble.nix toolchain) in flake.lock"
```

---

### Task 3: Verify the dev shell

**Files:** none (verification only)

- [ ] **Step 1: Confirm pebble-tool resolves in the shell**

Run: `nice -n 19 nix develop --command pebble --version 2>&1 | tail -20`
Expected: prints a pebble-tool 5.x version string. First run is slow (builds/downloads the toolchain closure).

- [ ] **Step 2: Confirm the ARM toolchain is on PATH**

Run: `nice -n 19 nix develop --command arm-none-eabi-gcc --version 2>&1 | tail -5`
Expected: prints a gcc 4.9.x version (arm-none-eabi).

---

### Task 4: Verify the reproducible build (with Phase-2 boundary)

**Files:** none (verification only)

- [ ] **Step 1: Build the package**

Run: `nice -n 19 nix build .#packages.x86_64-linux.default 2>&1 | tail -40`

- [ ] **Step 2: Interpret the result against the Phase-1 boundary**

- If it succeeds: `result/Timely.pbw`, `result/meta.yml`, and
  `result/appstore-bundle.tar.gz` exist. Confirm with
  `ls -l result/`. Phase 1 fully done.
- If it fails **inside the C compile** (`pebble build` reached the compiler and
  the legacy source errors out under SDK 4.x): the flake/SDK plumbing is proven
  and Phase 1 is complete; the compile errors are Phase 2 scope. Record the
  first compiler error verbatim for the Phase 2 spec — do NOT patch C source
  here.
- If it fails **before** reaching the compiler (eval error, missing input,
  pebble-tool not found, SDK setup error): that is a Phase 1 flake bug — fix
  `flake.nix` and re-run.

---

## Self-Review

- **Spec coverage:** devShell (`pebbleEnv`, `emulatorTarget=basalt`) → Task 1/3.
  Reproducible build (`buildPebbleApp` with name/type/src/description/
  releaseNotes/screenshots placeholder) → Task 1/4. `flake.lock` pin → Task 2.
  System restriction rationale → Task 1 comment. Phase-1-vs-Phase-2 boundary on
  source compile → Task 4 Step 2. All spec Phase-1 items covered.
- **Placeholder scan:** no TBD/TODO; `flake.nix` content is complete; the
  "screenshot placeholder" is an intentional, named bootstrap (real repo file),
  not a plan placeholder.
- **Consistency:** `pebble.pebbleEnv.${system}` and
  `pebble.buildPebbleApp.${system}` match the verified pebble.nix output names;
  attribute names (`emulatorTarget`, `name`, `type`, `src`, `description`,
  `releaseNotes`, `screenshots`) match the verified `buildPebbleApp`/`pebbleEnv`
  signatures.
