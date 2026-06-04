'use strict';

// Builds the offline settings page as a self-contained HTML string from the
// config spec. No external CSS/JS/host: app.js serves it via a data: URI, so it
// works with no network. On submit the page redirects to `return_to` (provided
// by the emulator as a query param) or, on a real watch, to pebblejs://close#.

function esc(s) {
  return String(s)
    .replace(/&/g, '&amp;').replace(/</g, '&lt;')
    .replace(/>/g, '&gt;').replace(/"/g, '&quot;');
}

function renderField(f, current) {
  var cur = (current && current[f.key] != null) ? current[f.key] : f.def;
  var h = '';
  if (f.type === 'toggle') {
    h += '<label class="row"><span>' + esc(f.label) + '</span>' +
         '<input type="checkbox" data-key="' + esc(f.key) + '" data-type="bool"' +
         (Number(cur) ? ' checked' : '') + '></label>';
  } else {
    h += '<label class="row"><span>' + esc(f.label) + '</span><select data-key="' +
         esc(f.key) + '" data-type="int">';
    for (var i = 0; i < f.options.length; i++) {
      var o = f.options[i];
      h += '<option value="' + esc(o[1]) + '"' +
           (Number(cur) === Number(o[1]) ? ' selected' : '') + '>' + esc(o[0]) + '</option>';
    }
    h += '</select></label>';
  }
  if (f.note) { h += '<p class="note">' + esc(f.note) + '</p>'; }
  return h;
}

var CSS = [
  '*{box-sizing:border-box}',
  'body{margin:0;padding:14px 14px 92px;background:#1b1b1d;color:#eee;',
  'font-family:-apple-system,Roboto,Segoe UI,Helvetica,Arial,sans-serif;-webkit-text-size-adjust:100%}',
  'h1{font-size:22px;font-weight:600;margin:4px 2px 16px}',
  'section{background:#262629;border-radius:10px;padding:2px 14px;margin:0 0 14px}',
  'h2{font-size:12px;text-transform:uppercase;letter-spacing:.07em;color:#ff9f0a;margin:14px 0 6px}',
  '.row{display:flex;align-items:center;justify-content:space-between;gap:12px;',
  'padding:11px 0;border-bottom:1px solid #333;font-size:16px}',
  '.row:last-of-type{border-bottom:0}',
  'select{font-size:16px;background:#333;color:#eee;border:1px solid #454547;border-radius:7px;padding:8px 9px;max-width:55%}',
  'input[type=checkbox]{width:26px;height:26px;accent-color:#ff9f0a}',
  '.note{font-size:12px;color:#9a9a9a;margin:-2px 0 10px}',
  '.bar{position:fixed;left:0;right:0;bottom:0;display:flex;gap:10px;padding:11px 14px;',
  'background:#1b1b1de6;border-top:1px solid #333;backdrop-filter:blur(6px)}',
  'button{flex:1;font-size:17px;font-weight:600;border:0;border-radius:8px;padding:13px;color:#fff}',
  '#cancel{background:#3a3a3d}#save{background:#ff9f0a;color:#1b1b1d}'
].join('');

function buildConfigPage(spec, current) {
  var body = '';
  for (var s = 0; s < spec.length; s++) {
    body += '<section><h2>' + esc(spec[s].title) + '</h2>';
    for (var i = 0; i < spec[s].fields.length; i++) {
      body += renderField(spec[s].fields[i], current);
    }
    body += '</section>';
  }
  var script =
    // Read return_to from the full href: data:/file: URIs do not populate
    // location.search, but the emulator appends ?return_to= and the encoded page
    // body has no literal ? or &, so the match here is unambiguous.
    'function qp(n,d){var m=(location.href||"").match(new RegExp("[?&]"+n+"=([^&#]*)"));' +
    'return m?decodeURIComponent(m[1]):d;}' +
    'var RET=qp("return_to","pebblejs://close#");' +
    'document.getElementById("cancel").onclick=function(){document.location=RET;};' +
    'document.getElementById("save").onclick=function(){var o={},' +
    'els=document.querySelectorAll("[data-key]");for(var i=0;i<els.length;i++){' +
    'var e=els[i],k=e.getAttribute("data-key");' +
    'o[k]=e.getAttribute("data-type")==="bool"?(e.checked?1:0):Number(e.value);}' +
    'document.location=RET+encodeURIComponent(JSON.stringify(o));};';
  return '<!DOCTYPE html><html lang="en"><head><meta charset="utf-8">' +
    '<meta name="viewport" content="width=device-width,initial-scale=1">' +
    '<title>TimelyNG settings</title><style>' + CSS + '</style></head><body>' +
    '<h1>TimelyNG</h1><form id="f">' + body + '</form>' +
    '<div class="bar"><button type="button" id="cancel">Cancel</button>' +
    '<button type="button" id="save">Save</button></div>' +
    '<script>' + script + '<\/script></body></html>';
}

module.exports = buildConfigPage;
