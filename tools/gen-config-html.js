// Render the offline settings page to a standalone HTML file.
// Used for previewing in a browser and for emulator testing
// (`pebble emu-app-config --file <out>`), which provides return_to so the
// page's pebblejs://close# fallback is not needed there.
var fs = require('fs');
var spec = require('../src/js/config');
var build = require('../src/js/configpage');
var out = process.argv[2] || 'build/config.html';
fs.writeFileSync(out, build(spec, {}));
console.log('wrote ' + out);
