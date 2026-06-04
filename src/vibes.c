#include "vibes.h"

bool period_contains(uint8_t start_incr, uint8_t stop_incr,
                     uint8_t current_incr, bool retval_on_equal) {
  if (start_incr == stop_incr) return retval_on_equal;
  if (start_incr > stop_incr) // window wraps past midnight
    return (current_incr >= start_incr || current_incr <= stop_incr);
  return (current_incr >= start_incr && current_incr <= stop_incr);
}
