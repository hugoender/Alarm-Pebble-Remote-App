#include <pebble.h>
	
static Window *window;

//static TextLayer *text_layer;
static ActionBarLayer *action_bar_layer;
static BitmapLayer *back_ground_layer;

static GBitmap *buttonArm;
static GBitmap *buttonDisarm;
static GBitmap *buttonStay;
static GBitmap *houseAlarmBG;


enum {
	KEY_REQUEST
};

static void out_sent_handler(DictionaryIterator *sent, void *context) {
	//Outgoing message was delivered
	vibes_short_pulse();
}

static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
	//Outgoing message failed to deliver
	vibes_double_pulse();
}

static void send_request(char *request) {
	Tuplet request_tuple = TupletCString(KEY_REQUEST, request);
	
	DictionaryIterator *iter;
	app_message_outbox_begin(&iter);
	
	if (iter == NULL) {
		return;
	}
	
	dict_write_tuplet(iter, &request_tuple);
	dict_write_end(iter);
	
	app_message_outbox_send();
}
	
//buttonArm
static void up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
	send_request("armAlarm");
}

//buttonDisarm
static void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
	send_request("disarmAlarm");
}

//buttonStay
static void down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
	send_request("stayAlarm");
}

static void click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) up_single_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) select_single_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) down_single_click_handler);
}
	
static void window_load(Window *window) {
	//We will add the creation of the Window's elements here!
	
	//!!!Make sure to uncomment destroy code in window unload if you uncomment this block!!!
	/*text_layer = text_layer_create(GRect(0, 45, 132, 168));
	text_layer_set_background_color(text_layer, GColorClear);
	text_layer_set_text_color(text_layer, GColorBlack);
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	
	layer_add_child(window_get_root_layer(window), (Layer*) text_layer);
	
	text_layer_set_text(text_layer, "Single pulse:\nSuccess\n\nDouble pulse:\n Failure");*/
	
	//Load background bitmap into GBitmap structure
	houseAlarmBG = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_HOUSE_ALARM_BG);
	//Create BitmapLayers to show GBitmaps and add to window
	back_ground_layer = bitmap_layer_create(GRect(0,10,120,120));
	bitmap_layer_set_bitmap(back_ground_layer, houseAlarmBG);
	bitmap_layer_set_alignment(back_ground_layer, GAlignCenter);
	//Add back_ground_layer to window
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(back_ground_layer));
	
	//Initialize the action bar
	action_bar_layer = action_bar_layer_create();
	//Associate the action bar with the window
	action_bar_layer_add_to_window(action_bar_layer, window);
	//Set the click config provider
	action_bar_layer_set_click_config_provider(action_bar_layer, (ClickConfigProvider) click_config_provider);
	//Set the icons
	buttonArm = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ARM);
	buttonDisarm = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DISARM);
	buttonStay = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_STAY);
	action_bar_layer_set_icon(action_bar_layer, BUTTON_ID_UP, buttonArm);
	action_bar_layer_set_icon(action_bar_layer, BUTTON_ID_SELECT, buttonDisarm);
	action_bar_layer_set_icon(action_bar_layer, BUTTON_ID_DOWN, buttonStay);	
	//Add action bar to window
	action_bar_layer_add_to_window(action_bar_layer, window);
}

static void window_unload(Window *window) {
	//We will safely destroy the Window's elements here!
	action_bar_layer_destroy(action_bar_layer);
	
	gbitmap_destroy(buttonArm);
	gbitmap_destroy(buttonDisarm);
	gbitmap_destroy(buttonStay);
	
	bitmap_layer_destroy(back_ground_layer);
	
	gbitmap_destroy(houseAlarmBG);
	
	//text_layer_destroy(text_layer);
}

static void app_message_init() {
	app_message_register_outbox_sent(out_sent_handler);
	app_message_register_outbox_failed(out_failed_handler);
	app_message_open(/*app_message_inbox_size_maximum()*/64 /*inbound size*/, /*app_message_outbox_size_maximum()*/64 /*outbound size*/);	
}

static void init() {
	//Initialize the app elements here!
	app_message_init();
	
	window = window_create();
	window_set_window_handlers(window, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload,
	});
	
	window_stack_push(window, true);
}

static void deinit() {
	//De-initialize elements here to save memory!
	window_destroy(window);
}
	
int main(void) {
	init();
	app_event_loop();
	deinit();
}