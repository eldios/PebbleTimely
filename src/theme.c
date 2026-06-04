#include "theme.h"
#include "ui.h"        // window, currentTime
#include "settings.h"  // settings_get()->theme / theme_mode

// Palettes: [theme][0=light, 1=dark]. Tune these via emulator screenshots.
static const Palette PALETTES[THEME_COUNT][2] = {
  // THEME_MONO — pure black & white (the Pebble 2 Duo look, even on color)
  { { GColorWhite, GColorBlack, GColorBlack, GColorWhite, GColorBlack, GColorBlack, GColorWhite },
    { GColorBlack, GColorWhite, GColorWhite, GColorBlack, GColorWhite, GColorWhite, GColorBlack } },
  // THEME_FUNCTIONAL — color carries meaning (today / weekend / warn)
  { { GColorWhite, GColorBlack, GColorJaegerGreen, GColorWhite, GColorRed,  GColorRed, GColorLightGray },
    { GColorBlack, GColorWhite, GColorJaegerGreen, GColorWhite, GColorMelon, GColorRed, GColorDarkGray } },
  // THEME_MINIMAL — monochrome + a single accent
  { { GColorWhite, GColorBlack, GColorBlue,          GColorWhite, GColorBlack, GColorBlack, GColorWhite },
    { GColorBlack, GColorWhite, GColorVividCerulean, GColorBlack, GColorWhite, GColorWhite, GColorBlack } },
  // THEME_VIBRANT — bold flat colors
  { { GColorWhite,      GColorBlack, GColorOrange,       GColorWhite, GColorMagenta,       GColorRed, GColorPastelYellow },
    { GColorOxfordBlue, GColorWhite, GColorChromeYellow, GColorBlack, GColorBrilliantRose, GColorRed, GColorDukeBlue } },
};

static bool is_night(void) {
  // Placeholder for AUTO mode: dark 19:00-06:59. Upgraded to sunset/sunrise next.
  if (!currentTime) return true;
  int h = currentTime->tm_hour;
  return (h >= 19 || h < 7);
}

Palette theme_palette(void) {
  uint8_t theme = settings_get()->theme;
  if (theme >= THEME_COUNT) theme = THEME_FUNCTIONAL;
  uint8_t mode = settings_get()->theme_mode;
  int dark = (mode == THEME_MODE_DARK) || (mode == THEME_MODE_AUTO && is_night());
  return PALETTES[theme][dark ? 1 : 0];
}

void setColors(GContext* ctx) {
  Palette p = theme_palette();
  window_set_background_color(window, p.bg);
  graphics_context_set_stroke_color(ctx, p.fg);
  graphics_context_set_fill_color(ctx, p.bg);
  graphics_context_set_text_color(ctx, p.fg);
}

void setInvColors(GContext* ctx) {
  Palette p = theme_palette();
  window_set_background_color(window, p.fg);
  graphics_context_set_stroke_color(ctx, p.bg);
  graphics_context_set_fill_color(ctx, p.fg);
  graphics_context_set_text_color(ctx, p.bg);
}

void setTodayColors(GContext* ctx) {
  Palette p = theme_palette();
  window_set_background_color(window, p.bg);
  graphics_context_set_stroke_color(ctx, p.accent_fg);
  graphics_context_set_fill_color(ctx, p.accent);
  graphics_context_set_text_color(ctx, p.accent_fg);
}
