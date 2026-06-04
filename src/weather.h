#pragma once
#include <stdint.h>
#include <pebble.h>
// Weather state, owned by weather.c. Access only through weather_state().
typedef struct weather_data {
  int16_t current;    // current temperature
  char condition[2];  // weather condition (mapped to a single climacons glyph)
  int16_t requests;   // requests sent since last success
  int16_t failures;   // failed responses since last success
} __attribute__((__packed__)) weather_data;

weather_data *weather_state(void);

void weather_layer_update_callback(Layer *me, GContext* ctx);
