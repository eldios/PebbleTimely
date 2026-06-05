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

// Compute the layout for a screen of width x height pixels. The _rows variant
// takes which optional rows are enabled (TOP status bar / CENTER above-time /
// BOTTOM above-calendar); disabled rows free their height to the rest.
TimelyLayout layout_compute_rows(int width, int height, int has_top, int has_center, int has_bottom);
TimelyLayout layout_compute(int width, int height); // all rows present (default)

// Clock font choice as a pure, testable decision (the view maps it to a Pebble
// FONT_KEY). Scales with the time-band height; the big proportional Roboto is
// only for wide screens where it won't collide with the weather column.
typedef enum {
  CLOCK_FONT_ROBOTO_49 = 0, // wide screens, tall band
  CLOCK_FONT_LECO_42,
  CLOCK_FONT_LECO_38,
  CLOCK_FONT_LECO_32,
  CLOCK_FONT_LECO_28,       // smallest (very short band)
} ClockFont;
ClockFont clock_font_for(int width, int band_h);

// The most recently computed layout (set by the view at window_load); read by
// components that render proportionally (calendar, etc.).
void layout_store(TimelyLayout l);
TimelyLayout layout_get(void);
