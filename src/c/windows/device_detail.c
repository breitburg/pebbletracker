#include "device_detail.h"
#include "../device_data.h"
#include <stdio.h>

static Window *s_window;
static ScrollLayer *s_scroll_layer;
static Layer *s_content_layer;
static StatusBarLayer *s_status_bar;
static uint8_t s_device_index;

// Pre-formatted text buffers
static char s_display_line[48];
static char s_battery_line[32];
static char s_water_line[32];
static char s_sensors_buffer[128];
static char s_price_line[24];

// Content height calculation
static int16_t s_content_height;

// Helper to draw a section header
static void draw_section_header(GContext *ctx, const char *title, int16_t y, GRect bounds) {
  int16_t margin = PBL_IF_ROUND_ELSE(bounds.size.w / 6, 4);

#ifdef PBL_COLOR
  graphics_context_set_text_color(ctx, GColorCobaltBlue);
#else
  graphics_context_set_text_color(ctx, GColorBlack);
#endif

  GRect header_rect = GRect(margin, y, bounds.size.w - (2 * margin), 22);
  graphics_draw_text(ctx, title,
                     fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD),
                     header_rect,
                     GTextOverflowModeTrailingEllipsis,
                     PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft),
                     NULL);
}

// Helper to draw a detail line and return height used
static int16_t draw_detail_line(GContext *ctx, const char *text, int16_t y, GRect bounds) {
  int16_t margin = PBL_IF_ROUND_ELSE(bounds.size.w / 6, 4);
  int16_t text_width = bounds.size.w - (2 * margin);

  graphics_context_set_text_color(ctx, GColorBlack);

  GFont font = fonts_get_system_font(FONT_KEY_GOTHIC_14);

  // Calculate text height
  GSize text_size = graphics_text_layout_get_content_size(
    text, font, GRect(0, 0, text_width, 200),
    GTextOverflowModeWordWrap, GTextAlignmentLeft
  );

  int16_t height = text_size.h + 2;

  GRect text_rect = GRect(margin, y, text_width, height);
  graphics_draw_text(ctx, text,
                     font,
                     text_rect,
                     GTextOverflowModeWordWrap,
                     PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft),
                     NULL);

  return height + 2;
}

// Calculate total content height
static int16_t calculate_content_height(const PebbleDevice *device, GRect bounds) {
  int16_t margin = PBL_IF_ROUND_ELSE(bounds.size.w / 6, 4);
  int16_t text_width = bounds.size.w - (2 * margin);
  GFont body_font = fonts_get_system_font(FONT_KEY_GOTHIC_14);

  int16_t y = 0;

  // Title
  y += 30;

  // Year line
  y += 20;

  y += 8;

  // DISPLAY section (if applicable)
  if (device->display_type != DISPLAY_NONE) {
    y += 24; // Header
    y += 18; // Resolution line
    y += 18; // Size line
    y += 8;
  }

  // HARDWARE section
  y += 24; // Header
  y += 18; // Processor

  // Battery line
  GSize battery_size = graphics_text_layout_get_content_size(
    s_battery_line, body_font, GRect(0, 0, text_width, 100),
    GTextOverflowModeWordWrap, GTextAlignmentLeft
  );
  y += battery_size.h + 4;

  if (device->water_resist_m > 0) {
    y += 18;
  }

  y += 8;

  // SENSORS section
  y += 24; // Header
  GSize sensors_size = graphics_text_layout_get_content_size(
    s_sensors_buffer, body_font, GRect(0, 0, text_width, 200),
    GTextOverflowModeWordWrap, GTextAlignmentLeft
  );
  y += sensors_size.h + 4;
  y += 8;

  // BODY section
  y += 24; // Header
  y += 18; // Material
  GSize colors_size = graphics_text_layout_get_content_size(
    device->colors_available, body_font, GRect(0, 0, text_width, 100),
    GTextOverflowModeWordWrap, GTextAlignmentLeft
  );
  y += colors_size.h + 4;
  y += 8;

  // DETAILS section
  y += 24; // Header
  y += 18; // Price
  GSize features_size = graphics_text_layout_get_content_size(
    device->notable_features, body_font, GRect(0, 0, text_width, 200),
    GTextOverflowModeWordWrap, GTextAlignmentLeft
  );
  y += features_size.h + 4;

  y += 20; // Bottom padding

  return y;
}

