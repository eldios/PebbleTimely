#include "utest.h"
#include "calendar.h"

// Thu June 4 2026, Sunday start, 1 week before + 1 after.
// Matches the emulator screenshot: 24..30 / 31,1..6 / 7..13, today=4.
UTEST(calendar, june_2026_sunday_start) {
  CalGrid g = calendar_build(2026, 5, 4, 4, 0, 0);
  ASSERT_EQ(4, g.special_col);
  ASSERT_EQ(2, g.special_row);
  ASSERT_EQ(24, g.days[0]);
  ASSERT_EQ(30, g.days[6]);
  ASSERT_EQ(31, g.days[7]);
  ASSERT_EQ(4,  g.days[11]);
  ASSERT_EQ(6,  g.days[13]);
  ASSERT_EQ(7,  g.days[14]);
  ASSERT_EQ(13, g.days[20]);
}

UTEST(calendar, monday_start_offset) {
  CalGrid g = calendar_build(2026, 5, 4, 4, 1, 0);
  ASSERT_EQ(3, g.special_col);
  ASSERT_EQ(1, g.days[7]);   // Monday Jun 1 starts the week row
  ASSERT_EQ(4, g.days[10]);  // today
}

UTEST(calendar, sunday_with_monday_start_wraps_to_last_col) {
  CalGrid g = calendar_build(2026, 5, 7, 0, 1, 0);
  ASSERT_EQ(6, g.special_col); // Sunday is the last column under Monday start
}
