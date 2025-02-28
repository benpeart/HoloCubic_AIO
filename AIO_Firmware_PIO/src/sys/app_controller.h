#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include "Arduino.h"
#include "interface.h" // Include the new header file
#include "driver/imu.h"
#include "common.h"
#include <list>

#define CTRL_NAME "AppCtrl"
#define APP_MAX_NUM 20             // Maximum number of runnable apps
#define WIFI_LIFE_CYCLE 60000      // WiFi lifecycle (60s)
#define MQTT_ALIVE_CYCLE 1000      // MQTT reconnection cycle
#define EVENT_LIST_MAX_LENGTH 10   // Message queue capacity
#define APP_CONTROLLER_NAME_LEN 16 // App controller name length

// struct EVENT_OBJ
// {
//     const APP_OBJ *from;   // App sending the request
//     const APP_OBJ *to;     // App receiving the request
//     APP_MESSAGE_TYPE type; // App message type
//     unsigned int id;       // Request ID
//     void *message;         // Attached data, can be any type
// };

struct EVENT_OBJ
{
    const APP_OBJ *from;       // App sending the request
    APP_MESSAGE_TYPE type;     // App event type
    void *info;                // Information carried by the request
    uint8_t retryMaxNum;       // Maximum retry count
    uint8_t retryCount;        // Retry count
    unsigned long nextRunTime; // Timestamp for the next run
};

class AppController
{
public:
    AppController(const char *name = CTRL_NAME);
    ~AppController();
    void init(void);
    void Display(void); // Display interface
    int app_auto_start();
    // Register the app to the app_controller
    int app_install(APP_OBJ *app,
                    APP_TYPE app_type = APP_TYPE_REAL_TIME);
    // Uninstall (delete) the app from the app_controller
    int app_uninstall(const APP_OBJ *app);
    // Remove the app's background task from the task queue (can only be removed by the app itself when exiting)
    int remove_backgroud_task(void);
    int main_process(ImuAction *act_info);
    void app_exit(void); // System call provided for app exit
    // Message sending
    int send_to(const char *from, const char *to,
                APP_MESSAGE_TYPE type, void *message,
                void *ext_info);
    void deal_config(APP_MESSAGE_TYPE type,
                     const char *key, char *value);
    // Event handling
    int req_event_deal(void);
    bool wifi_event(APP_MESSAGE_TYPE type); // WiFi event handling
    void read_config(SysUtilConfig *cfg);
    void write_config(SysUtilConfig *cfg);
    void read_config(SysMpuConfig *cfg);
    void write_config(SysMpuConfig *cfg);
    void read_config(RgbConfig *cfg);
    void write_config(RgbConfig *cfg);

private:
    APP_OBJ *getAppByName(const char *name);
    int getAppIdxByName(const char *name);
    int app_is_legal(const APP_OBJ *app_obj);

private:
    char name[APP_CONTROLLER_NAME_LEN]; // App controller name
    APP_OBJ *appList[APP_MAX_NUM];      // Reserved APP_MAX_NUM app registration slots
    APP_TYPE appTypeList[APP_MAX_NUM];  // Corresponding app running types
    // std::list<const APP_OBJ *> app_list; // App registration slots (abandoned linked list for C language portability)
    std::list<EVENT_OBJ> eventList;   // Used to store events
    boolean m_wifi_status;            // Indicates WiFi status, true for on, false for off
    unsigned long m_preWifiReqMillis; // Saves the timestamp of the last request
    unsigned int app_num;
    boolean app_exit_flag; // Indicates whether to exit the app
    int cur_app_index;     // Current running app index
    int pre_app_index;     // Previous running app index

    TimerHandle_t xTimerEventDeal; // Event handling timer

public:
    SysUtilConfig sys_cfg;
    SysMpuConfig mpu_cfg;
    RgbConfig rgb_cfg;
};

#endif