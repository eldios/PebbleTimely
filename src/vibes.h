#pragma once
#include <stdint.h>
#include <stdbool.h>
// Is current_incr within the [start_incr, stop_incr] window? Units are 10-minute
// increments (0-143 = hour*6 + min/10). Inclusive; may wrap past midnight
// (start > stop). Equal start/stop returns retval_on_equal.
bool period_contains(uint8_t start_incr, uint8_t stop_incr,
                     uint8_t current_incr, bool retval_on_equal);
