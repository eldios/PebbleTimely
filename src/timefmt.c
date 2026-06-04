#include "timefmt.h"
#include <stdio.h>
#include <stdlib.h>

int daysInMonth(int mon, int year) {
  mon++; // callers pass 0-based months (0 = January)
  if (mon == 4 || mon == 6 || mon == 9 || mon == 11) {
    return 30;
  } else if (mon == 2) {
    if (year % 400 == 0) return 29;
    if (year % 100 == 0) return 28;
    if (year % 4 == 0) return 29;
    return 28;
  }
  return 31;
}

int days_left_in_year(int year, int yday) {
  int days_this_year = (daysInMonth(1, year) == 29) ? 366 : 365;
  return days_this_year - yday - 1;
}

void format_days_left_in_year(int days_left, char *buf, size_t n) {
  if (days_left < 0)   days_left = 0;
  if (days_left > 365) days_left = 365;
  snprintf(buf, n, "R%03d", days_left);
}

void format_timezone_offset(int tz_offset, char *buf, size_t n) {
  if (tz_offset == TIMEZONE_UNINITIALIZED) {
    snprintf(buf, n, "UTC ?");
    return;
  }
  // Clamp to the real timezone domain (UTC-14..+14 in quarter-hours): guards
  // against malformed config and bounds the formatted width.
  if (tz_offset < -56) tz_offset = -56;
  if (tz_offset > 56)  tz_offset = 56;
  int tz_mins  = (tz_offset % 4) * 15;
  int tz_hours = (tz_offset - (tz_offset % 4)) / 4;
  // Sign convention is intentionally inverted to match the watchface's
  // historical display: positive offset prints "UTC-", non-positive "UTC+".
  if (tz_offset > 0) {
    if (tz_mins == 0) snprintf(buf, n, "UTC-%d", tz_hours);
    else              snprintf(buf, n, "UTC-%d:%d", tz_hours, tz_mins);
  } else {
    if (tz_mins == 0) snprintf(buf, n, "UTC+%d", abs(tz_hours));
    else              snprintf(buf, n, "UTC+%d:%d", abs(tz_hours), abs(tz_mins));
  }
}
