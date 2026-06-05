# TODO

Future work for TimelyNG. Roughly ordered by priority.

## Platforms
- **Re-add `aplite`** (original 2013 Pebble, 24 KB app RAM). It was dropped
  because the current feature set no longer fits (≈19 KB of code leaves almost
  no heap, so it faulted on launch). Bringing it back needs an aplite-specific
  code diet behind `#ifdef PBL_PLATFORM_APLITE` — trim optional complications,
  extra icons and large fonts — and a build there that runs without faulting
  before it goes back into `package.json` `targetPlatforms`.
- **Round platforms** (`chalk`, `gabbro`). The layout is rectangle-centric;
  a round variant would need its own geometry in `layout.c`.

## Code cleanup
- **Remove the retired middle `day_layer`** complication slot. It is always
  hidden (the row model is now left/right only) but still created, themed and
  destroyed; also drop the now-unused `show_day` setting + `AK_STYLE_DAY`
  handling and the `STAT_BT_ICON_*` defines left over from the old fixed BT icon.

## Features / polish
- More complications (e.g. step count / health, a configurable text label).
- Per-complication formatting options where it makes sense.
- Revisit weather error/backoff behaviour for flaky phone links.

## Project / infra
- **Add a `LICENSE`** (the upstream Timely/PebbleTimely license should be
  checked and honoured; pick a compatible one).
- **CI: add the full SDK build** (per-platform `pebble build` + `tools/test.sh`
  strict-check) once a stable Core Devices Pebble SDK container image is
  available. CI currently runs the host unit tests + JS syntax check.
- Add appstore screenshots/banner under a `marketing/` folder (see
  `PUBLISHING.md`).

## Known limitations
- The weather location name is only shown when picked as the "Location"
  complication; there is no automatic fallback display.
