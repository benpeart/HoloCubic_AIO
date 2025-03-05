#include "rgb_led.h"
#include "common.h"
#include <Arduino.h>

void Pixel::init()
{
    FastLED.addLeds<WS2812, RGB_LED_PIN, GRB>(rgb_buffers, RGB_LED_NUM);
    FastLED.setBrightness(200);
}

Pixel &Pixel::setRGB(int r, int g, int b)
{
    for (int pos = 0; pos < RGB_LED_NUM; ++pos)
    {
        rgb_buffers[pos] = CRGB(r, g, b);
    }
    FastLED.show();

    return *this;
}

Pixel &Pixel::setHVS(uint8_t ih, uint8_t is, uint8_t iv)
{
    for (int pos = 0; pos < RGB_LED_NUM; ++pos)
    {
        rgb_buffers[pos].setHSV(ih, is, iv);
    }
    FastLED.show();

    return *this;
}

Pixel &Pixel::fill_rainbow(int min_r, int max_r,
                           int min_g, int max_g,
                           int min_b, int max_b)
{
    fill_gradient(rgb_buffers, 0, CHSV(50, 255, 255), 29, CHSV(150, 255, 255), SHORTEST_HUES);
    FastLED.show();

    return *this;
}

Pixel &Pixel::setBrightness(float duty)
{
    duty = constrain(duty, 0, 1);
    FastLED.setBrightness((uint8_t)(255 * duty));
    FastLED.show();

    return *this;
}

LED_RUN_MODE run_mode = RUN_MODE_NONE;
RgbParam g_rgb;
RgbRunStatus rgb_status;
BaseType_t taskRgbReturned;
TaskHandle_t handleLed = NULL;
TimerHandle_t xTimer_rgb = NULL;

void led_timerHandler(TimerHandle_t xTimer);
void led_taskHandler(void *parameter);
static void hsvModeChange(void);
static void rgbModeChange(void);
static void onceChange(void);
static void count_cur_brightness(void);

bool set_rgb_and_run(RgbParam *rgb_setting, LED_RUN_MODE mode)
{
    if (RUN_MODE_NONE <= mode)
    {
        // Creation failed
        return false;
    }

    if (run_mode != mode)
    {
        // Running mode has changed
        rgb_stop();
        run_mode = mode;
    }

    g_rgb = *rgb_setting;

    // Copy data
    if (LED_MODE_RGB == g_rgb.mode)
    {
        rgb_status.current_r = g_rgb.min_value_r;
        rgb_status.current_g = g_rgb.min_value_g;
        rgb_status.current_b = g_rgb.min_value_b;
        rgb_status.current_brightness = g_rgb.min_brightness;
        rgb_status.pos = 0;
    }
    else if (LED_MODE_HSV == g_rgb.mode)
    {
        rgb_status.current_h = g_rgb.min_value_h;
        rgb_status.current_s = g_rgb.min_value_s;
        rgb_status.current_v = g_rgb.min_value_v;
        rgb_status.current_brightness = g_rgb.min_brightness;
        rgb_status.pos = 0;
    }

    // Choose to start two running modes
    if (RUN_MODE_TIMER == run_mode)
    {
        if (NULL != xTimer_rgb)
        {
            xTimerStop(xTimer_rgb, 0);
            xTimer_rgb = NULL;
        }
        xTimer_rgb = xTimerCreate("led_timerHandler",
                                  g_rgb.time / portTICK_PERIOD_MS,
                                  pdTRUE, (void *)0, led_timerHandler);
        xTimerStart(xTimer_rgb, 0); // Start the timer
    }
    else if (RUN_MODE_TASK == run_mode)
    {
        if (NULL == handleLed)
        {
            taskRgbReturned = xTaskCreate(
                led_taskHandler,
                "led_taskHandler",
                8 * 128, // Actually 7*128 is enough
                (void *)&g_rgb.time,
                TASK_RGB_PRIORITY,
                &handleLed);
            if (taskRgbReturned != pdPASS)
            {
                return false;
            }
        }
    }
    return true;
}

void led_timerHandler(TimerHandle_t xTimer)
{
    onceChange();
}

void led_taskHandler(void *parameter)
{
    int *ms = (int *)parameter; // Control time
    for (;;)
    {
        onceChange();
        vTaskDelay(*ms);

        // if (pdTRUE == xSemaphoreTake(lvgl_mutex, portMAX_DELAY))
        // {
        //     lv_task_handler();
        //     xSemaphoreGive(lvgl_mutex);
        // }
    }
}

static void onceChange(void)
{
    if (LED_MODE_RGB == g_rgb.mode)
    {
        rgbModeChange();
    }
    else if (LED_MODE_HSV == g_rgb.mode)
    {
        hsvModeChange();
    }
}

