#include "device_data.h"
#include <string.h>

const uint8_t NUM_DEVICES = 13;
const uint8_t NUM_CATEGORIES = 6;

// Categories with device indices (sections in MenuLayer)
const DeviceCategory g_categories[] = {
  { "Original Pebbles",    0, 2 },  // Classic, Steel
  { "Pebble Time Series",  2, 3 },  // Time, Time Steel, Time Round
  { "Pebble 2 Series",     5, 2 },  // Pebble 2, Pebble 2 SE
  { "Core Watches",        7, 3 },  // 2 Duo, Time 2, Round 2
  { "Other Devices",      10, 1 },  // Index 01
  { "Cancelled",          11, 2 }   // Pebble Time 2 (2016), Pebble Core
};

// All devices in order matching category indices
const PebbleDevice g_devices[] = {
  // ===== Original Pebbles (0-1) =====
  {
    .model_name = "Pebble Classic",
    .release_year = 2013,
    .manufacturer = MANUFACTURER_PEBBLE_TECH,
    .status = STATUS_RELEASED,
    .platform = PLATFORM_APLITE,
    .form_factor = FORM_WATCH_RECT,
    .display_width = 144,
    .display_height = 168,
    .display_size_tenths = 126,
    .display_type = DISPLAY_BW_EPAPER,
    .colors = 2,
    .processor = "Cortex-M3 @ 80MHz",
    .battery_mah = 130,
    .battery_days = 7,
    .water_resist_m = 50,
    .sensors = SENSOR_ACCELEROMETER | SENSOR_COMPASS | SENSOR_AMBIENT_LIGHT,
    .body_material = "Polycarbonate",
    .colors_available = "Black, White, Red, Orange, Grey",
    .original_price_usd = 150,
    .notable_features = "First Pebble, Kickstarter record $10.3M"
  },
  {
    .model_name = "Pebble Steel",
    .release_year = 2014,
    .manufacturer = MANUFACTURER_PEBBLE_TECH,
    .status = STATUS_RELEASED,
    .platform = PLATFORM_APLITE,
    .form_factor = FORM_WATCH_RECT,
    .display_width = 144,
    .display_height = 168,
    .display_size_tenths = 126,
    .display_type = DISPLAY_BW_EPAPER,
    .colors = 2,
    .processor = "Cortex-M3 @ 80MHz",
    .battery_mah = 130,
    .battery_days = 7,
    .water_resist_m = 50,
    .sensors = SENSOR_ACCELEROMETER | SENSOR_COMPASS | SENSOR_AMBIENT_LIGHT,
    .body_material = "Stainless Steel",
    .colors_available = "Brushed Steel, Matte Black",
    .original_price_usd = 249,
    .notable_features = "Premium steel body, Gorilla Glass"
  },

  // ===== Pebble Time Series (2-4) =====
  {
    .model_name = "Pebble Time",
    .release_year = 2015,
    .manufacturer = MANUFACTURER_PEBBLE_TECH,
    .status = STATUS_RELEASED,
    .platform = PLATFORM_BASALT,
    .form_factor = FORM_WATCH_RECT,
    .display_width = 144,
    .display_height = 168,
    .display_size_tenths = 125,
    .display_type = DISPLAY_COLOR_EPAPER,
    .colors = 64,
    .processor = "Cortex-M4 @ 100MHz",
    .battery_mah = 150,
    .battery_days = 7,
    .water_resist_m = 30,
    .sensors = SENSOR_ACCELEROMETER | SENSOR_COMPASS | SENSOR_AMBIENT_LIGHT | SENSOR_MICROPHONE,
    .body_material = "Polycarbonate",
    .colors_available = "Black, White, Red",
    .original_price_usd = 199,
    .notable_features = "First color Pebble, Timeline UI, Kickstarter $20.4M"
  },
  {
    .model_name = "Pebble Time Steel",
    .release_year = 2015,
    .manufacturer = MANUFACTURER_PEBBLE_TECH,
    .status = STATUS_RELEASED,
    .platform = PLATFORM_BASALT,
    .form_factor = FORM_WATCH_RECT,
    .display_width = 144,
    .display_height = 168,
    .display_size_tenths = 125,
    .display_type = DISPLAY_COLOR_EPAPER,
    .colors = 64,
    .processor = "Cortex-M4 @ 100MHz",
    .battery_mah = 150,
    .battery_days = 10,
    .water_resist_m = 30,
    .sensors = SENSOR_ACCELEROMETER | SENSOR_COMPASS | SENSOR_AMBIENT_LIGHT | SENSOR_MICROPHONE,
    .body_material = "Stainless Steel",
    .colors_available = "Silver, Black, Gold",
    .original_price_usd = 299,
    .notable_features = "Premium build, 10-day battery, smart straps port"
  },
  {
    .model_name = "Pebble Time Round",
    .release_year = 2015,
    .manufacturer = MANUFACTURER_PEBBLE_TECH,
    .status = STATUS_RELEASED,
    .platform = PLATFORM_CHALK,
    .form_factor = FORM_WATCH_ROUND,
    .display_width = 180,
    .display_height = 180,
    .display_size_tenths = 100,
    .display_type = DISPLAY_COLOR_EPAPER,
    .colors = 64,
    .processor = "Cortex-M4 @ 100MHz",
    .battery_mah = 55,
    .battery_days = 2,
    .water_resist_m = 30,
    .sensors = SENSOR_ACCELEROMETER | SENSOR_COMPASS | SENSOR_AMBIENT_LIGHT | SENSOR_MICROPHONE,
    .body_material = "Stainless Steel",
    .colors_available = "Silver, Black, Rose Gold",
    .original_price_usd = 249,
    .notable_features = "Thinnest smartwatch ever at 7.5mm, round display"
  },

  // ===== Pebble 2 Series (5-6) =====
  {
    .model_name = "Pebble 2",
    .release_year = 2016,
    .manufacturer = MANUFACTURER_PEBBLE_TECH,
    .status = STATUS_RELEASED,
    .platform = PLATFORM_DIORITE,
    .form_factor = FORM_WATCH_RECT,
    .display_width = 144,
    .display_height = 168,
    .display_size_tenths = 126,
    .display_type = DISPLAY_BW_EPAPER,
    .colors = 2,
    .processor = "Cortex-M4 @ 100MHz",
    .battery_mah = 130,
    .battery_days = 7,
    .water_resist_m = 30,
    .sensors = SENSOR_ACCELEROMETER | SENSOR_COMPASS | SENSOR_MICROPHONE | SENSOR_HEART_RATE,
    .body_material = "Polycarbonate",
    .colors_available = "Black, White, Aqua, Flame, Lime",
    .original_price_usd = 129,
    .notable_features = "First Pebble with heart rate monitor"
  },
  {
    .model_name = "Pebble 2 SE",
    .release_year = 2016,
    .manufacturer = MANUFACTURER_PEBBLE_TECH,
    .status = STATUS_RELEASED,
    .platform = PLATFORM_DIORITE,
    .form_factor = FORM_WATCH_RECT,
    .display_width = 144,
    .display_height = 168,
    .display_size_tenths = 126,
    .display_type = DISPLAY_BW_EPAPER,
    .colors = 2,
    .processor = "Cortex-M4 @ 100MHz",
    .battery_mah = 130,
    .battery_days = 7,
    .water_resist_m = 30,
    .sensors = SENSOR_ACCELEROMETER | SENSOR_COMPASS | SENSOR_MICROPHONE,
    .body_material = "Polycarbonate",
    .colors_available = "Black, White",
    .original_price_usd = 99,
    .notable_features = "Budget option without heart rate sensor"
  },

  // ===== Core Watches (7-9) =====
  {
    .model_name = "Pebble 2 Duo",
    .release_year = 2025,
    .manufacturer = MANUFACTURER_CORE_DEVICES,
    .status = STATUS_RELEASED,
    .platform = PLATFORM_FLINT,
    .form_factor = FORM_WATCH_RECT,
    .display_width = 144,
    .display_height = 168,
    .display_size_tenths = 126,
    .display_type = DISPLAY_BW_EPAPER,
    .colors = 2,
    .processor = "nRF52840 BLE",
    .battery_mah = 200,
    .battery_days = 30,
    .water_resist_m = 50,
    .sensors = SENSOR_ACCELEROMETER | SENSOR_GYROSCOPE | SENSOR_COMPASS | SENSOR_BAROMETER | SENSOR_MICROPHONE | SENSOR_SPEAKER,
    .body_material = "Polycarbonate",
    .colors_available = "White, Black",
    .original_price_usd = 149,
    .notable_features = "Open source PebbleOS, 30-day battery, RGB backlight"
  },
  {
    .model_name = "Pebble Time 2",
    .release_year = 2025,
    .manufacturer = MANUFACTURER_CORE_DEVICES,
    .status = STATUS_RELEASED,
    .platform = PLATFORM_EMERY,
    .form_factor = FORM_WATCH_RECT,
    .display_width = 200,
    .display_height = 228,
    .display_size_tenths = 150,
    .display_type = DISPLAY_COLOR_EPAPER,
    .colors = 64,
    .processor = "nRF52840 BLE",
    .battery_mah = 250,
    .battery_days = 30,
    .water_resist_m = 50,
    .sensors = SENSOR_ACCELEROMETER | SENSOR_GYROSCOPE | SENSOR_COMPASS | SENSOR_HEART_RATE | SENSOR_MICROPHONE | SENSOR_SPEAKER,
    .body_material = "Stainless Steel 316",
    .colors_available = "Silver, Black, Gold, Rose Gold",
    .original_price_usd = 225,
    .notable_features = "First PebbleOS touchscreen, 53% larger display"
  },
  {
    .model_name = "Pebble Round 2",
    .release_year = 2026,
    .manufacturer = MANUFACTURER_CORE_DEVICES,
    .status = STATUS_PREORDER,
    .platform = PLATFORM_CHALK,
    .form_factor = FORM_WATCH_ROUND,
    .display_width = 260,
    .display_height = 260,
    .display_size_tenths = 130,
    .display_type = DISPLAY_COLOR_EPAPER,
    .colors = 64,
    .processor = "nRF52840 BLE",
    .battery_mah = 150,
    .battery_days = 14,
    .water_resist_m = 30,
    .sensors = SENSOR_ACCELEROMETER | SENSOR_COMPASS | SENSOR_MICROPHONE,
    .body_material = "Stainless Steel",
    .colors_available = "Silver, Black",
    .original_price_usd = 199,
    .notable_features = "283 DPI display, touchscreen, 8.1mm thin"
  },

  // ===== Other Devices (10) =====
  {
    .model_name = "Pebble Index 01",
    .release_year = 2026,
    .manufacturer = MANUFACTURER_CORE_DEVICES,
    .status = STATUS_PREORDER,
    .platform = PLATFORM_NONE,
    .form_factor = FORM_RING,
    .display_width = 0,
    .display_height = 0,
    .display_size_tenths = 0,
    .display_type = DISPLAY_NONE,
    .colors = 0,
    .processor = "BLE chip",
    .battery_mah = 0,
    .battery_days = 730,
    .water_resist_m = 50,
    .sensors = SENSOR_MICROPHONE,
    .body_material = "Stainless Steel",
    .colors_available = "Silver, Gold, Matte Black",
    .original_price_usd = 75,
    .notable_features = "Smart ring, voice notes, 2-year battery, 2.5mm thin"
  },

  // ===== Cancelled (11-12) =====
  {
    .model_name = "Pebble Time 2 (2016)",
    .release_year = 2016,
    .manufacturer = MANUFACTURER_PEBBLE_TECH,
    .status = STATUS_CANCELLED,
    .platform = PLATFORM_EMERY,
    .form_factor = FORM_WATCH_RECT,
    .display_width = 200,
    .display_height = 228,
    .display_size_tenths = 150,
    .display_type = DISPLAY_COLOR_EPAPER,
    .colors = 64,
    .processor = "Cortex-M4 @ 100MHz",
    .battery_mah = 180,
    .battery_days = 10,
    .water_resist_m = 30,
    .sensors = SENSOR_ACCELEROMETER | SENSOR_COMPASS | SENSOR_MICROPHONE | SENSOR_HEART_RATE,
    .body_material = "Stainless Steel",
    .colors_available = "Silver, Black, Gold",
    .original_price_usd = 199,
    .notable_features = "Never released - Fitbit acquisition ended production"
  },
  {
    .model_name = "Pebble Core",
    .release_year = 2016,
    .manufacturer = MANUFACTURER_PEBBLE_TECH,
    .status = STATUS_CANCELLED,
    .platform = PLATFORM_NONE,
    .form_factor = FORM_RING,  // Closest match - small wearable
    .display_width = 0,
    .display_height = 0,
    .display_size_tenths = 0,
    .display_type = DISPLAY_NONE,
    .colors = 0,
    .processor = "Android 5.0",
    .battery_mah = 0,
    .battery_days = 1,
    .water_resist_m = 0,
    .sensors = SENSOR_MICROPHONE | SENSOR_SPEAKER,
    .body_material = "Plastic",
    .colors_available = "Black",
    .original_price_usd = 69,
    .notable_features = "GPS, 3G, Spotify offline, Alexa, hackable - never shipped"
  }
};

