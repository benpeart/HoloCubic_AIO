#ifndef RGB_H
#define RGB_H

#include <FastLED.h>
#include <esp32-hal-timer.h>

#define RGB_LED_NUM 2

#define LED_MODE_RGB 0
#define LED_MODE_HSV 1

enum LED_RUN_MODE : unsigned char
{
    RUN_MODE_TIMER = 0, // rtos timer
    RUN_MODE_TASK,      // rtos task
    RUN_MODE_NONE
};

class Pixel
{
private:
    CRGB rgb_buffers[RGB_LED_NUM];

public:
    void init();

    Pixel &setRGB(int r, int g, int b);

    Pixel &setHVS(uint8_t ih, uint8_t is, uint8_t iv);

    Pixel &fill_rainbow(int min_r, int max_r,
                        int min_g, int max_g,
                        int min_b, int max_b);

    Pixel &setBrightness(float duty);
};

struct RgbConfig
{
    uint8_t mode;
    uint8_t min_value_0;
    uint8_t min_value_1;
    uint8_t min_value_2;
    uint8_t max_value_0;
    uint8_t max_value_1;
    uint8_t max_value_2;
    int8_t step_0;
    int8_t step_1;
    int8_t step_2;
    uint16_t min_brightness; // Brightness value 0~1000
    uint16_t max_brightness; // Brightness value 0~1000
    uint8_t brightness_step; // Brightness value 0~100
    int time;                // Timer time 10~1000
};

struct RgbParam
{
    uint8_t mode; // 0 for RGB color (LED_MODE_RGB) 1 for HSV color (LED_MODE_HSV)
    union
    {
        uint8_t min_value_r;
        uint8_t min_value_h;
    };
    union
    {
        uint8_t min_value_g;
        uint8_t min_value_s;
    };
    union
    {
        uint8_t min_value_b;
        uint8_t min_value_v;
    };

    union
    {
        uint8_t max_value_r;
        uint8_t max_value_h;
    };
    union
    {
        uint8_t max_value_g;
        uint8_t max_value_s;
    };
    union
    {
        uint8_t max_value_b;
        uint8_t max_value_v;
    };

    union
    {
        int8_t step_r;
        int8_t step_h;
    };
    union
    {
        int8_t step_g;
        int8_t step_s;
    };
    union
    {
        int8_t step_b;
        int8_t step_v;
    };

    uint16_t min_brightness; // Brightness value 0~1000
    uint16_t max_brightness; // Brightness value 0~1000
    uint8_t brightness_step; // Brightness value 0~100

    int time; // Timer time
};

struct RgbRunStatus
{
    union
    {
        uint8_t current_r;
        uint8_t current_h;
    };
    union
    {
        uint8_t current_g;
        uint8_t current_s;
    };
    union
    {
        uint8_t current_b;
        uint8_t current_v;
    };
    uint8_t pos;
    uint16_t current_brightness; // Brightness value 0~1000
};

bool set_rgb_and_run(RgbParam *rgb_setting,
                     LED_RUN_MODE mode = RUN_MODE_TASK);
void rgb_stop(void);

#endif
