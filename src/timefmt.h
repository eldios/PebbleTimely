// Pure date/timezone formatting helpers, free of any Pebble SDK dependency so
// they can be unit-tested on the host. See tests/test_timefmt.c.
#pragma once

#include <stddef.h>

// Sentinel for an offset that has not been received from the JS config yet.
#define TIMEZONE_UNINITIALIZED 80

// Number of days in a given month. mon is 0-based (0 = January, 11 = December);
// year is the full Gregorian year (e.g. 2026). Leap years handled per the
// Gregorian rules.
int daysInMonth(int mon, int year);

// Days remaining in the year after the given day-of-year. year is the full
// Gregorian year; yday is 0-based (0 = Jan 1), matching struct tm's tm_yday.
// Returns 0..365.
int days_left_in_year(int year, int yday);

// Format days-remaining as "R%03d" into buf (needs >= 5 bytes). days_left is
// clamped to [0, 365] before formatting.
void format_days_left_in_year(int days_left, char *buf, size_t n);

// Format a quarter-hour timezone offset as "UTC", e.g. "UTC-5", "UTC+5:30",
// or "UTC ?" when uninitialized. buf needs >= 11 bytes (16 recommended).
void format_timezone_offset(int tz_offset, char *buf, size_t n);
