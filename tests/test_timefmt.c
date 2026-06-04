// Host-side unit tests for src/timefmt.c (pure logic, no Pebble SDK).
// Build/run via `make test`, `just test`, or `nix flake check`.
#include "utest.h"
#include "timefmt.h"

UTEST(daysInMonth, february_leap_rules) {
  ASSERT_EQ(29, daysInMonth(1, 2000)); // divisible by 400 -> leap
  ASSERT_EQ(28, daysInMonth(1, 1900)); // divisible by 100, not 400 -> common
  ASSERT_EQ(29, daysInMonth(1, 2024)); // divisible by 4 -> leap
  ASSERT_EQ(28, daysInMonth(1, 2026)); // common year
}

UTEST(daysInMonth, month_lengths) {
  ASSERT_EQ(31, daysInMonth(0, 2026));  // January
  ASSERT_EQ(30, daysInMonth(3, 2026));  // April
  ASSERT_EQ(31, daysInMonth(11, 2026)); // December
}

UTEST(days_left_in_year, boundaries) {
  ASSERT_EQ(364, days_left_in_year(2026, 0));    // common year, Jan 1
  ASSERT_EQ(0,   days_left_in_year(2026, 364));  // common year, Dec 31
  ASSERT_EQ(365, days_left_in_year(2024, 0));    // leap year, Jan 1
  ASSERT_EQ(0,   days_left_in_year(2024, 365));  // leap year, Dec 31
}

UTEST(format_days_left_in_year, typical_and_clamp) {
  char b[5];
  format_days_left_in_year(364, b, sizeof(b));  ASSERT_STREQ("R364", b);
  format_days_left_in_year(0, b, sizeof(b));    ASSERT_STREQ("R000", b);
  format_days_left_in_year(5, b, sizeof(b));    ASSERT_STREQ("R005", b);
  format_days_left_in_year(-3, b, sizeof(b));   ASSERT_STREQ("R000", b); // clamp low
  format_days_left_in_year(9999, b, sizeof(b)); ASSERT_STREQ("R365", b); // clamp high
}

// Preserves the watchface's existing (inverted-sign) convention:
// positive offset -> "UTC-", non-positive -> "UTC+".
UTEST(format_timezone_offset, formats) {
  char b[16];
  format_timezone_offset(TIMEZONE_UNINITIALIZED, b, sizeof(b)); ASSERT_STREQ("UTC ?", b);
  format_timezone_offset(0, b, sizeof(b));   ASSERT_STREQ("UTC+0", b);
  format_timezone_offset(4, b, sizeof(b));   ASSERT_STREQ("UTC-1", b);     // +1h east
  format_timezone_offset(5, b, sizeof(b));   ASSERT_STREQ("UTC-1:15", b);  // +1h15
  format_timezone_offset(-4, b, sizeof(b));  ASSERT_STREQ("UTC+1", b);     // -1h west
  format_timezone_offset(-5, b, sizeof(b));  ASSERT_STREQ("UTC+1:15", b);  // -1h15
}

