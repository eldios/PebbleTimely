#include "utest.h"
#include "vibes.h"

UTEST(vibes, single_day_window) {
  ASSERT_TRUE(period_contains(60, 120, 90, false));   // 10:00-20:00, now 15:00
  ASSERT_FALSE(period_contains(60, 120, 30, false));  // now 05:00, outside
  ASSERT_TRUE(period_contains(60, 120, 60, false));   // inclusive start
  ASSERT_TRUE(period_contains(60, 120, 120, false));  // inclusive stop
}
UTEST(vibes, wraps_midnight) {
  ASSERT_TRUE(period_contains(132, 36, 138, false));  // 22:00-06:00, now 23:00
  ASSERT_TRUE(period_contains(132, 36, 12, false));   // now 02:00
  ASSERT_FALSE(period_contains(132, 36, 72, false));  // now 12:00, outside
}
UTEST(vibes, equal_start_stop_returns_flag) {
  ASSERT_FALSE(period_contains(60, 60, 90, false));
  ASSERT_TRUE(period_contains(60, 60, 90, true));
}
