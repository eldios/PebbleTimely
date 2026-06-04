// Clay configuration page for TimelyNG.
// Select/radiogroup values are HTML strings; app.js coerces the integer-valued
// ones to numbers before sending so the watch can read them as uint8.

var VIBE_PATTERNS = [
  { label: 'None', value: '0' },
  { label: '1x', value: '1' },
  { label: '2x', value: '2' },
  { label: '3x', value: '3' },
  { label: 'Long', value: '4' },
  { label: 'Min', value: '5' },
  { label: 'Min 2', value: '6' },
  { label: 'Ow', value: '7' }
];

module.exports = [
  {
    type: 'heading',
    defaultValue: 'TimelyNG',
    size: 1
  },
  {
    type: 'section',
    items: [
      { type: 'heading', defaultValue: 'Appearance' },
      {
        type: 'select',
        messageKey: 'theme',
        label: 'Theme',
        defaultValue: '1',
        options: [
          { label: 'Mono', value: '0' },
          { label: 'Functional', value: '1' },
          { label: 'Minimal', value: '2' },
          { label: 'Vibrant', value: '3' }
        ]
      },
      {
        type: 'select',
        messageKey: 'theme_mode',
        label: 'Mode',
        description: 'Auto follows local sunset/sunrise.',
        defaultValue: '1',
        options: [
          { label: 'Light', value: '0' },
          { label: 'Dark', value: '1' },
          { label: 'Auto', value: '2' }
        ]
      },
      {
        type: 'toggle',
        messageKey: 'style_day_inv',
        label: 'Highlight today',
        defaultValue: true
      },
      {
        type: 'toggle',
        messageKey: 'style_grid',
        label: 'Calendar grid background',
        defaultValue: true
      },
      {
        type: 'select',
        messageKey: 'intl_dowo',
        label: 'Start of week',
        defaultValue: '0',
        options: [
          { label: 'Sunday', value: '0' },
          { label: 'Monday', value: '1' },
          { label: 'Tuesday', value: '2' },
          { label: 'Wednesday', value: '3' },
          { label: 'Thursday', value: '4' },
          { label: 'Friday', value: '5' },
          { label: 'Saturday', value: '6' }
        ]
      }
    ]
  },
  {
    type: 'section',
    items: [
      { type: 'heading', defaultValue: 'Clock' },
      {
        type: 'select',
        messageKey: 'intl_fmt_date',
        label: 'Date format',
        defaultValue: '0',
        options: [
          { label: 'MMMM DD, YYYY', value: '0' },
          { label: 'DD.MM.YYYY', value: '1' }
        ]
      },
      {
        type: 'select',
        messageKey: 'style_week',
        label: 'Below time, left',
        defaultValue: '0',
        options: [
          { label: '—', value: '0' },
          { label: 'Week', value: '1' },
          { label: 'Timezone', value: '2' },
          { label: 'AM/PM', value: '3' }
        ]
      },
      {
        type: 'select',
        messageKey: 'style_day',
        label: 'Below time, middle',
        defaultValue: '0',
        options: [
          { label: '—', value: '0' },
          { label: 'Day', value: '1' },
          { label: 'Month', value: '2' },
          { label: 'Timezone', value: '3' },
          { label: 'Week', value: '4' },
          { label: 'AM/PM', value: '5' }
        ]
      },
      {
        type: 'select',
        messageKey: 'style_am_pm',
        label: 'Below time, right',
        defaultValue: '0',
        options: [
          { label: '—', value: '0' },
          { label: 'AM/PM', value: '1' },
          { label: 'Timezone', value: '2' },
          { label: 'Week', value: '3' }
        ]
      },
      {
        type: 'select',
        messageKey: 'intl_fmt_week',
        label: 'Week numbering',
        defaultValue: '0',
        options: [
          { label: 'ISO 8601', value: '0' },
          { label: 'Sun 1st of W1', value: '1' },
          { label: 'Mon 1st of W1', value: '2' }
        ]
      }
    ]
  },
  {
    type: 'section',
    items: [
      { type: 'heading', defaultValue: 'Vibration' },
      {
        type: 'select',
        messageKey: 'vibe_hour',
        label: 'Hourly',
        defaultValue: '0',
        options: VIBE_PATTERNS
      },
      {
        type: 'select',
        messageKey: 'vibe_pat_disconnect',
        label: 'On disconnect',
        defaultValue: '2',
        options: VIBE_PATTERNS
      },
      {
        type: 'select',
        messageKey: 'vibe_pat_connect',
        label: 'On reconnect',
        defaultValue: '0',
        options: VIBE_PATTERNS
      }
    ]
  },
  {
    type: 'submit',
    defaultValue: 'Save'
  }
];
