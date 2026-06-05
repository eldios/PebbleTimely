# TimelyNG

A calendar watchface for Pebble — current date & time (with optional weather)
up top, a compact 3‑week calendar below, and fully configurable rows of
"complications" you can place where you like.

**Version 0.0.1.**

## Homage & inspiration

TimelyNG is **freely inspired by, and an homage to, the original *Timely* /
*PebbleTimely* watchface and its community forks** — in particular
[Andrew129260/Timely‑2](https://github.com/Andrew129260/Timely-2) and
[alan-johnson/PebbleTimely](https://github.com/alan-johnson/PebbleTimely).
It carries forward their ideas and spirit (the calendar‑centric layout, the
localizable date/time, the complication slots), rebuilt for the modern
Core Devices Pebble SDK and the new hardware. All credit for the original
concept goes to those projects; any bugs here are mine.

## What it shows

- A **status bar** plus two more configurable rows (**above the time** and
  **above the calendar**). Each row holds **one complication (centred) or two
  (side by side)**; empty a row and the freed space goes back to the clock and
  calendar — the layout is adaptive and reflows live when the config changes.
- **Complications** (one shared, alphabetical menu for every slot): date, day,
  month, week number, day‑of‑year / days‑left, seconds, AM/PM, timezone, a
  second time zone, sunrise, sunset, moon phase, weather location, and **watch
  battery, phone battery & Bluetooth**.
- **Weather** (Open‑Meteo, no API key) — condition icon + temperature, sized
  per screen.
- **Battery styles**: a filling bar with the % inside, plain text, icon + text,
  or bar + icon.
- **Calendar**: previous / current / next week, today accented on colour
  watches.
- Vibration (hourly, on disconnect / reconnect), Do‑Not‑Disturb, themes and
  full localization — all from the config screen.

## Platforms

- Pebble Time 2 — `emery`, colour, 200×228
- Pebble 2 Duo / Core 2 Duo — `flint`, black & white, 144×168
- Classic colour / B&W — `basalt`, `diorite`

Round platforms (`chalk` / `gabbro`) are not targeted — the layout is
rectangle‑centric. `aplite` (original 2013 Pebble, 24 KB RAM) is currently
dropped; see [`TODO.md`](TODO.md).

## Building (Nix + official Pebble CLI)

```sh
nix develop                      # pebble CLI + ARM toolchain + emulator
pebble build                     # -> build/TimelyNG.pbw
pebble install --emulator emery  # colour emulator (or basalt / diorite / flint)
```

Build/test exactly as the cloud does (catches the `-Werror`/warnings the local
build relaxes):

```sh
nix develop -c sh tools/test.sh  # host unit tests + build + strict per‑platform compile
```

## Configuration

The settings screen is fully offline: no server, no CDN, no external host. On
`showConfiguration` the watch's PebbleKit JS builds the page from
`src/js/config.js` (the field spec) via `src/js/configpage.js` and hands it to
the phone as a `data:text/html` URI; the page returns the chosen values via
`pebblejs://close#`. Edit `src/js/config.js` to change the options.
