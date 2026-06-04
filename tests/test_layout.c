#include "utest.h"
#include "layout.h"

UTEST(layout, classic_144x168_matches_historical) {
  TimelyLayout L = layout_compute(144, 168);
  ASSERT_EQ(0,   L.statusbar.y);  ASSERT_EQ(24, L.statusbar.h);
  ASSERT_EQ(144, L.statusbar.w);
  ASSERT_EQ(24,  L.slot_top.y);   ASSERT_EQ(72, L.slot_top.h);
  ASSERT_EQ(96,  L.slot_bot.y);   ASSERT_EQ(72, L.slot_bot.h);
  ASSERT_EQ(7,   L.cal_cols);
  ASSERT_EQ(20,  L.cal_cell_w);   // (144-4)/7 = 20
  ASSERT_EQ(24,  L.cal_cell_h);   // 72/3
}

UTEST(layout, emery_200x228_fills_screen) {
  TimelyLayout L = layout_compute(200, 228);
  ASSERT_EQ(24,  L.statusbar.h);          // fixed
  ASSERT_EQ(200, L.statusbar.w);
  ASSERT_EQ(24,  L.slot_top.y);           // right after statusbar
  ASSERT_EQ(102, L.slot_top.h);           // (228-24)/2
  ASSERT_EQ(126, L.slot_bot.y);           // 24+102
  ASSERT_EQ(28,  L.cal_cell_w);           // (200-4)/7
  ASSERT_EQ(34,  L.cal_cell_h);           // 102/3
  ASSERT_EQ(152, L.battery.x);            // 200-48
}

