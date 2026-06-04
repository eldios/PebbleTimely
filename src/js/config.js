// Declarative spec for the offline settings page (see configpage.js).
// Each field's `key` matches a messageKey in package.json. Numeric keys are read
// by the watch as uint8; text keys (language + translations) as strings.

var VIBES = [
  ['None', 0], ['1x', 1], ['2x', 2], ['3x', 3],
  ['Long', 4], ['Min', 5], ['Min 2', 6], ['Ow', 7]
];

// Complication menu shared by all three below-time slots (left/middle/right).
// Values must match update_slot_text() in Timely.c.
var SLOTS = [
  ['—', 0], ['Day', 1], ['Month', 2], ['Week', 3], ['Timezone', 4], ['AM/PM', 5],
  ['Day of year', 6], ['Days left in year', 7], ['Day of year / left', 8],
  ['Seconds', 9], ['Location', 10]
];

// Date formats; values must match update_date_text() in Timely.c. 255 = custom.
var DATE_FORMATS = [
  ['MMMM DD, YYYY', 0], ['MMMM DD, ’YY', 1], ['Mmm DD, YYYY', 2], ['Mmm DD, ’YY', 3],
  ['D MMMM YYYY', 11], ['D MMMM ’YY', 12], ['D Mmm YYYY', 13], ['D Mmm ’YY', 14],
  ['MM/DD/YYYY', 197], ['DD/MM/YYYY', 217], ['DD.MM.YYYY', 215], ['YYYY-MM-DD', 236],
  ['DD-MM-YYYY', 216], ['MM-DD-YYYY', 196], ['YYYY/MM/DD', 237], ['YYYYMMDD', 239],
  ['Custom (strftime)', 255]
];

// Build a list of text fields: keys[i] -> label[i] with default defs[i].
function textFields(keys, labels, defs, max) {
  var out = [];
  for (var i = 0; i < keys.length; i++) {
    out.push({ key: keys[i], label: labels[i], type: 'text', def: defs[i], max: max });
  }
  return out;
}

var DOW = ['sunday', 'monday', 'tuesday', 'wedsday', 'thursday', 'friday', 'saturday'];
var DOW_LABEL = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];
var DOW_ABBR = ['Su', 'Mo', 'Tu', 'We', 'Th', 'Fr', 'Sa'];
var MON = ['january', 'february', 'march', 'april', 'may', 'june',
           'july', 'august', 'september', 'october', 'november', 'december'];
var MON_LABEL = ['January', 'February', 'March', 'April', 'May', 'June',
                 'July', 'August', 'September', 'October', 'November', 'December'];
var MON_ABBR = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];

// Editable translation strings. The language selector (see configpage.js) fills
// these from a built-in table; they are only shown for manual editing when the
// language is set to Custom (langCustom flag).
var translations = [
  { key: 'trans_connected', label: 'Connected', type: 'text', def: 'Linked', max: 9 },
  { key: 'trans_disconnected', label: 'Disconnected', type: 'text', def: 'NOLINK', max: 9 },
  { key: 'trans_time_am', label: 'AM', type: 'text', def: 'AM', max: 6 },
  { key: 'trans_time_pm', label: 'PM', type: 'text', def: 'PM', max: 6 }
]
  .concat(textFields(DOW.map(function (d) { return 'trans_abbr_' + d; }),
    DOW_LABEL.map(function (l) { return l + ' (abbr)'; }), DOW_ABBR, 2))
  .concat(textFields(DOW.map(function (d) { return 'trans_' + d; }), DOW_LABEL, DOW_LABEL, 12))
  .concat(textFields(MON.map(function (m) { return 'trans_abbr_' + m; }),
    MON_LABEL.map(function (l) { return l + ' (abbr)'; }), MON_ABBR, 3))
  .concat(textFields(MON.map(function (m) { return 'trans_' + m; }), MON_LABEL, MON_LABEL, 11));