// Content layer update proc - draws all device details
static void content_layer_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  const PebbleDevice *device = &g_devices[s_device_index];

  int16_t margin = PBL_IF_ROUND_ELSE(bounds.size.w / 6, 4);
  int16_t text_width = bounds.size.w - (2 * margin);
  int16_t y = 0;

  // Draw device title
  graphics_context_set_text_color(ctx, GColorBlack);
  GRect title_rect = GRect(margin, y, text_width, 28);
  graphics_draw_text(ctx, device->model_name,
                     fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD),
                     title_rect,
                     GTextOverflowModeTrailingEllipsis,
                     PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft),
                     NULL);
  y += 30;

  // Simple year line with status if notable
  static char year_line[32];
  if (device->status == STATUS_CANCELLED) {
    snprintf(year_line, sizeof(year_line), "%d · Never shipped", device->release_year);
  } else {
    snprintf(year_line, sizeof(year_line), "%d · %s",
             device->release_year,
             manufacturer_to_string(device->manufacturer));
  }
  y += draw_detail_line(ctx, year_line, y, bounds);

  y += 8;

  // DISPLAY section (only for watches)
  if (device->display_type != DISPLAY_NONE) {
    draw_section_header(ctx, "DISPLAY", y, bounds);
    y += 24;

    snprintf(s_display_line, sizeof(s_display_line), "%dx%d %s, %d colors",
             device->display_width, device->display_height,
             display_type_to_string(device->display_type),
             device->colors);
    y += draw_detail_line(ctx, s_display_line, y, bounds);

    static char size_line[24];
    snprintf(size_line, sizeof(size_line), "%d.%02d\" diagonal",
             device->display_size_tenths / 100,
             device->display_size_tenths % 100);
    y += draw_detail_line(ctx, size_line, y, bounds);

    y += 8;
  }

  // HARDWARE section
  draw_section_header(ctx, "HARDWARE", y, bounds);
  y += 24;

  y += draw_detail_line(ctx, device->processor, y, bounds);

  if (device->battery_days >= 365) {
    snprintf(s_battery_line, sizeof(s_battery_line), "~%d year battery (non-rechargeable)",
             device->battery_days / 365);
  } else if (device->battery_mah > 0) {
    snprintf(s_battery_line, sizeof(s_battery_line), "%dmAh battery, ~%d days",
             device->battery_mah, device->battery_days);
  } else {
    snprintf(s_battery_line, sizeof(s_battery_line), "~%d days battery life",
             device->battery_days);
  }
  y += draw_detail_line(ctx, s_battery_line, y, bounds);

  if (device->water_resist_m > 0) {
    snprintf(s_water_line, sizeof(s_water_line), "Water resistant: %dm",
             device->water_resist_m);
    y += draw_detail_line(ctx, s_water_line, y, bounds);
  }

  y += 8;

  // SENSORS section
  draw_section_header(ctx, "SENSORS", y, bounds);
  y += 24;

  sensors_to_string(device->sensors, s_sensors_buffer, sizeof(s_sensors_buffer));
  y += draw_detail_line(ctx, s_sensors_buffer, y, bounds);

  y += 8;

  // BODY section
  draw_section_header(ctx, "BODY", y, bounds);
  y += 24;

  y += draw_detail_line(ctx, device->body_material, y, bounds);
  y += draw_detail_line(ctx, device->colors_available, y, bounds);

  y += 8;

  // DETAILS section
  draw_section_header(ctx, "DETAILS", y, bounds);
  y += 24;

  snprintf(s_price_line, sizeof(s_price_line), "Original price: $%d",
           device->original_price_usd);
  y += draw_detail_line(ctx, s_price_line, y, bounds);

  y += draw_detail_line(ctx, device->notable_features, y, bounds);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  const PebbleDevice *device = &g_devices[s_device_index];

  // Create status bar
  s_status_bar = status_bar_layer_create();
#ifdef PBL_COLOR
  status_bar_layer_set_colors(s_status_bar, GColorCobaltBlue, GColorWhite);
#else
  status_bar_layer_set_colors(s_status_bar, GColorWhite, GColorBlack);
#endif
  layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar));

  // Calculate content area bounds (below status bar)
  GRect scroll_bounds = GRect(
    bounds.origin.x,
    bounds.origin.y + STATUS_BAR_LAYER_HEIGHT,
    bounds.size.w,
    bounds.size.h - STATUS_BAR_LAYER_HEIGHT
  );

  // Pre-format strings for height calculation
  if (device->battery_days >= 365) {
    snprintf(s_battery_line, sizeof(s_battery_line), "~%d year battery (non-rechargeable)",
             device->battery_days / 365);
  } else if (device->battery_mah > 0) {
    snprintf(s_battery_line, sizeof(s_battery_line), "%dmAh battery, ~%d days",
             device->battery_mah, device->battery_days);
  } else {
    snprintf(s_battery_line, sizeof(s_battery_line), "~%d days battery life",
             device->battery_days);
  }
  sensors_to_string(device->sensors, s_sensors_buffer, sizeof(s_sensors_buffer));

  // Calculate content height
  s_content_height = calculate_content_height(device, scroll_bounds);

  // Create scroll layer
  s_scroll_layer = scroll_layer_create(scroll_bounds);
  scroll_layer_set_click_config_onto_window(s_scroll_layer, window);
  scroll_layer_set_shadow_hidden(s_scroll_layer, true);

  // Create content layer
  GRect content_bounds = GRect(0, 0, scroll_bounds.size.w, s_content_height);
  s_content_layer = layer_create(content_bounds);
  layer_set_update_proc(s_content_layer, content_layer_update_proc);

  // Set content size and add to scroll layer
  scroll_layer_set_content_size(s_scroll_layer, GSize(scroll_bounds.size.w, s_content_height));
  scroll_layer_add_child(s_scroll_layer, s_content_layer);

  layer_add_child(window_layer, scroll_layer_get_layer(s_scroll_layer));
}

static void window_unload(Window *window) {
  layer_destroy(s_content_layer);
  s_content_layer = NULL;
  scroll_layer_destroy(s_scroll_layer);
  s_scroll_layer = NULL;
  status_bar_layer_destroy(s_status_bar);
  s_status_bar = NULL;
}

void device_detail_window_push(uint8_t device_index) {
  s_device_index = device_index;

  if (!s_window) {
    s_window = window_create();
    window_set_window_handlers(s_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
    });
  }

  // Force window reload to update content
  if (window_stack_contains_window(s_window)) {
    window_stack_remove(s_window, false);
  }

  window_stack_push(s_window, true);
}
