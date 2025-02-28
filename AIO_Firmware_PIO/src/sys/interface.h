#ifndef INTERFACE_H
#define INTERFACE_H

enum APP_MESSAGE_TYPE
{
    APP_MESSAGE_WIFI_CONN = 0, // Start connection
    APP_MESSAGE_WIFI_AP,       // Start AP event
    APP_MESSAGE_WIFI_ALIVE,    // WiFi switch heartbeat maintenance
    APP_MESSAGE_WIFI_DISCONN,  // Connection disconnected
    APP_MESSAGE_UPDATE_TIME,
    APP_MESSAGE_MQTT_DATA, // MQTT client received message
    APP_MESSAGE_GET_PARAM, // Get parameters
    APP_MESSAGE_SET_PARAM, // Set parameters
    APP_MESSAGE_READ_CFG,  // Read parameters from disk
    APP_MESSAGE_WRITE_CFG, // Write parameters to disk

    APP_MESSAGE_NONE
};

enum APP_TYPE
{
    APP_TYPE_REAL_TIME = 0, // Real-time application
    APP_TYPE_BACKGROUND,    // Background application

    APP_TYPE_NONE
};

class AppController;
struct ImuAction;

struct APP_OBJ
{
    // Application name and title
    const char *app_name;

    // APP image storage address, APP application icon 128*128
    const void *app_image;

    // Other information about the application such as author, version number, etc.
    const char *app_info;

    // APP initialization function, can also be empty or do nothing (equivalent to the Arduino setup() function)
    int (*app_init)(AppController *sys);

    // Main program function entry pointer of the APP
    void (*main_process)(AppController *sys,
                         const ImuAction *act_info);

    // Entry pointer of the APP task (generally called once within a minute)
    void (*background_task)(AppController *sys,
                            const ImuAction *act_info);

    // Callback function to be processed before exiting, can be empty
    int (*exit_callback)(void *param);

    // Message handling mechanism
    void (*message_handle)(const char *from, const char *to,
                           APP_MESSAGE_TYPE type, void *message,
                           void *ext_info);
};

#endif // INTERFACE_H