#include "splash.h"
#include "theme.h"
#include "layout.h"

// Version shown on the loading splash. Keep in sync with package.json "version".
#define APP_VERSION "0.0.7"

static Layer *s_splash_layer;

static void splash_render(Layer *me, GContext* ctx) {
  (void)me;
  int w = layout_get().slot_bot.w; // full width: center the splash on any screen
  setColors(ctx);
  graphics_draw_text(ctx, "TimelyNG", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), GRect(0,0,w,36), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  graphics_draw_text(ctx, APP_VERSION, fonts_get_system_font(FONT_KEY_GOTHIC_28), GRect(0,32,w,36), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
}

void splash_create(Layer *parent, GRect frame) {
  s_splash_layer = layer_create(frame);
  layer_set_update_proc(s_splash_layer, splash_render);
  layer_add_child(parent, s_splash_layer);
}
void splash_destroy(void)            { layer_destroy(s_splash_layer); }
void splash_set_hidden(bool hidden)  { layer_set_hidden(s_splash_layer, hidden); }
void splash_set_frame(GRect frame)   { layer_set_frame(s_splash_layer, frame); }
