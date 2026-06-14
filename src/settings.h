#pragma once
#include <stdint.h>
// User settings + advanced settings. State owned by settings.c; access via
// settings_get() / adv_settings_get(). Structs are persist-backed.

typedef struct persist { // 18 bytes
  uint8_t version;                // version key
  uint8_t inverted;               // Invert display
  uint8_t day_invert;             // Invert colors on today's date
  uint8_t grid;                   // Show the grid
  uint8_t vibe_hour;              // vibrate at the top of the hour?
  uint8_t dayOfWeekOffset;        // first day of our week
  uint8_t date_format;            // date format
  uint8_t show_am_pm;             // Above-calendar slot, right (complication content)
  uint8_t show_day;               // (retired middle slot)
  uint8_t show_week;              // Above-calendar slot, left (complication content)
  uint8_t slot_stat_l;            // Status bar slot, left (complication content)
  uint8_t slot_stat_r;            // Status bar slot, right (complication content)
  uint8_t slot_ctr_l;             // Center row (above time), left
  uint8_t slot_ctr_r;             // Center row (above time), right
  uint8_t batt_style;             // battery complication style: 0 bar, 1 text, 2 icon+text
  uint8_t week_format;            // week format (calculation, e.g. ISO 8601)
  uint8_t vibe_pat_disconnect;    // vibration pattern for disconnect
  uint8_t vibe_pat_connect;       // vibration pattern for connect
  char *strftime_format;          // custom date_format string (date_format = 255)
  uint8_t track_battery;          // track battery information
  uint8_t theme;                  // color theme id (see theme.h)
  uint8_t theme_mode;             // 0 light, 1 dark, 2 auto (dark at night)
} __attribute__((__packed__)) persist;

typedef struct persist_adv_settings { // 243 bytes
  uint8_t week_pattern;    //  1 byte
  uint8_t invertStatBar;   //  1 byte
  uint8_t invertTopSlot;   //  1 byte
  uint8_t invertBotSlot;   //  1 byte
  uint8_t showStatus;      //  1 byte
  uint8_t showStatusBat;   //  1 byte
  uint8_t showDate;        //  1 byte
  uint8_t DND_start;       //  1 byte
  uint8_t DND_stop;        //  1 byte
  uint8_t dnd_mode;        //  1 byte: 0 off, 1 follow watch Quiet Time, 2 app window
  uint8_t vibe_hour_start; //  1 byte
  uint8_t vibe_hour_stop;  //  1 byte
  uint8_t vibe_hour_days;  //  1 byte
  uint8_t idle_reminder;   //  1 byte
  uint8_t idle_pattern;    //  1 byte
  char custom_date_fmt[32]; // 32 bytes: custom strftime date format (date_format == 255)
  uint8_t idle_start;      //  1 byte
  uint8_t idle_stop;       //  1 byte
  int8_t clock2_tz;        //  1 byte
  char clock2_desc[32];    // 32 bytes
  uint8_t weather_format;  //  1 byte
  uint8_t weather_update;  //  1 byte
  char weather_lat[8];     //  8 bytes
  char weather_lon[8];     //  8 bytes
  uint8_t clock_font;      //  1 byte
  uint8_t token_type[2];   //  2 bytes
  char token_code[2][65];  //130 bytes
  uint8_t slots[10];       // 10 bytes
  uint8_t weather_icons;   //  1 byte: 0 default (colour where supported), 1 force colour, 2 force B&W
} __attribute__((__packed__)) persist_adv_settings;
// New fields go at the END: persist_read_data tolerates a shorter stored blob,
// leaving appended fields at their settings.c default for pre-existing installs.

persist *settings_get(void);
persist_adv_settings *adv_settings_get(void);
