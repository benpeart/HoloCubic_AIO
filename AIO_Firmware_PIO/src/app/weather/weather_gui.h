#ifndef APP_WEATHER_GUI_H
#define APP_WEATHER_GUI_H

#define FORECAST_DAYS 4 // Total number of forecast days

struct Weather
{

    int weather_code; // Weather phenomenon code
    int temperature;  // Temperature
    int humidity;     // Humidity
    int maxTemp;      // Maximum temperature
    int minTemp;      // Minimum temperature

    int windLevel;
    int airQulity;

    char windDir[20];
    char cityname[10];  // City name
    char windpower[10]; // Wind power
    char weather[25];   // Weather phenomenon

    short daily_max[FORECAST_DAYS];
    short daily_min[FORECAST_DAYS];
};

struct TimeStr
{
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int weekday;
};

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"

#define ANIEND                      \
    while (lv_anim_count_running()) \
        lv_task_handler(); // Wait for animation to complete

    void weather_gui_init(void);
    void display_curve_init(lv_scr_load_anim_t anim_type);
    void display_curve(short maxT[], short minT[], lv_scr_load_anim_t anim_type);
    void display_weather_init(lv_scr_load_anim_t anim_type);
    void display_weather(struct Weather weaInfo, lv_scr_load_anim_t anim_type);
    void display_time(struct TimeStr timeInfo, lv_scr_load_anim_t anim_type);
    void weather_gui_release(void);
    void weather_gui_del(void);
    void display_space(void);
    // int airQulityLevel(int q);
    int airQulityLevel(char *q);

#ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"
    extern const lv_img_dsc_t app_weather;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif