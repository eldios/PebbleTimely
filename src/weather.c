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
};

weather_data *weather_state(void) { return &s_weather; }

void weather_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;
  static char temp_current[] = "N/A  ";
  static char cond_current[] = "0";
  if (weather_state()->current < 900) {
    snprintf(temp_current, sizeof(temp_current), "%d\u00b0", weather_state()->current);
  } else {
    snprintf(temp_current, sizeof(temp_current), "N/A");
  }
  snprintf(cond_current, sizeof(cond_current), "%s", weather_state()->condition);

  setColors(ctx);
  graphics_draw_text(ctx, cond_current, climacons, GRect(2,16,34,34), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  graphics_draw_text(ctx, temp_current, fonts_get_system_font(FONT_KEY_GOTHIC_24), GRect(2,42,36,36), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  if (debug_get()->general) { app_log(APP_LOG_LEVEL_DEBUG, __FILE__, __LINE__, "Weather redrawing: %d, %s", weather_state()->current, weather_state()->condition); }
}
