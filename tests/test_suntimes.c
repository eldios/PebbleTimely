#include "utest.h"
#include "suntimes.h"

// Milan (45.46N, 9.19E), 4 June (yday 154), CEST = UTC+2.
// Real sunrise ~05:33, sunset ~21:01; we allow ~30min (EoT omitted).
UTEST(suntimes, milan_june) {
  float sr, ss;
  sun_times(45.46f, 9.19f, 154, 2.0f, &sr, &ss);
  ASSERT_TRUE(sr > 5.0f && sr < 6.5f);
  ASSERT_TRUE(ss > 20.0f && ss < 21.5f);
  ASSERT_FALSE(sun_is_night(45.46f, 9.19f, 154, 2.0f, 12.0f)); // noon: day
  ASSERT_TRUE(sun_is_night(45.46f, 9.19f, 154, 2.0f, 2.0f));   // 02:00: night
  ASSERT_TRUE(sun_is_night(45.46f, 9.19f, 154, 2.0f, 23.0f));  // 23:00: night
}
