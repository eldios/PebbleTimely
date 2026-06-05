#pragma once
#include <stdbool.h>
// Sunrise/sunset approximation (solar declination + hour angle; equation-of-time
// omitted, ~15min). Pure: uses math.c's trig, so it is host-testable.
//   lat, lon : degrees (N/E positive).  yday : 0-based day of year (tm_yday).
//   tz_hours : offset from UTC in hours (e.g. +2 for CEST).
// Outputs sunrise/sunset as fractional LOCAL clock hours (0..24).
void sun_times(float lat, float lon, int yday, float tz_hours,
               float *sunrise, float *sunset);

// Is the given local time (fractional hours) outside [sunrise, sunset]?
bool sun_is_night(float lat, float lon, int yday, float tz_hours, float now_hours);
