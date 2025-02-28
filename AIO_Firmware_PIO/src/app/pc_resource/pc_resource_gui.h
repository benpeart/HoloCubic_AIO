#ifndef APP_WEATHER_GUI_H
#define APP_WEATHER_GUI_H

#define MAX_EXTENSION_NUM 5 // Maximum number of component extensions

// Sensor data, data with one decimal place is multiplied by 10
struct PC_Resource
{
    int cpu_usage; // CPU usage (%)
    int cpu_temp;  // CPU temperature (℃), multiplied by 10
    int cpu_freq;  // CPU frequency (MHz)
    int cpu_power; // CPU power (W), multiplied by 10

    int gpu_usage; // GPU usage (%)
    int gpu_temp;  // GPU temperature (℃), multiplied by 10
    int gpu_power; // GPU power (W), multiplied by 10

    int ram_usage; // RAM usage (%)
    int ram_use;   // RAM usage amount (MB)

    int net_upload_speed;   // Network upload speed (KB/s), multiplied by 10
    int net_download_speed; // Network download speed (KB/s), multiplied by 10
};

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"
    extern const lv_img_dsc_t app_pc_resource;

    // A sensor module for a component, suitable for CPU, GPU, RAM, SSD, HDD, NET
    // Some components may not use certain attributes, such as RAM not using temperature
    typedef struct _sensor_module
    {
        const char *name;            // Component name
        lv_obj_t *module_label;      // Component label
        lv_obj_t *usage_rate_arc;    // Component usage rate, arc tool
        lv_obj_t *usage_rate_label;  // Component usage rate, value display label
        lv_obj_t *buttom_label;      // Component bottom label, value display label
        lv_obj_t *extension_label_1; // Component extension attribute 1, such as CPU frequency, GPU memory usage, SSD read speed, NET upload speed, etc.
        lv_obj_t *extension_label_2; // Component extension attribute 2, such as SSD write speed, NET download speed, etc.
        lv_obj_t *extension_label_3; // Component extension attribute 3
        lv_obj_t *extension_label_4; // Component extension attribute 4
        lv_obj_t *extension_label_5; // Component extension attribute 5

        void (*extension_update[MAX_EXTENSION_NUM])(struct PC_Resource); // Extension attribute update function pointer
    } sensor_module;

    void display_pc_resource_gui_init(void);
    void display_pc_resource_init(void);
    void display_pc_resource(struct PC_Resource sensorInfo);
    void pc_resource_gui_release(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
