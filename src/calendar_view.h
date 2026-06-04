#pragma once
#include <pebble.h>
// Calendar display component (owns its layer; draws the calendar.h model).
void calendar_create(Layer *parent, GRect frame);
void calendar_destroy(void);
void calendar_set_hidden(bool hidden);
void calendar_mark_dirty(void);
