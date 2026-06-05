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

// CENTER/BOTTOM bands collapse to zero exactly when their row is off, and the
// three slot_top bands sum to slot_top.h.
UTEST(layout, bands_collapse_and_sum) {
  TimelyLayout a = layout_compute_rows(144, 168, 1, 1, 0); // no bottom
  ASSERT_EQ(a.slot_top.h, a.subtext_top);                  // zero-height bottom sits at the end
  TimelyLayout b = layout_compute_rows(144, 168, 1, 0, 1); // no center
  ASSERT_EQ(0, b.clock_date.h);                            // center band gone
  ASSERT_EQ(0, b.clock_time.y);                            // time band starts at top of slot_top
  // time band + bottom band fit inside slot_top
  ASSERT_TRUE(b.clock_time.y + b.clock_time.h <= b.slot_top.h);
}

// Pure clock-font selection: scales with band height; Roboto only on wide+tall.
UTEST(clockfont, scales_with_band_and_width) {
  ASSERT_EQ(CLOCK_FONT_ROBOTO_49, clock_font_for(200, 65)); // emery, tall band
  ASSERT_EQ(CLOCK_FONT_LECO_42,   clock_font_for(200, 55)); // wide but shorter -> LECO
  ASSERT_EQ(CLOCK_FONT_LECO_42,   clock_font_for(144, 70)); // narrow never gets Roboto
  ASSERT_EQ(CLOCK_FONT_LECO_38,   clock_font_for(144, 49)); // 144 default band
  ASSERT_EQ(CLOCK_FONT_LECO_32,   clock_font_for(144, 40));
  ASSERT_EQ(CLOCK_FONT_LECO_28,   clock_font_for(144, 30)); // very short
}
