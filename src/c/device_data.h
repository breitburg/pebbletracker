#pragma once

#include <pebble.h>

// Platform codenames
typedef enum {
  PLATFORM_APLITE,    // Pebble Classic, Steel
  PLATFORM_BASALT,    // Pebble Time, Time Steel
  PLATFORM_CHALK,     // Pebble Time Round
  PLATFORM_DIORITE,   // Pebble 2, 2 SE
  PLATFORM_EMERY,     // Pebble Time 2 (cancelled)
  PLATFORM_FLINT,     // Core Pebble 2 Duo
  PLATFORM_NONE       // Non-watch devices (Index 01)
} PebblePlatform;

// Manufacturer
typedef enum {
  MANUFACTURER_PEBBLE_TECH,  // Pebble Technology Corp (2013-2016)
  MANUFACTURER_CORE_DEVICES  // Core Devices Inc (2025-2026)
} Manufacturer;

// Device status
typedef enum {
  STATUS_RELEASED,
  STATUS_CANCELLED,
  STATUS_PREORDER
} DeviceStatus;

// Display type
typedef enum {
  DISPLAY_BW_EPAPER,      // Black/White e-paper
  DISPLAY_COLOR_EPAPER,   // 64-color e-paper
  DISPLAY_NONE            // No display (Index 01)
} DisplayType;

// Device form factor
typedef enum {
  FORM_WATCH_RECT,
  FORM_WATCH_ROUND,
  FORM_RING
} FormFactor;

// Sensor bit flags
#define SENSOR_ACCELEROMETER  (1 << 0)
#define SENSOR_COMPASS        (1 << 1)
#define SENSOR_MICROPHONE     (1 << 2)
#define SENSOR_HEART_RATE     (1 << 3)
#define SENSOR_AMBIENT_LIGHT  (1 << 4)
#define SENSOR_SPEAKER        (1 << 5)
#define SENSOR_BAROMETER      (1 << 6)
#define SENSOR_GYROSCOPE      (1 << 7)

// Category structure
typedef struct {
  const char *name;
  uint8_t device_start_index;
  uint8_t device_count;
} DeviceCategory;

// Main device structure
typedef struct {
  const char *model_name;
  uint16_t release_year;
  Manufacturer manufacturer;
  DeviceStatus status;
  PebblePlatform platform;
  FormFactor form_factor;

  // Display specs
  uint16_t display_width;
  uint16_t display_height;
  uint8_t display_size_tenths;  // Size in tenths of inch (e.g., 126 = 1.26")
  DisplayType display_type;
  uint8_t colors;               // 2 or 64

  // Hardware
  const char *processor;
  uint16_t battery_mah;
  uint16_t battery_days;
  uint8_t water_resist_m;

  // Sensors
  uint8_t sensors;

  // Physical
  const char *body_material;
  const char *colors_available;
  uint16_t original_price_usd;

  // Features
  const char *notable_features;
} PebbleDevice;

// External declarations
extern const PebbleDevice g_devices[];
extern const DeviceCategory g_categories[];
extern const uint8_t NUM_DEVICES;
extern const uint8_t NUM_CATEGORIES;

// Helper functions
const char* platform_to_string(PebblePlatform platform);
const char* manufacturer_to_string(Manufacturer manufacturer);
const char* status_to_string(DeviceStatus status);
const char* display_type_to_string(DisplayType type);
const char* form_factor_to_string(FormFactor form);
void sensors_to_string(uint8_t sensors, char *buffer, size_t size);
