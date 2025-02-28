#include "common.h"
#include "network.h"

IMU mpu;
SdCard tf;
Pixel rgb;
// Global configuration file
Network g_network;  // Network connection
FlashFS g_flashCfg; // File system in flash (replacing the original Preferences)
Display screen;     // Screen object
Ambient ambLight;   // Ambient light sensor object

// lvgl handle lock
SemaphoreHandle_t lvgl_mutex = xSemaphoreCreateMutex();

boolean doDelayMillisTime(unsigned long interval, unsigned long *previousMillis, boolean state)
{
    unsigned long currentMillis = GET_SYS_MILLIS();
    if (currentMillis - *previousMillis >= interval)
    {
        *previousMillis = currentMillis;
        state = !state;
    }
    return state;
}

#if GFX

#include <Arduino_GFX_Library.h>

Arduino_HWSPI *bus = new Arduino_HWSPI(TFT_DC /* DC */, TFT_CS /* CS */, TFT_SCLK, TFT_MOSI, TFT_MISO);
Arduino_ST7789 *tft = new Arduino_ST7789(bus, TFT_RST /* RST */, 3 /* rotation */, true /* IPS */,
                                         240 /* width */, 240 /* height */,
                                         0 /* col offset 1 */, 80 /* row offset 1 */);

#else
#include <TFT_eSPI.h>
/*
TFT pins should be set in path/to/Arduino/libraries/TFT_eSPI/User_Setups/Setup24_ST7789.h
*/
TFT_eSPI *tft = new TFT_eSPI(SCREEN_HOR_RES, SCREEN_VER_RES);
#endif