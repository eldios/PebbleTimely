'use strict';

// Ordered list of the numeric (uint8 / int8) settings sent on EVERY save. They
// travel positionally — values only, no key names — so the whole desired state
// fits in the tiny pebblejs://close payload a real watch can carry (the verbose
// per-key JSON of the full state gets truncated by the phone and the save is
// silently lost). configpage.js encodes values in this order; app.js decodes
// them back to keys. This order IS the wire contract between the two: never
// reorder or remove an entry — only APPEND new numeric keys at the end.
//
// The two non-translation STRING settings (strftime_format, language) and any
// changed translation strings travel by name alongside the array; they are few
// and short, so they do not blow the payload.
module.exports = [
  'theme', 'theme_mode', 'style_day_inv', 'style_grid', 'intl_fmt_date',
  'slot_stat_l', 'slot_stat_r', 'slot_ctr_l', 'slot_ctr_r', 'style_week', 'style_am_pm',
  'batt_style', 'intl_fmt_week', 'clock2_tz', 'intl_dowo', 'cal_week_pattern',
  'weather_fmt', 'weather_update', 'weather_icons', 'show_stat_bar', 'show_stat_batt',
  'vibe_pat_disconnect', 'vibe_pat_connect', 'debugging_on', 'debuglang_on',
  'vibe_days', 'vibe_hour', 'vibe_start', 'vibe_stop', 'dnd_noaccel', 'dnd_start', 'dnd_stop'
];
