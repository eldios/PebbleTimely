// Declarative spec for the offline settings page (see configpage.js).
// Each field's `key` matches a messageKey in package.json; the watch reads the
// value as a uint8, so option values and defaults are plain integers.

var VIBES = [
  ['None', 0], ['1x', 1], ['2x', 2], ['3x', 3],
  ['Long', 4], ['Min', 5], ['Min 2', 6], ['Ow', 7]
];

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
      { key: 'style_grid', label: 'Calendar grid background', type: 'toggle', def: 1 },
      { key: 'intl_dowo', label: 'Start of week', type: 'select', def: 0,
        options: [['Sunday', 0], ['Monday', 1], ['Tuesday', 2], ['Wednesday', 3],
                  ['Thursday', 4], ['Friday', 5], ['Saturday', 6]] }
    ]
  },
  {
    title: 'Clock',
    fields: [
      { key: 'intl_fmt_date', label: 'Date format', type: 'select', def: 0,
        options: [['MMMM DD, YYYY', 0], ['DD.MM.YYYY', 1]] },
      { key: 'style_week', label: 'Below time, left', type: 'select', def: 0,
        options: [['—', 0], ['Week', 1], ['Timezone', 2], ['AM/PM', 3]] },
      { key: 'style_day', label: 'Below time, middle', type: 'select', def: 0,
        options: [['—', 0], ['Day', 1], ['Month', 2], ['Timezone', 3], ['Week', 4], ['AM/PM', 5]] },
      { key: 'style_am_pm', label: 'Below time, right', type: 'select', def: 0,
        options: [['—', 0], ['AM/PM', 1], ['Timezone', 2], ['Week', 3]] },
      { key: 'intl_fmt_week', label: 'Week numbering', type: 'select', def: 0,
        options: [['ISO 8601', 0], ['Sun 1st of W1', 1], ['Mon 1st of W1', 2]] }
    ]
  },
  {
    title: 'Vibration',
    fields: [
      { key: 'vibe_hour', label: 'Hourly', type: 'select', def: 0, options: VIBES },
      { key: 'vibe_pat_disconnect', label: 'On disconnect', type: 'select', def: 2, options: VIBES },
      { key: 'vibe_pat_connect', label: 'On reconnect', type: 'select', def: 0, options: VIBES }
    ]
  }
];
