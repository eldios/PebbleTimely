#pragma once
// 3-week calendar grid model (pure; no Pebble deps). Rendering stays in Timely.c.

typedef struct {
  int days[21];     // day-of-month numbers, row-major 3 weeks x 7 columns
  int special_col;  // column [0-6] holding today
  int special_row;  // week row [1-3] holding today
} CalGrid;

// Build the grid. year=full (2026), mon=0-11, mday=1-31, wday=0(Sun)-6(Sat),
// dow_offset=start-of-week offset 0-6, week_pattern: 0=1 before+1 after,
// 1=2 before, 2=2 after.
CalGrid calendar_build(int year, int mon, int mday, int wday,
                       int dow_offset, int week_pattern);
