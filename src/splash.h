#pragma once
#include <pebble.h>
// Startup splash component (owns its layer).
void splash_create(Layer *parent, GRect frame);
void splash_destroy(void);
void splash_set_hidden(bool hidden);
