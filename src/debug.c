#include "debug.h"
// All debugging disabled by default.
static persist_debug s_debug = {
  .general = false, .language = false,
  .reserved_1 = false, .reserved_2 = false,
  .reserved_3 = false, .reserved_4 = false,
};
persist_debug *debug_get(void) { return &s_debug; }
