#include "layout.h"

// Statusbar stays a fixed height: it holds fixed-size 20px icons and a 15px
// battery, which must not scale. The remaining height is split evenly between
// the time/date/weather slot and the calendar slot (the historical 144x168
// design used 24 / 72 / 72, i.e. statusbar then two equal halves).
#define STATUSBAR_H   24
#define CAL_COLS       7
#define CAL_GAP        1
#define CAL_LEFT       2

TimelyLayout layout_compute(int width, int height) {
  TimelyLayout L;
  int body = height - STATUSBAR_H;
  int slot_h = body / 2;

  L.statusbar = (LayoutRect){ 0, 0, width, STATUSBAR_H };
  L.slot_top  = (LayoutRect){ 0, STATUSBAR_H, width, slot_h };
  L.slot_bot  = (LayoutRect){ 0, STATUSBAR_H + slot_h, width, height - STATUSBAR_H - slot_h };

  // statusbar internals (battery right-aligned; icons mirror the 144x168 look)
  L.battery     = (LayoutRect){ width - 48, 4, 44, 15 };
  L.bt_icon_x   = -2; L.bt_icon_y = 2;
  L.chrg_icon_x = width - 68; L.chrg_icon_y = 2;

  // clock/date inside slot_top (proportional, mirrors REL_CLOCK_* at 144x168)
  L.clock_date = (LayoutRect){ 2, 0, width - 4, (slot_h * 30) / 72 };
  L.clock_time = (LayoutRect){ 0, (slot_h * 7) / 72, width - 2, (slot_h * 60) / 72 };
  L.subtext_top = (slot_h * 56) / 72;

  // calendar grid inside slot_bot: 7 columns spanning the width, 3 rows.
  L.cal_cols   = CAL_COLS;
  L.cal_gap    = CAL_GAP;
  L.cal_left   = CAL_LEFT;
  L.cal_cell_w = (width - 2 * CAL_LEFT) / CAL_COLS;
  L.cal_cell_h = L.slot_bot.h / 4; // header row + 3 week rows

  return L;
}

static TimelyLayout s_current;
void layout_store(TimelyLayout l) { s_current = l; }
TimelyLayout layout_get(void) { return s_current; }
