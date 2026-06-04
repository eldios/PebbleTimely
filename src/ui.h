#pragma once
#include <pebble.h>
// Shared UI handles owned by the view (Timely.c) and used by split view modules.
extern Window *window;
extern GFont climacons; // weather icon font (loaded in window_load)
#include <time.h>
extern struct tm *currentTime;   // current time (updated each tick by the view)
extern GFont cal_normal, cal_bold; // calendar day-label fonts (loaded in window_load)
