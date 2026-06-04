#pragma once
#include <pebble.h>
// Color roles for a single resolved palette. On 1-bit platforms colors degrade
// to black/white automatically.
typedef struct {
  GColor bg;        // background
  GColor fg;        // primary text / stroke
  GColor accent;    // today highlight / key accent
  GColor accent_fg; // text drawn on the accent
  GColor weekend;   // weekend day color (functional theme)
  GColor warn;      // low battery / alert
  GColor grid;      // calendar grid background patch
} Palette;

enum { THEME_MONO = 0, THEME_FUNCTIONAL = 1, THEME_MINIMAL = 2, THEME_VIBRANT = 3, THEME_COUNT };
enum { THEME_MODE_LIGHT = 0, THEME_MODE_DARK = 1, THEME_MODE_AUTO = 2 };

// The active palette, resolved from settings (theme + mode; AUTO uses night).
Palette theme_palette(void);

// Apply palette roles to a graphics context (and the window background):
void setColors(GContext* ctx);     // base: bg + fg
void setInvColors(GContext* ctx);  // swapped patch: fg-on-bg
void setTodayColors(GContext* ctx);// accent
