#include "suntimes.h"
#include "math.h" // my_sin, my_cos, my_acos, my_tan

#define SUN_PI 3.14159265358979
#define DEG (SUN_PI / 180.0)

void sun_times(float lat, float lon, int yday, float tz_hours,
               float *sunrise, float *sunset) {
  // Solar declination for the day (Cooper's approximation).
  float decl = 23.45 * DEG * my_sin(2.0 * SUN_PI * (284 + yday) / 365.0);
  float latr = lat * DEG;
  float cosH = -my_tan(latr) * my_tan(decl);
  if (cosH <= -1.0) { *sunrise = 0.0;  *sunset = 24.0; return; }  // polar day
  if (cosH >=  1.0) { *sunrise = 12.0; *sunset = 12.0; return; }  // polar night
  float H = my_acos(cosH);            // sunrise hour angle (radians)
  float half = H * 12.0 / SUN_PI;     // half the day length, hours
  // Local solar noon in clock time (longitude + timezone correction; no EoT).
  float noon = 12.0 - lon / 15.0 + tz_hours;
  *sunrise = noon - half;
  *sunset  = noon + half;
}

bool sun_is_night(float lat, float lon, int yday, float tz_hours, float now_hours) {
  float sr, ss;
  sun_times(lat, lon, yday, tz_hours, &sr, &ss);
  return (now_hours < sr || now_hours >= ss);
}
