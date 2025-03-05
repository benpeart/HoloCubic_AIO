#include "server.h"
#include "server_gui.h"
#include "web_setting.h"
#include "sys/app_controller.h"
#include "app/app_conf.h"
#include "network.h"
#include "common.h"

#define SERVER_REFLUSH_INTERVAL 5000UL // Configuration page refresh interval (5s)
#define DNS_PORT 53                    // DNS port
WebServer server(80);

// DNSServer dnsServer;

struct ServerAppRunData
{
    boolean web_start;                    // Flag to indicate whether the web server service is started, 0 for off, 1 for on
    boolean req_sent;                     // Flag to indicate whether the WiFi request service is sent, 0 for off, 1 for on
    unsigned long serverReflushPreMillis; // Time of the last update
};

static ServerAppRunData *run_data = NULL;

void start_web_config()
{
    // Home page
    server.on("/", HTTP_GET, HomePage);

    init_page_header();
    init_page_footer();
    server.on("/download", File_Download);
    server.on("/upload", File_Upload);
    server.on("/delete", File_Delete);
    server.on("/delete_result", delete_result);

    server.on("/sys_setting", sys_setting);
    server.on("/rgb_setting", rgb_setting);
#if APP_WEATHER_USE
    server.on("/weather_setting", weather_setting);
#endif
#if APP_WEATHER_OLD_USE
    server.on("/weather_old_setting", weather_old_setting);
#endif
#if APP_BILIBILI_FANS_USE
    server.on("/bili_setting", bili_setting);
#endif
#if APP_STOCK_MARKET_USE
    server.on("/stock_setting", stock_setting);
#endif
#if APP_PICTURE_USE
    server.on("/picture_setting", picture_setting);
#endif
#if APP_MEDIA_PLAYER_USE
    server.on("/media_setting", media_setting);
#endif
#if APP_SCREEN_SHARE_USE
    server.on("/screen_setting", screen_setting);
#endif
#if APP_HEARTBEAT_USE
    server.on("/heartbeat_setting", heartbeat_setting);
#endif
#if APP_ANNIVERSARY_USE
    server.on("/anniversary_setting", anniversary_setting);
#endif
#if APP_PC_RESOURCE_USE
    server.on("/pc_resource_setting", pc_resource_setting);
#endif

    server.on(
        "/fupload", HTTP_POST,
        []()
        { server.send(200); },
        handleFileUpload);

    // Connection
    server.on("/saveSysConf", saveSysConf);
    server.on("/saveRgbConf", saveRgbConf);
#if APP_WEATHER_USE
    server.on("/saveWeatherConf", saveWeatherConf);
#endif
#if APP_WEATHER_OLD_USE
    server.on("/saveWeatherOldConf", saveWeatherOldConf);
#endif
#if APP_BILIBILI_FANS_USE
    server.on("/saveBiliConf", saveBiliConf);
#endif
#if APP_STOCK_MARKET_USE
    server.on("/saveStockConf", saveStockConf);
#endif
#if APP_PICTURE_USE
    server.on("/savePictureConf", savePictureConf);
#endif
#if APP_MEDIA_PLAYER_USE
    server.on("/saveMediaConf", saveMediaConf);
#endif
#if APP_SCREEN_SHARE_USE
    server.on("/saveScreenConf", saveScreenConf);
#endif
#if APP_HEARTBEAT_USE
    server.on("/saveHeartbeatConf", saveHeartbeatConf);
#endif
#if APP_ANNIVERSARY_USE
    server.on("/saveAnniversaryConf", saveAnniversaryConf);
#endif
#if APP_PC_RESOURCE_USE
    server.on("/savePCResourceConf", savePCResourceConf);
#endif

    server.begin();
    // MDNS.addService("http", "tcp", 80);
    Serial.println("HTTP server started");

    // dnsServer.start(DNS_PORT, "*", gateway);
}

void stop_web_config()
{
    run_data->web_start = 0;
    run_data->req_sent = 0;
    server.stop();
    server.close();
}

static int server_init(AppController *sys)
{
    server_gui_init();
    // Initialize runtime parameters
    run_data = (ServerAppRunData *)malloc(sizeof(ServerAppRunData));
    run_data->web_start = 0;
    run_data->req_sent = 0;
    run_data->serverReflushPreMillis = 0;
    return 0;
}

static void server_process(AppController *sys,
                           const ImuAction *action)
{
    lv_scr_load_anim_t anim_type = LV_SCR_LOAD_ANIM_NONE;

    if (RETURN == action->active)
    {
        stop_web_config();
        sys->app_exit();
        return;
    }

    if (0 == run_data->web_start && 0 == run_data->req_sent)
    {
        // Pre-display
        display_setting(
            "WebServer Start",
            "Domain: holocubic",
            "Wait...", "Wait...",
            // "", "",
            LV_SCR_LOAD_ANIM_NONE);
        // If the web service is not started and the AP start request is not sent, message here has no effect (fill 0)
        sys->send_to(SERVER_APP_NAME, CTRL_NAME,
                     APP_MESSAGE_WIFI_AP, NULL, NULL);
        run_data->req_sent = 1; // Mark the AP start request as sent
    }
    else if (1 == run_data->web_start)
    {
        server.handleClient(); // Must be placed in the loop to scan
        // dnsServer.processNextRequest();
        if (doDelayMillisTime(SERVER_REFLUSH_INTERVAL, &run_data->serverReflushPreMillis, false) == true)
        {
            // Send WiFi keep-alive heartbeat
            sys->send_to(SERVER_APP_NAME, CTRL_NAME,
                         APP_MESSAGE_WIFI_ALIVE, NULL, NULL);

            display_setting(
                "WebServer Start",
                "Domain: holocubic",
                WiFi.localIP().toString().c_str(),
                WiFi.softAPIP().toString().c_str(),
                LV_SCR_LOAD_ANIM_NONE);
        }
    }
}

static void server_background_task(AppController *sys,
                                   const ImuAction *act_info)
{
    // This function is a background task, the main controller will call this function every minute
    // This function should try to only call "resident data", other variables may have been released due to lifecycle reasons
}

static int server_exit_callback(void *param)
{
    setting_gui_del();

    // Release runtime data
    if (NULL != run_data)
    {
        free(run_data);
        run_data = NULL;
    }
    return 0;
}

static void server_message_handle(const char *from, const char *to,
                                  APP_MESSAGE_TYPE type, void *message,
                                  void *ext_info)
{
    switch (type)
    {
    case APP_MESSAGE_WIFI_AP:
    {
        Serial.print(F("APP_MESSAGE_WIFI_AP enable\n"));
        display_setting(
            "WebServer Start",
            "Domain: holocubic",
            WiFi.localIP().toString().c_str(),
            WiFi.softAPIP().toString().c_str(),
            LV_SCR_LOAD_ANIM_NONE);
        start_web_config();
        run_data->web_start = 1;
    }
    break;
    case APP_MESSAGE_WIFI_ALIVE:
    {
        // WiFi keep-alive response, no need to handle
    }
    break;
    default:
        break;
    }
}

APP_OBJ server_app = {SERVER_APP_NAME, &app_server, "",
                      server_init, server_process, server_background_task,
                      server_exit_callback, server_message_handle};