// Helper function implementations
const char* platform_to_string(PebblePlatform platform) {
  switch (platform) {
    case PLATFORM_APLITE:  return "aplite";
    case PLATFORM_BASALT:  return "basalt";
    case PLATFORM_CHALK:   return "chalk";
    case PLATFORM_DIORITE: return "diorite";
    case PLATFORM_EMERY:   return "emery";
    case PLATFORM_FLINT:   return "flint";
    case PLATFORM_NONE:    return "n/a";
    default:               return "unknown";
  }
}

const char* manufacturer_to_string(Manufacturer manufacturer) {
  switch (manufacturer) {
    case MANUFACTURER_PEBBLE_TECH:  return "Pebble Technology";
    case MANUFACTURER_CORE_DEVICES: return "Core Devices";
    default:                        return "Unknown";
  }
}

const char* status_to_string(DeviceStatus status) {
  switch (status) {
    case STATUS_RELEASED:  return "Released";
    case STATUS_CANCELLED: return "Cancelled";
    case STATUS_PREORDER:  return "Pre-order";
    default:               return "Unknown";
  }
}

const char* display_type_to_string(DisplayType type) {
  switch (type) {
    case DISPLAY_BW_EPAPER:    return "B/W e-paper";
    case DISPLAY_COLOR_EPAPER: return "Color e-paper";
    case DISPLAY_NONE:         return "No display";
    default:                   return "Unknown";
  }
}

