#include "weather.h"
#include "theme.h"
#include "debug.h"
#include "ui.h"

// Single owner of the weather state (default: 999 = "N/A", 'h' = updating glyph).
static weather_data s_weather = {
  .current   = 999,
  .condition = {'h'},
  .requests  = 0,
  .failures  = 0,
  .city      = "",
};

weather_data *weather_state(void) { return &s_weather; }

static Layer *s_weather_layer;
static bool s_compact = false; // narrow screens (144px): smaller glyph + temperature

void weather_set_compact(bool compact) { s_compact = compact; }

static void weather_render(Layer *me, GContext *ctx) {
  static char temp_current[12] = "N/A";
  static char cond_current[4] = "0";
  if (weather_state()->current < 900) {
    snprintf(temp_current, sizeof(temp_current), "%d°", weather_state()->current);
  } else {
    snprintf(temp_current, sizeof(temp_current), "N/A");
  }
  cond_current[0] = weather_state()->condition[0]; // single climacons glyph
  cond_current[1] = '\0';

  setColors(ctx);
  // The layer IS the time band. Top-align the icon-over-temperature block so it
  // sits level with the clock (which is also top-aligned) and never spills past
  // the band into the calendar below.
  GFont temp_font = fonts_get_system_font(s_compact ? FONT_KEY_GOTHIC_18 : FONT_KEY_GOTHIC_24);
  // gap = where the temperature sits below the icon's top; the climacons glyph
  // renders well inside its box, so pull the temperature up tight against it.
  int gap    = s_compact ? 18 : 21;
  int temp_h = s_compact ? 18 : 22;
  int band_h = layer_get_bounds(me).size.h;
  int top = 2;
  if (top + gap + temp_h > band_h) { top = band_h - gap - temp_h; if (top < 0) { top = 0; } }
  graphics_draw_text(ctx, cond_current, climacons, GRect(2, top, 34, 36), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  graphics_draw_text(ctx, temp_current, temp_font, GRect(2, top + gap, 36, temp_h + 8), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  if (debug_get()->general) { app_log(APP_LOG_LEVEL_DEBUG, __FILE__, __LINE__, "Weather redrawing: %d, %s", weather_state()->current, weather_state()->condition); }
}

void weather_create(Layer *parent, GRect frame) {
  s_weather_layer = layer_create(frame);
  layer_set_update_proc(s_weather_layer, weather_render);
  layer_add_child(parent, s_weather_layer);
}
void weather_destroy(void)            { layer_destroy(s_weather_layer); }
void weather_set_frame(GRect frame)   { layer_set_frame(s_weather_layer, frame); }
void weather_set_hidden(bool hidden)  { layer_set_hidden(s_weather_layer, hidden); }
void weather_mark_dirty(void)         { layer_mark_dirty(s_weather_layer); }
