#include <pebble.h>
#include "windows/device_list.h"

static void prv_init(void) {
  // Push the main device list
  device_list_window_push();
}

static void prv_deinit(void) {
  // Window cleanup handled by window_unload callbacks
}

int main(void) {
  prv_init();
  app_event_loop();
  prv_deinit();
}
