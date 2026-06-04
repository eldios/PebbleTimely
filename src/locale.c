#include "locale.h"

static persist_months_lang s_months = {
  .monthsNames = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" },
};

static persist_days_lang s_days = {
  .DaysOfWeek = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" },
};

static persist_general_lang s_gen = {
  .statuses = { "Linked", "NOLINK" },
  .abbrTime = { "AM", "PM" },
  .abbrDaysOfWeek = { "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa" },
  .abbrMonthsNames = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" },
  .language = "EN",
};

persist_general_lang *lang_gen_get(void)   { return &s_gen; }
persist_months_lang  *lang_months_get(void){ return &s_months; }
persist_days_lang    *lang_days_get(void)  { return &s_days; }
