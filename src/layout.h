#pragma once
// Pebble-free layout geometry so it can be unit-tested on the host.
typedef struct { int x, y, w, h; } LayoutRect;

typedef struct {
  LayoutRect statusbar;   // top band (fixed height: BT/charge/battery)
  LayoutRect slot_top;    // upper half: time/date/weather
  LayoutRect slot_bot;    // lower half: calendar
  LayoutRect battery;     // right-aligned battery box (within statusbar)
  int bt_icon_x, bt_icon_y;
  int chrg_icon_x, chrg_icon_y;
  LayoutRect clock_time;  // relative to slot_top origin
  LayoutRect clock_date;  // relative to slot_top origin
  int subtext_top;
  int cal_cols;
  int cal_cell_w;
  int cal_cell_h;
  int cal_left;
  int cal_gap;
} TimelyLayout;

// Compute the layout for a screen of width x height pixels.
TimelyLayout layout_compute(int width, int height);
