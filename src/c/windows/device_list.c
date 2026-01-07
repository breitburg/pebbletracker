#include "device_list.h"
#include "device_detail.h"
#include "../device_data.h"

static Window *s_window;
static MenuLayer *s_menu_layer;
static StatusBarLayer *s_status_bar;

// Get number of sections (categories)
static uint16_t menu_get_num_sections(MenuLayer *menu_layer, void *data) {
  return NUM_CATEGORIES;
}

// Get number of rows in each section
static uint16_t menu_get_num_rows(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return g_categories[section_index].device_count;
}

// Get section header height
static int16_t menu_get_header_height(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

// Get cell height (platform-aware)
static int16_t menu_get_cell_height(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
#ifdef PBL_ROUND
  if (menu_layer_is_index_selected(menu_layer, cell_index)) {
    return MENU_CELL_ROUND_FOCUSED_TALL_CELL_HEIGHT;
  }
  return MENU_CELL_ROUND_UNFOCUSED_SHORT_CELL_HEIGHT;
#else
  return 52;
#endif
}

// Draw section header - white background with accent text, uppercase
static void menu_draw_header(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  GRect bounds = layer_get_bounds(cell_layer);

  // White background with accent text
#ifdef PBL_COLOR
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  graphics_context_set_text_color(ctx, GColorCobaltBlue);
#else
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  graphics_context_set_text_color(ctx, GColorBlack);
#endif

  // Convert title to uppercase
  const char *src = g_categories[section_index].name;
  static char title[32];
  size_t i = 0;
  while (src[i] && i < sizeof(title) - 1) {
    char c = src[i];
    title[i] = (c >= 'a' && c <= 'z') ? (c - 32) : c;
    i++;
  }
  title[i] = '\0';

#ifdef PBL_ROUND
  GRect text_bounds = GRect(0, 0, bounds.size.w, bounds.size.h);
  graphics_draw_text(ctx, title,
                     fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD),
                     text_bounds,
                     GTextOverflowModeTrailingEllipsis,
                     GTextAlignmentCenter,
                     NULL);
#else
  GRect text_bounds = GRect(4, 0, bounds.size.w - 8, bounds.size.h);
  graphics_draw_text(ctx, title,
                     fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD),
                     text_bounds,
                     GTextOverflowModeTrailingEllipsis,
                     GTextAlignmentLeft,
                     NULL);
#endif
}

// Draw each device row
static void menu_draw_row(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  GRect bounds = layer_get_bounds(cell_layer);

  // Get the device for this row
  uint8_t device_idx = g_categories[cell_index->section].device_start_index + cell_index->row;
  const PebbleDevice *device = &g_devices[device_idx];

  // Use menu_cell_layer_is_highlighted for proper animation support
  // MenuLayer handles background colors via menu_layer_set_normal_colors/set_highlight_colors
  bool is_highlighted = menu_cell_layer_is_highlighted(cell_layer);
  graphics_context_set_text_color(ctx, is_highlighted ? GColorWhite : GColorBlack);

  // Create subtitle - keep it simple and Pebble-like
  static char subtitle[32];
  if (device->status == STATUS_CANCELLED) {
    snprintf(subtitle, sizeof(subtitle), "%d · Never shipped", device->release_year);
  } else if (device->form_factor == FORM_WATCH_ROUND) {
    snprintf(subtitle, sizeof(subtitle), "%d · Round", device->release_year);
  } else if (device->form_factor == FORM_RING) {
    snprintf(subtitle, sizeof(subtitle), "%d · Smart ring", device->release_year);
  } else if (device->display_type == DISPLAY_COLOR_EPAPER) {
    snprintf(subtitle, sizeof(subtitle), "%d · Color", device->release_year);
  } else {
    snprintf(subtitle, sizeof(subtitle), "%d", device->release_year);
  }

  // Calculate layout dynamically
  int16_t margin = PBL_IF_ROUND_ELSE(bounds.size.w / 6, 4);
  int16_t text_width = bounds.size.w - (2 * margin);

  GFont title_font = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);

  GFont subtitle_font = fonts_get_system_font(FONT_KEY_GOTHIC_14);

  // Draw title
  GRect title_rect = GRect(margin, 0, text_width, 28);
  graphics_draw_text(ctx, device->model_name,
                     title_font,
                     title_rect,
                     GTextOverflowModeTrailingEllipsis,
                     PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft),
                     NULL);

  // Draw subtitle
  GRect subtitle_rect = GRect(margin, 28, text_width, 18);
  graphics_draw_text(ctx, subtitle,
                     subtitle_font,
                     subtitle_rect,
                     GTextOverflowModeTrailingEllipsis,
                     PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft),
                     NULL);
}

// Handle device selection
static void menu_select_click(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  uint8_t device_idx = g_categories[cell_index->section].device_start_index + cell_index->row;
  device_detail_window_push(device_idx);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create status bar
  s_status_bar = status_bar_layer_create();
#ifdef PBL_COLOR
  status_bar_layer_set_colors(s_status_bar, GColorCobaltBlue, GColorWhite);
#else
  status_bar_layer_set_colors(s_status_bar, GColorWhite, GColorBlack);
#endif
  layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar));

  // Create menu layer below status bar
  GRect menu_bounds = GRect(
    bounds.origin.x,
    bounds.origin.y + STATUS_BAR_LAYER_HEIGHT,
    bounds.size.w,
    bounds.size.h - STATUS_BAR_LAYER_HEIGHT
  );

  s_menu_layer = menu_layer_create(menu_bounds);

  // Hide scroll shadows for cleaner look
  scroll_layer_set_shadow_hidden(menu_layer_get_scroll_layer(s_menu_layer), true);

  // Set callbacks
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks) {
    .get_num_sections = menu_get_num_sections,
    .get_num_rows = menu_get_num_rows,
    .get_header_height = menu_get_header_height,
    .get_cell_height = menu_get_cell_height,
    .draw_header = menu_draw_header,
    .draw_row = menu_draw_row,
    .select_click = menu_select_click,
  });

  // Configure button behavior
  menu_layer_set_click_config_onto_window(s_menu_layer, window);

  // Set colors - enables MenuLayer's built-in highlight animations
#ifdef PBL_COLOR
  menu_layer_set_normal_colors(s_menu_layer, GColorWhite, GColorBlack);
  menu_layer_set_highlight_colors(s_menu_layer, GColorCobaltBlue, GColorWhite);
#else
  menu_layer_set_normal_colors(s_menu_layer, GColorWhite, GColorBlack);
  menu_layer_set_highlight_colors(s_menu_layer, GColorBlack, GColorWhite);
#endif

  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

static void window_unload(Window *window) {
  menu_layer_destroy(s_menu_layer);
  s_menu_layer = NULL;
  status_bar_layer_destroy(s_status_bar);
  s_status_bar = NULL;
}

void device_list_window_push(void) {
  if (!s_window) {
    s_window = window_create();
    window_set_window_handlers(s_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
    });
  }
  window_stack_push(s_window, true);
}
