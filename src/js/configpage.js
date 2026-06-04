'use strict';

// Builds the offline settings page as a self-contained HTML string from the
// config spec. No external CSS/JS/host: app.js serves it via a data: URI, so it
// works with no network. On submit the page redirects to `return_to` (provided
// by the emulator as a query param) or, on a real watch, to pebblejs://close#.
//
// Field types: select (int), toggle (0/1), number (int), text (string),
// time (HH:MM stored as a 10-minute increment 0-143, h*6 + floor(m/10)).

function esc(s) {
  return String(s)
    .replace(/&/g, '&amp;').replace(/</g, '&lt;')
    .replace(/>/g, '&gt;').replace(/"/g, '&quot;');
}

function pad2(n) { return ('0' + n).slice(-2); }
function incrToTime(incr) {
  incr = Number(incr) || 0;
  return pad2(Math.floor(incr / 6)) + ':' + pad2((incr % 6) * 10);
}

function renderField(f, current) {
  var cur = (current && current[f.key] != null) ? current[f.key] : f.def;
  var attrs = 'data-key="' + esc(f.key) + '"';
  var control;
  switch (f.type) {
    case 'toggle':
      control = '<input type="checkbox" ' + attrs + ' data-type="bool"' +
        (Number(cur) ? ' checked' : '') + '>';
      break;
    case 'number':
      control = '<input type="number" ' + attrs + ' data-type="int" value="' + esc(cur) +
        '" min="' + (f.min != null ? f.min : 0) + '" max="' + (f.max != null ? f.max : 100) + '">';
      break;
    case 'time':
      control = '<input type="time" ' + attrs + ' data-type="time" value="' + incrToTime(cur) + '">';
      break;
    case 'text':
      control = '<input type="text" ' + attrs + ' data-type="str" value="' + esc(cur || '') +
        '"' + (f.max ? ' maxlength="' + f.max + '"' : '') + '>';
      break;
    default: // select
      control = '<select ' + attrs + ' data-type="int">';
      for (var i = 0; i < f.options.length; i++) {
        var o = f.options[i];
        control += '<option value="' + esc(o[1]) + '"' +
          (Number(cur) === Number(o[1]) ? ' selected' : '') + '>' + esc(o[0]) + '</option>';
      }
      control += '</select>';
  }
  var row = '<label class="row"><span>' + esc(f.label) + '</span>' + control + '</label>';
  if (f.note) { row += '<p class="note">' + esc(f.note) + '</p>'; }
  return row;
}

var CSS = [
  '*{box-sizing:border-box}',
  'body{margin:0;padding:14px 14px 92px;background:#1b1b1d;color:#eee;',
  'font-family:-apple-system,Roboto,Segoe UI,Helvetica,Arial,sans-serif;-webkit-text-size-adjust:100%}',
  'h1{font-size:22px;font-weight:600;margin:4px 2px 16px}',
  'details{background:#262629;border-radius:10px;padding:0 14px;margin:0 0 12px;overflow:hidden}',
  'summary{font-size:13px;text-transform:uppercase;letter-spacing:.06em;color:#ff9f0a;',
  'font-weight:600;padding:13px 0;cursor:pointer;list-style:none}',
  'summary::-webkit-details-marker{display:none}',
  'summary:after{content:"+";float:right;color:#888;font-weight:400}',
  'details[open] summary:after{content:"\\2212"}',
  '.row{display:flex;align-items:center;justify-content:space-between;gap:12px;',
  'padding:11px 0;border-top:1px solid #333;font-size:16px}',
  'select,input[type=number],input[type=text],input[type=time]{font-size:16px;background:#333;color:#eee;',
  'border:1px solid #454547;border-radius:7px;padding:8px 9px;max-width:55%}',
  'input[type=text]{max-width:48%}',
  'input[type=checkbox]{width:26px;height:26px;accent-color:#ff9f0a;flex:none}',
  '.note{font-size:12px;color:#9a9a9a;margin:2px 0 8px}',
  '.bar{position:fixed;left:0;right:0;bottom:0;display:flex;gap:10px;padding:11px 14px;',
  'background:#1b1b1de6;border-top:1px solid #333}',
  'button{flex:1;font-size:17px;font-weight:600;border:0;border-radius:8px;padding:13px;color:#fff}',
  '#cancel{background:#3a3a3d}#save{background:#ff9f0a;color:#1b1b1d}'
].join('');

function buildConfigPage(spec, current) {
  var body = '';
  for (var s = 0; s < spec.length; s++) {
    var sec = spec[s];
    body += '<details' + (sec.open === false ? '' : ' open') + '><summary>' + esc(sec.title) + '</summary>';
    for (var i = 0; i < sec.fields.length; i++) { body += renderField(sec.fields[i], current); }
    body += '</details>';
  }
  var script =
    // Read return_to from the full href: data:/file: URIs do not populate
    // location.search, but the emulator appends ?return_to= and the encoded page
    // body has no literal ? or &, so the match here is unambiguous.
    'function qp(n,d){var m=(location.href||"").match(new RegExp("[?&]"+n+"=([^&#]*)"));' +
    'return m?decodeURIComponent(m[1]):d;}' +
    'var RET=qp("return_to","pebblejs://close#");' +
    'function val(e){var t=e.getAttribute("data-type");' +
    'if(t==="bool")return e.checked?1:0;' +
    'if(t==="str")return e.value;' +
    'if(t==="time"){var p=(e.value||"0:0").split(":");' +
    'return (parseInt(p[0],10)||0)*6+Math.floor((parseInt(p[1],10)||0)/10);}' +
    'return Number(e.value);}' +
    'document.getElementById("cancel").onclick=function(){document.location=RET;};' +
    'document.getElementById("save").onclick=function(){var o={},' +
    'els=document.querySelectorAll("[data-key]");for(var i=0;i<els.length;i++){' +
    'o[els[i].getAttribute("data-key")]=val(els[i]);}' +
    'document.location=RET+encodeURIComponent(JSON.stringify(o));};';
  return '<!DOCTYPE html><html lang="en"><head><meta charset="utf-8">' +
    '<meta name="viewport" content="width=device-width,initial-scale=1">' +
    '<title>TimelyNG settings</title><style>' + CSS + '</style></head><body>' +
    '<h1>TimelyNG</h1>' + body +
    '<div class="bar"><button type="button" id="cancel">Cancel</button>' +
    '<button type="button" id="save">Save</button></div>' +
    '<script>' + script + '<\/script></body></html>';
}

module.exports = buildConfigPage;
