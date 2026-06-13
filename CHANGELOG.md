# Changelog

All notable changes to TimelyNG. Format loosely follows
[Keep a Changelog](https://keepachangelog.com/). The entry below is also the
text to paste into the **Release notes** field when uploading the `.pbw` to the
[Rebble developer portal](https://dev-portal.rebble.io/) (it is not embedded in
the build, so the portal does not auto-fill it). The store **Description** lives
in [`PUBLISHING.md`](PUBLISHING.md).

## 0.0.2

- Settings are now WYSIWYG: saving the config page applies **every** value it
  shows, not only the ones you touched. Previously the page sent just the keys
  that changed against a phone-side baseline; when that baseline had drifted from
  the watch (reinstall, a different phone, or defaults that never matched), a
  setting shown in the page but left untouched was silently never applied — so
  e.g. a complication could read "Location" in the settings yet stay "Date" on
  the watch. Every non-translation setting is now always sent. Translation
  strings stay delta-only (they are bulk and must fit the watch's message inbox);
  the language picker resends them when it changes them.
- Config page defaults now match the watch's firmware defaults (the
  above-calendar Week and AM/PM slots, low-battery threshold), so a fresh install
  shows the watch's real out-of-box state before the first save.
- Coloured weather icons on colour watches (basalt, emery): the condition glyph
  is tinted by meaning — sun amber, rain/snow blue, lightning amber, moon pale
  yellow — while the temperature keeps the theme colour. Black-and-white watches
  (diorite, flint) and the Mono theme are unchanged.

## 0.0.1 — first public release

- Configurable complication rows (status bar, above the time, above the
  calendar) — one centred or two side by side per row.
- One shared, alphabetical menu for every slot, including watch/phone battery,
  Bluetooth and the date itself.
- Adaptive layout that reflows live on save; the clock font auto-scales.
- Battery styles: filling bar with the % inside, text, icon + text, or bar +
  icon.
- Open-Meteo weather (no API key); fully offline configuration.
- Builds for Pebble Time 2 (emery), Pebble 2 Duo (flint), basalt and diorite.

Freely inspired by, and an homage to, the original Timely / PebbleTimely and the
Timely-2 and PebbleTimely community forks.
