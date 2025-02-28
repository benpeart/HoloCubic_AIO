#ifndef COMMON_H
#define COMMON_H

#define AIO_VERSION "2.1.12"
#define GET_SYS_MILLIS xTaskGetTickCount // Get system milliseconds
// #define GET_SYS_MILLIS millis            // Get system milliseconds

#include "Arduino.h"
#include "driver/rgb_led.h"
#include "driver/flash_fs.h"
#include "driver/sd_card.h"
#include "driver/display.h"
#include "driver/ambient.h"
#include "driver/imu.h"
#include "network.h"

// RGB
#define RGB_LED_PIN 27

// SD_Card
#define SD_SCK 14
#define SD_MISO 26
#define SD_MOSI 13
#define SD_SS 15

// MUP6050
#define IMU_I2C_SDA 32
#define IMU_I2C_SCL 33

extern IMU mpu; // Principally only for main program calls
extern SdCard tf;
extern Pixel rgb;
// extern Config g_cfg;       // Global configuration file
extern Network g_network;  // Network connection
extern FlashFS g_flashCfg; // File system in flash (replacing the previous Preferences)
extern Display screen;     // Screen object
extern Ambient ambLight;   // Ambient light sensor object

boolean doDelayMillisTime(unsigned long interval,
                          unsigned long *previousMillis,
                          boolean state);

// Ambient light (same as MPU6050)
#define AMB_I2C_SDA 32
#define AMB_I2C_SCL 33

// Screen dimensions
#define SCREEN_HOR_RES 240 // Horizontal
#define SCREEN_VER_RES 240 // Vertical

#define SCREEN_HEIGHT SCREEN_VER_RES
#define SCREEN_WIDTH SCREEN_HOR_RES

// TFT screen interface
// #define PEAK
#ifdef PEAK
#define LCD_BL_PIN 12
/* Battery */
#define CONFIG_BAT_DET_PIN 37
#define CONFIG_BAT_CHG_DET_PIN 38
/* Power */
#define CONFIG_POWER_EN_PIN 21
#define CONFIG_ENCODER_PUSH_PIN 27
#else
#define LCD_BL_PIN 5
#endif

#define LCD_BL_PWM_CHANNEL 0

// Priority definition (the smaller the value, the lower the priority)
// Highest is configMAX_PRIORITIES-1
#define TASK_RGB_PRIORITY 0  // RGB task priority
#define TASK_LVGL_PRIORITY 2 // LVGL page priority

// lvgl operation lock
extern SemaphoreHandle_t lvgl_mutex;
// Safe macros for LVGL operations (to avoid dirty data)
#define AIO_LVGL_OPERATE_LOCK(CODE)                          \
    if (pdTRUE == xSemaphoreTake(lvgl_mutex, portMAX_DELAY)) \
    {                                                        \
        CODE;                                                \
        xSemaphoreGive(lvgl_mutex);                          \
    }

struct SysUtilConfig
{
    String ssid_0;
    String password_0;
    String ssid_1;
    String password_1;
    String ssid_2;
    String password_2;
    String auto_start_app;        // The name of the app that starts automatically at boot
    uint8_t power_mode;           // Power consumption mode (0 for energy-saving mode, 1 for performance mode)
    uint8_t backLight;            // Screen brightness (1-100)
    uint8_t rotation;             // Screen rotation direction
    uint8_t auto_calibration_mpu; // Whether to automatically calibrate the gyroscope: 0 to disable automatic calibration, 1 to enable automatic calibration
    uint8_t mpu_order;            // Operation direction
};

#define GFX 0

#if GFX
#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS -1 // Not connected
#define TFT_DC 2
#define TFT_RST 4 // Connect reset to ensure display initialises
#include <Arduino_GFX_Library.h>
extern Arduino_HWSPI *bus;
extern Arduino_ST7789 *tft;

#else
#include <TFT_eSPI.h>
/*
TFT pins should be set in path/to/Arduino/libraries/TFT_eSPI/User_Setups/Setup24_ST7789.h
*/
extern TFT_eSPI *tft;
#endif

#endif