translations.forEach(function (f) { f.langCustom = true; });

module.exports = [
  {
    title: 'Appearance',
    fields: [
      { key: 'theme', label: 'Theme', type: 'select', def: 1,
        options: [['Mono', 0], ['Functional', 1], ['Minimal', 2], ['Vibrant', 3]] },
      { key: 'theme_mode', label: 'Mode', type: 'select', def: 1,
        note: 'Auto follows local sunset/sunrise.',
        options: [['Light', 0], ['Dark', 1], ['Auto', 2]] },
      { key: 'style_day_inv', label: 'Highlight today', type: 'toggle', def: 1 },
      { key: 'style_grid', label: 'Calendar grid background', type: 'toggle', def: 1 }
    ]
  },
  {
    title: 'Clock',
    fields: [
      { key: 'intl_fmt_date', label: 'Date format', type: 'select', def: 0, options: DATE_FORMATS },
      { key: 'strftime_format', label: 'Custom format', type: 'text', def: '%Y-%m-%d', max: 31,
        showWhen: { key: 'intl_fmt_date', val: 255 },
        note: 'strftime pattern, e.g. %a %d %b. Used when Date format is Custom.' },
      { key: 'style_week', label: 'Above calendar, left', type: 'select', def: 0, options: SLOTS },
      { key: 'style_am_pm', label: 'Above calendar, right', type: 'select', def: 0, options: SLOTS },
      { key: 'intl_fmt_week', label: 'Week numbering', type: 'select', def: 0,
        options: [['ISO 8601', 0], ['Sun 1st of W1', 1], ['Mon 1st of W1', 2]] }
    ]
  },
  {
    title: 'Calendar',
    fields: [
      { key: 'intl_dowo', label: 'Start of week', type: 'select', def: 0,
        options: [['Sunday', 0], ['Monday', 1], ['Tuesday', 2], ['Wednesday', 3],
                  ['Thursday', 4], ['Friday', 5], ['Saturday', 6]] },
      { key: 'cal_week_pattern', label: 'Weeks shown', type: 'select', def: 0,
        options: [['Previous + next', 0], ['Last two weeks', 1], ['Next two weeks', 2]] }
    ]
  },
  {
    title: 'Weather',
    open: false,
    fields: [
      { key: 'weather_fmt', label: 'Units', type: 'select', def: 0,
        options: [['Celsius', 0], ['Fahrenheit', 1]] },
      { key: 'weather_update', label: 'Update every', type: 'select', def: 15,
        options: [['Off', 0], ['15 min', 15], ['30 min', 30], ['60 min', 60]] }
    ]
  },
  {
    title: 'Status bar',
    open: false,
    fields: [
      { key: 'show_stat_bar', label: 'Show status bar', type: 'select', def: 1,
        options: [['Never', 0], ['Always', 1], ['When battery low', 2]] },
      { key: 'show_stat_batt', label: 'Low battery threshold (%)', type: 'number', def: 20,
        min: 0, max: 100, note: 'Used when "When battery low" is selected.' }
    ]
  },
  {
    title: 'Vibration',
    open: false,
    fields: [
      { type: 'vibe-sched' },
      { key: 'vibe_pat_disconnect', label: 'On disconnect', type: 'select', def: 2, options: VIBES },
      { key: 'vibe_pat_connect', label: 'On reconnect', type: 'select', def: 0, options: VIBES }
    ]
  },
  {
    title: 'Do Not Disturb',
    open: false,
    fields: [
      { type: 'dnd-sched' }
    ]
  },
  {
    title: 'Language',
    open: false,
    fields: [{ type: 'lang-sel' }].concat(translations)
  },
  {
    title: 'Advanced',
    open: false,
    fields: [
      { key: 'debugging_on', label: 'Debug logging', type: 'toggle', def: 0 },
      { key: 'debuglang_on', label: 'Translation debug logging', type: 'toggle', def: 0 }
    ]
  }
];
