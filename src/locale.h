#pragma once
// Localization tables. State owned by locale.c; access via the *_get()
// accessors. Structs are persist-backed.

typedef struct persist_months_lang { // 252 bytes
  char monthsNames[12][21];       // 252: 10-20 UTF8 characters for each of 12 months
} __attribute__((__packed__)) persist_months_lang;

typedef struct persist_days_lang { // 238 bytes
  char DaysOfWeek[7][34];         //  238: 16-33 UTF8 characters for each of 7 weekdays
} __attribute__((__packed__)) persist_days_lang;

typedef struct persist_general_lang { // 253 bytes
  char statuses[2][26];
  char abbrTime[2][12];
  char abbrDaysOfWeek[7][6];
  char abbrMonthsNames[12][11];
  char language[3];               // 2 chars for language code (ascii)
} __attribute__((__packed__)) persist_general_lang;

persist_general_lang *lang_gen_get(void);
persist_months_lang  *lang_months_get(void);
persist_days_lang    *lang_days_get(void);