const char* form_factor_to_string(FormFactor form) {
  switch (form) {
    case FORM_WATCH_RECT:  return "Rectangular Watch";
    case FORM_WATCH_ROUND: return "Round Watch";
    case FORM_RING:        return "Smart Ring";
    default:               return "Unknown";
  }
}

void sensors_to_string(uint8_t sensors, char *buffer, size_t size) {
  buffer[0] = '\0';
  bool first = true;

  if (sensors & SENSOR_ACCELEROMETER) {
    strncat(buffer, "Accelerometer", size - strlen(buffer) - 1);
    first = false;
  }
  if (sensors & SENSOR_GYROSCOPE) {
    if (!first) strncat(buffer, ", ", size - strlen(buffer) - 1);
    strncat(buffer, "Gyroscope", size - strlen(buffer) - 1);
    first = false;
  }
  if (sensors & SENSOR_COMPASS) {
    if (!first) strncat(buffer, ", ", size - strlen(buffer) - 1);
    strncat(buffer, "Compass", size - strlen(buffer) - 1);
    first = false;
  }
  if (sensors & SENSOR_BAROMETER) {
    if (!first) strncat(buffer, ", ", size - strlen(buffer) - 1);
    strncat(buffer, "Barometer", size - strlen(buffer) - 1);
    first = false;
  }
  if (sensors & SENSOR_HEART_RATE) {
    if (!first) strncat(buffer, ", ", size - strlen(buffer) - 1);
    strncat(buffer, "Heart Rate", size - strlen(buffer) - 1);
    first = false;
  }
  if (sensors & SENSOR_MICROPHONE) {
    if (!first) strncat(buffer, ", ", size - strlen(buffer) - 1);
    strncat(buffer, "Microphone", size - strlen(buffer) - 1);
    first = false;
  }
  if (sensors & SENSOR_SPEAKER) {
    if (!first) strncat(buffer, ", ", size - strlen(buffer) - 1);
    strncat(buffer, "Speaker", size - strlen(buffer) - 1);
    first = false;
  }
  if (sensors & SENSOR_AMBIENT_LIGHT) {
    if (!first) strncat(buffer, ", ", size - strlen(buffer) - 1);
    strncat(buffer, "Light Sensor", size - strlen(buffer) - 1);
    first = false;
  }

  if (first) {
    strncpy(buffer, "None", size);
  }
}
