#include "theme.h"
#include "ui.h"

void setColors(GContext* ctx) {
    window_set_background_color(window, GColorBlack);
    graphics_context_set_stroke_color(ctx, GColorWhite);
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_context_set_text_color(ctx, GColorWhite);
}

void setInvColors(GContext* ctx) {
    window_set_background_color(window, GColorWhite);
    graphics_context_set_stroke_color(ctx, GColorBlack);
    graphics_context_set_fill_color(ctx, GColorWhite);
    graphics_context_set_text_color(ctx, GColorBlack);
}

// Highlight for today's calendar cell: accent fill on color hardware (tune
// GColorJaegerGreen to taste), classic white-on-black inversion on B&W.
void setTodayColors(GContext* ctx) {
    window_set_background_color(window, PBL_IF_COLOR_ELSE(GColorBlack, GColorWhite));
    graphics_context_set_stroke_color(ctx, PBL_IF_COLOR_ELSE(GColorWhite, GColorBlack));
    graphics_context_set_fill_color(ctx, PBL_IF_COLOR_ELSE(GColorJaegerGreen, GColorWhite));
    graphics_context_set_text_color(ctx, PBL_IF_COLOR_ELSE(GColorWhite, GColorBlack));
}
