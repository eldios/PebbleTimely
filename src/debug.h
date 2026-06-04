#pragma once
#include <stdbool.h>
// Debug flags. State owned by debug.c; access via debug_get().
typedef struct persist_debug { // 6 bytes
  bool general;     // general debugging messages
  bool language;    // language/translation debugging
  bool reserved_1;
  bool reserved_2;
  bool reserved_3;
  bool reserved_4;
} __attribute__((__packed__)) persist_debug;

persist_debug *debug_get(void);
