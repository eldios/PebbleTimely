#include "utest.h"
#include "layout.h"

// Default layout_compute() = all three rows present (TOP + CENTER + BOTTOM).
UTEST(layout, all_rows_144x168) {
  TimelyLayout L = layout_compute(144, 168);
  ASSERT_EQ(0,   L.statusbar.y);  ASSERT_EQ(24, L.statusbar.h);
  ASSERT_EQ(144, L.statusbar.w);
  ASSERT_EQ(24,  L.slot_top.y);   ASSERT_EQ(88, L.slot_top.h);  // center 26 + time 40 + bottom 22
  ASSERT_EQ(112, L.slot_bot.y);   ASSERT_EQ(56, L.slot_bot.h);  // 168-24-88
  ASSERT_EQ(7,   L.cal_cols);
  ASSERT_EQ(20,  L.cal_cell_w);   // (144-4)/7
  ASSERT_EQ(14,  L.cal_cell_h);   // 56/4
}

UTEST(layout, all_rows_emery_200x228) {
  TimelyLayout L = layout_compute(200, 228);
  ASSERT_EQ(24,  L.statusbar.h);
  ASSERT_EQ(200, L.statusbar.w);
  ASSERT_EQ(24,  L.slot_top.y);
  ASSERT_EQ(113, L.slot_top.h);           // center 26 + time 65 + bottom 22
  ASSERT_EQ(137, L.slot_bot.y);           // 24+113
  ASSERT_EQ(91,  L.slot_bot.h);           // 228-24-113
  ASSERT_EQ(28,  L.cal_cell_w);           // (200-4)/7
  ASSERT_EQ(152, L.battery.x);            // 200-48
}

// Disabling rows frees their height: the calendar (and clock) grow.
UTEST(layout, disabling_rows_grows_calendar_144) {
  TimelyLayout full = layout_compute_rows(144, 168, 1, 1, 1);   // all rows
  TimelyLayout none = layout_compute_rows(144, 168, 1, 0, 0);   // top only
  ASSERT_TRUE(none.slot_bot.h > full.slot_bot.h);               // calendar grew
  ASSERT_TRUE(none.clock_time.h >= full.clock_time.h);          // clock grew (or equal)
  ASSERT_EQ(0, none.clock_date.h);                              // center band collapsed
}

// No status bar (TOP off) reclaims its band too.
UTEST(layout, no_statusbar_reclaims_band) {
  TimelyLayout L = layout_compute_rows(144, 168, 0, 1, 1);
  ASSERT_EQ(0, L.statusbar.h);
  ASSERT_EQ(0, L.slot_top.y); // slot_top starts at the very top now
}
