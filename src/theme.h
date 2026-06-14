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
// Weather icon style (adv_settings.weather_icons): Default follows the platform
// and the Mono theme; Colour/B&W force it regardless.
enum { WEATHER_ICONS_DEFAULT = 0, WEATHER_ICONS_COLOUR = 1, WEATHER_ICONS_BW = 2 };

// The active palette, resolved from settings (theme + mode; AUTO uses night).
Palette theme_palette(void);

// Apply palette roles to a graphics context (and the window background):
void setColors(GContext* ctx);     // base: bg + fg
void setInvColors(GContext* ctx);  // swapped patch: fg-on-bg
void setTodayColors(GContext* ctx);// accent

// Meaningful tint for a Climacons weather glyph (sun yellow, rain blue, …),
// honouring the weather_icons setting. Returns the palette fg (monochrome) on
// 1-bit watches, when B&W is forced, or under Default + the Mono theme.
GColor weather_glyph_color(char glyph);