static void hsvModeChange(void)
{
    // Control of HSV color
    rgb_status.current_h += g_rgb.step_h;
    if (rgb_status.current_h >= g_rgb.max_value_h)
    {
        g_rgb.step_h = (-1) * g_rgb.step_h;
        rgb_status.current_h = g_rgb.max_value_h;
    }
    else if (rgb_status.current_h <= g_rgb.min_value_h)
    {
        g_rgb.step_h = (-1) * g_rgb.step_h;
        rgb_status.current_h = g_rgb.min_value_h;
    }

    rgb_status.current_s += g_rgb.step_s;
    if (rgb_status.current_s >= g_rgb.max_value_s)
    {
        g_rgb.step_s = (-1) * g_rgb.step_s;
        rgb_status.current_s = g_rgb.max_value_s;
    }
    else if (rgb_status.current_s <= g_rgb.min_value_s)
    {
        g_rgb.step_s = (-1) * g_rgb.step_s;
        rgb_status.current_s = g_rgb.min_value_s;
    }

    rgb_status.current_v += g_rgb.step_v;
    if (rgb_status.current_v >= g_rgb.max_value_v)
    {
        g_rgb.step_v = (-1) * g_rgb.step_v;
        rgb_status.current_v = g_rgb.max_value_v;
    }
    else if (rgb_status.current_v <= g_rgb.min_value_v)
    {
        g_rgb.step_v = (-1) * g_rgb.step_v;
        rgb_status.current_v = g_rgb.min_value_v;
    }

    // Calculate the current backlight value
    count_cur_brightness();

    // Set HSV status
    rgb.setHVS(rgb_status.current_h,
               rgb_status.current_s,
               rgb_status.current_v)
        .setBrightness(rgb_status.current_brightness / 1000.0f);
}

static void rgbModeChange(void)
{
    // Control of RGB color
    if (0 == rgb_status.pos) // Control to R
    {
        rgb_status.current_r += g_rgb.step_r;
        if (rgb_status.current_r >= g_rgb.max_value_r && g_rgb.step_r > 0)
        {
            rgb_status.pos = 1;
            rgb_status.current_r = g_rgb.max_value_r;
        }
        else if (rgb_status.current_r <= g_rgb.min_value_r && g_rgb.step_r < 0)
        {
            g_rgb.step_r = (-1) * g_rgb.step_r;
            rgb_status.current_r = g_rgb.min_value_r;
        }
    }
    else if (1 == rgb_status.pos) // Control to G
    {
        rgb_status.current_g += g_rgb.step_r;
        if (rgb_status.current_g >= g_rgb.max_value_g && g_rgb.step_r > 0)
        {
            rgb_status.pos = 2;
            rgb_status.current_g = g_rgb.max_value_g;
        }
        else if (rgb_status.current_g <= g_rgb.min_value_g && g_rgb.step_r < 0)
        {
            rgb_status.pos = 0;
            rgb_status.current_g = g_rgb.min_value_g;
        }
    }
    else if (2 == rgb_status.pos) // Control to B
    {
        rgb_status.current_b += g_rgb.step_r;
        if (rgb_status.current_b >= g_rgb.max_value_b && g_rgb.step_r > 0)
        {
            g_rgb.step_r = (-1) * g_rgb.step_r;
            rgb_status.current_b = g_rgb.max_value_b;
        }
        else if (rgb_status.current_b <= g_rgb.min_value_b && g_rgb.step_r < 0)
        {
            rgb_status.pos = 1;
            rgb_status.current_b = g_rgb.min_value_b;
        }
    }

    // Calculate the current backlight value
    count_cur_brightness();

    // Set RGB status
    rgb.setRGB(rgb_status.current_r,
               rgb_status.current_g,
               rgb_status.current_b)
        .setBrightness(rgb_status.current_brightness / 1000.0f);
}

static void count_cur_brightness(void)
{
    // Control of backlight
    if (g_rgb.max_brightness == g_rgb.min_brightness)
    {
        rgb_status.current_brightness = g_rgb.max_brightness;
        return;
    }

    rgb_status.current_brightness += g_rgb.brightness_step;
    if (rgb_status.current_brightness >= g_rgb.max_brightness)
    {
        rgb_status.current_brightness = g_rgb.max_brightness;
        g_rgb.brightness_step = (-1) * g_rgb.brightness_step;
    }
    else if (rgb_status.current_brightness <= g_rgb.min_brightness)
    {
        rgb_status.current_brightness = g_rgb.min_brightness;
        g_rgb.brightness_step = (-1) * g_rgb.brightness_step;
    }
}

void rgb_stop(void)
{
    if (RUN_MODE_TIMER == run_mode &&
        NULL != xTimer_rgb)
    {
        xTimerStop(xTimer_rgb, 0);
        xTimer_rgb = NULL;
    }

    if (RUN_MODE_TASK == run_mode &&
        NULL != handleLed)
    {
        vTaskDelete(handleLed);
        handleLed = NULL;
    }
}