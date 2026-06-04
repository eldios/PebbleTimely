/* Timely header file - structs and function prototypes
 * ( to be split out into pieces, for dynamic overlays, at a later date )
 */

// Create a struct to hold our persistent settings...
#include "settings.h"

#include "locale.h"

#include "debug.h"



#include "weather.h"

char *translate_error(AppMessageResult result);
struct tm *get_time();
void splash_layer_update_callback(Layer *me, GContext* ctx);
void calendar_layer_update_callback(Layer *me, GContext* ctx);
void update_date_text();
void update_time_text();
void update_day_text(TextLayer *which_layer);
void update_month_text(TextLayer *which_layer);
void update_week_text(TextLayer *which_layer);
void update_ampm_text(TextLayer *which_layer);
void update_seconds_text(TextLayer *which_layer);
char * get_doy_text();
char * get_dliy_text();
void update_doy_text(TextLayer *which_layer);
void update_dliy_text(TextLayer *which_layer);
void update_doy_dliy_text(TextLayer *which_layer);
void update_timezone_text(TextLayer *which_layer);
void process_show_week();
void process_show_day();
void process_show_ampm();
void position_connection_layer();
void position_date_layer();
void position_day_layer();
void position_time_layer();
void update_datetime_subtext();
void datetime_layer_update_callback(Layer *me, GContext* ctx);
void statusbar_visible();
void toggle_weather();
void toggle_statusbar();
void slot_status_layer_update_callback(Layer *me, GContext* ctx);
void statusbar_layer_update_callback(Layer *me, GContext* ctx);
void slot_top_layer_update_callback(Layer *me, GContext* ctx);
void slot_bot_layer_update_callback(Layer *me, GContext* ctx);
void battery_layer_update_callback(Layer *me, GContext* ctx);
static void request_weather(void *data);
static void request_timezone(void *data);
static void watch_version_send(void *data);
static void battery_status_send(void *data);
void set_status_charging_icon();
static void toggle_slot_bottom(void *data);
static void handle_battery(BatteryChargeState charge_state);
void generate_vibe(uint32_t vibe_pattern_number);
void update_connection();
static void handle_bluetooth(bool connected);
static void set_unifont();
bool period_check(uint8_t start_incr, uint8_t stop_incr, bool retval_on_equal);
bool dnd_period_check();
bool hourvibe_period_check();
void set_layer_attr(TextLayer *textlayer, GTextAlignment Alignment);
void set_layer_attr_sfont(TextLayer *textlayer, char *font_key, GTextAlignment Alignment);
void set_layer_attr_cfont(TextLayer *textlayer, uint32_t FontResHandle, GTextAlignment Alignment);
static void window_load(Window *window);
static void window_unload(Window *window);
static void deinit(void);
void handle_vibe_suppression();
static int need_second_tick_handler(void);
static void switch_tick_handler(void);
void my_out_sent_handler(DictionaryIterator *sent, void *context);
void my_out_fail_handler(DictionaryIterator *failed, AppMessageResult reason, void *context);
void in_js_ready_handler(DictionaryIterator *received, void *context);
void in_weather_handler(DictionaryIterator *received, void *context);
void in_timezone_handler(DictionaryIterator *received, void *context);
void in_configuration_handler(DictionaryIterator *received, void *context);
void my_in_rcv_handler(DictionaryIterator *received, void *context);
void my_in_drp_handler(AppMessageResult reason, void *context);
static void app_message_init(void);
static void init(void);
int main(void);
