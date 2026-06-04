#pragma once
#include <pebble.h>
// Color theme. Dark = white-on-black; Inv = black-on-white; Today = accent on
// color hardware with B&W fallback. Each sets the window background + the
// stroke/fill/text colors on the given context.
void setColors(GContext* ctx);
void setInvColors(GContext* ctx);
void setTodayColors(GContext* ctx);
