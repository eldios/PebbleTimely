#include "weather.h"

// Single owner of the weather state (default: 999 = "N/A", 'h' = updating glyph).
static weather_data s_weather = {
  .current   = 999,
  .condition = {'h'},
  .requests  = 0,
  .failures  = 0,
};

weather_data *weather_state(void) { return &s_weather; }
