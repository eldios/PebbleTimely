#pragma once
#include <pebble.h>
// Shared UI handles owned by the view (Timely.c) and used by split view modules.
extern Window *window;
extern GFont climacons; // weather icon font (loaded in window_load)
