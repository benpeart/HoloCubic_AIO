#include "app_controller.h"
#include "app_controller_gui.h"
#include "common.h"
#include "interface.h"
#include "Arduino.h"

const char *app_event_type_info[] = {"APP_MESSAGE_WIFI_CONN", "APP_MESSAGE_WIFI_AP",
                                     "APP_MESSAGE_WIFI_ALIVE", "APP_MESSAGE_WIFI_DISCONN",
                                     "APP_MESSAGE_UPDATE_TIME", "APP_MESSAGE_MQTT_DATA",
                                     "APP_MESSAGE_GET_PARAM", "APP_MESSAGE_SET_PARAM",
                                     "APP_MESSAGE_READ_CFG", "APP_MESSAGE_WRITE_CFG",
                                     "APP_MESSAGE_NONE"};

volatile static bool isRunEventDeal = false;

// TickType_t mainFormRefreshLastTime;
// const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
// mainFormRefreshLastTime = xTaskGetTickCount();
// vTaskDelayUntil(&mainFormRefreshLastTime, xDelay500ms);

void eventDealHandle(TimerHandle_t xTimer)
{
    isRunEventDeal = true;
}

AppController::AppController(const char *name)
{
    strncpy(this->name, name, APP_CONTROLLER_NAME_LEN);
    app_num = 0;
    app_exit_flag = 0;
    cur_app_index = 0;
    pre_app_index = 0;
    // appList = new APP_OBJ[APP_MAX_NUM];
    m_wifi_status = false;
    m_preWifiReqMillis = GET_SYS_MILLIS();

    // Define an event handling timer
    xTimerEventDeal = xTimerCreate("Event Deal",
                                   300 / portTICK_PERIOD_MS,
                                   pdTRUE, (void *)0, eventDealHandle);
    // Start the event handling timer
    xTimerStart(xTimerEventDeal, 0);
}

void AppController::init(void)
{
    // Set CPU frequency
    if (1 == this->sys_cfg.power_mode)
    {
        setCpuFrequencyMhz(240);
    }
    else
    {
        setCpuFrequencyMhz(80);
    }
    // uint32_t freq = getXtalFrequencyMhz(); // In MHz
    Serial.print(F("CpuFrequencyMhz: "));
    Serial.println(getCpuFrequencyMhz());

    app_control_gui_init();
    appList[0] = new APP_OBJ();
    appList[0]->app_image = &app_loading;
    appList[0]->app_name = "Loading...";
    appTypeList[0] = APP_TYPE_REAL_TIME;
    app_control_display_scr(appList[cur_app_index]->app_image,
                            appList[cur_app_index]->app_name,
                            LV_SCR_LOAD_ANIM_NONE, true);
    // Display();
}

void AppController::Display()
{
    // appList[0].app_image = &app_loading;
    app_control_display_scr(appList[cur_app_index]->app_image,
                            appList[cur_app_index]->app_name,
                            LV_SCR_LOAD_ANIM_NONE, true);
}

AppController::~AppController()
{
    rgb_stop();
}

int AppController::app_is_legal(const APP_OBJ *app_obj)
{
    // Check the legality of the APP
    if (NULL == app_obj)
        return 1;
    if (APP_MAX_NUM <= app_num)
        return 2;
    return 0;
}

// Install the APP into the app_controller
int AppController::app_install(APP_OBJ *app, APP_TYPE app_type)
{
    int ret_code = app_is_legal(app);
    if (0 != ret_code)
    {
        return ret_code;
    }

    appList[app_num] = app;
    appTypeList[app_num] = app_type;
    ++app_num;
    return 0; // Installation successful
}

// Remove the APP's background task from the task queue (can only be removed by the app itself when exiting)
int AppController::remove_backgroud_task(void)
{
    return 0; // Installation successful
}

// Uninstall (delete) the APP from the app_controller
int AppController::app_uninstall(const APP_OBJ *app)
{
    // todo
    return 0;
}

int AppController::app_auto_start()
{
    // APP auto start
    int index = this->getAppIdxByName(sys_cfg.auto_start_app.c_str());
    if (index < 0)
    {
        // No related APP found
        return 0;
    }
    // Enter the auto-start APP
    app_exit_flag = 1; // Enter the app, if already in
    cur_app_index = index;
    (*(appList[cur_app_index]->app_init))(this); // Execute APP initialization
    return 0;
}

int AppController::main_process(ImuAction *act_info)
{
    if (ACTIVE_TYPE::UNKNOWN != act_info->active)
    {
        Serial.print(F("[Operate]\tact_info->active: "));
        Serial.println(active_type_info[act_info->active]);
    }

    if (isRunEventDeal)
    {
        isRunEventDeal = false;
        // Scan events
        this->req_event_deal();
    }

    // WiFi auto-off (in power-saving mode)
    if (0 == sys_cfg.power_mode && true == m_wifi_status && doDelayMillisTime(WIFI_LIFE_CYCLE, &m_preWifiReqMillis, false))
    {
        send_to(CTRL_NAME, CTRL_NAME, APP_MESSAGE_WIFI_DISCONN, 0, NULL);
    }

    if (0 == app_exit_flag)
    {
        // Currently not in any app
        lv_scr_load_anim_t anim_type = LV_SCR_LOAD_ANIM_NONE;
        if (ACTIVE_TYPE::TURN_LEFT == act_info->active)
        {
            anim_type = LV_SCR_LOAD_ANIM_MOVE_RIGHT;
            pre_app_index = cur_app_index;
            cur_app_index = (cur_app_index + 1) % app_num;
            Serial.println(String("Current App: ") + appList[cur_app_index]->app_name);
        }
        else if (ACTIVE_TYPE::TURN_RIGHT == act_info->active)
        {
            anim_type = LV_SCR_LOAD_ANIM_MOVE_LEFT;
            pre_app_index = cur_app_index;
            // Equivalent to processId = (processId - 1 + APP_NUM) % 4;
            // +3 to prevent data overflow to negative numbers, causing modulo logic errors
            cur_app_index = (cur_app_index - 1 + app_num) % app_num; // Here 3 is consistent with the length of p_processList
            Serial.println(String("Current App: ") + appList[cur_app_index]->app_name);
        }
        else if (ACTIVE_TYPE::GO_FORWORD == act_info->active)
        {
            app_exit_flag = 1; // Enter the app
            if (NULL != appList[cur_app_index]->app_init)
            {
                (*(appList[cur_app_index]->app_init))(this); // Execute APP initialization
            }
        }

        if (ACTIVE_TYPE::GO_FORWORD != act_info->active) // && UNKNOWN != act_info->active
        {
            app_control_display_scr(appList[cur_app_index]->app_image,
                                    appList[cur_app_index]->app_name,
                                    anim_type, false);
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
    }
    else
    {
        app_control_display_scr(appList[cur_app_index]->app_image,
                                appList[cur_app_index]->app_name,
                                LV_SCR_LOAD_ANIM_NONE, false);
        // Run the APP process, equivalent to handing over control to the current APP
        (*(appList[cur_app_index]->main_process))(this, act_info);
    }
    act_info->active = ACTIVE_TYPE::UNKNOWN;
    act_info->isValid = 0;
    return 0;
}

APP_OBJ *AppController::getAppByName(const char *name)
{
    for (int pos = 0; pos < app_num; ++pos)
    {
        if (!strcmp(name, appList[pos]->app_name))
        {
            return appList[pos];
        }
    }

    return NULL;
}

int AppController::getAppIdxByName(const char *name)
{
    for (int pos = 0; pos < app_num; ++pos)
    {
        if (!strcmp(name, appList[pos]->app_name))
        {
            return pos;
        }
    }

    return -1;
}

// Communication center (message forwarding)
int AppController::send_to(const char *from, const char *to,
                           APP_MESSAGE_TYPE type, void *message,
                           void *ext_info)
{
    APP_OBJ *fromApp = getAppByName(from); // From whom, may be NULL
    APP_OBJ *toApp = getAppByName(to);     // To whom, may be NULL
    if (type <= APP_MESSAGE_MQTT_DATA)
    {
        // Update the requester of the event
        if (eventList.size() > EVENT_LIST_MAX_LENGTH)
        {
            return 1;
        }
        // Message sent to the controller (currently all WiFi events)
        EVENT_OBJ new_event = {fromApp, type, message, 3, 0, 0};
        eventList.push_back(new_event);
        Serial.print("[EVENT]\tAdd -> " + String(app_event_type_info[type]));
        Serial.print(F("\tEventList Size: "));
        Serial.println(eventList.size());
    }
    else
    {
        // Messages between apps
        if (NULL != toApp)
        {
            Serial.print("[Massage]\tFrom " + String(fromApp->app_name) + "\tTo " + String(toApp->app_name) + "\n");
            if (NULL != toApp->message_handle)
            {
                toApp->message_handle(from, to, type, message, ext_info);
            }
        }
        else if (!strcmp(to, CTRL_NAME))
        {
            Serial.print("[Massage]\tFrom " + String(fromApp->app_name) + "\tTo " + CTRL_NAME + "\n");
            deal_config(type, (const char *)message, (char *)ext_info);
        }
    }
    return 0;
}

int AppController::req_event_deal(void)
{
    // Request event handling
    for (std::list<EVENT_OBJ>::iterator event = eventList.begin(); event != eventList.end();)
    {
        if ((*event).nextRunTime > GET_SYS_MILLIS())
        {
            ++event;
            continue;
        }
        // Later, other event handling can be expanded
        bool ret = wifi_event((*event).type);
        if (false == ret)
        {
            // This event is not completed
            (*event).retryCount += 1;
            if ((*event).retryCount >= (*event).retryMaxNum)
            {
                // Multiple retries failed
                Serial.print("[EVENT]\tDelete -> " + String(app_event_type_info[(*event).type]));
                event = eventList.erase(event); // Delete the response event
                Serial.print(F("\tEventList Size: "));
                Serial.println(eventList.size());
            }
            else
            {
                // Retry next time
                (*event).nextRunTime = GET_SYS_MILLIS() + 4000;
                ++event;
            }
            continue;
        }

        // Event callback
        if (NULL != (*event).from && NULL != (*event).from->message_handle)
        {
            (*((*event).from->message_handle))(CTRL_NAME, (*event).from->app_name,
                                               (*event).type, (*event).info, NULL);
        }
        Serial.print("[EVENT]\tDelete -> " + String(app_event_type_info[(*event).type]));
        event = eventList.erase(event); // Delete the completed response event
        Serial.print(F("\tEventList Size: "));
        Serial.println(eventList.size());
    }
    return 0;
}

/**
 *  WiFi event handling
 *  Return true if the event is handled successfully, otherwise false
 * */
bool AppController::wifi_event(APP_MESSAGE_TYPE type)
{
    switch (type)
    {
    case APP_MESSAGE_WIFI_CONN:
    {
        // Update request
        // CONN_ERROR == g_network.end_conn_wifi() ||
        if (false == m_wifi_status)
        {
            g_network.start_conn_wifi(sys_cfg.ssid_0.c_str(), sys_cfg.password_0.c_str());
            m_wifi_status = true;
        }
        m_preWifiReqMillis = GET_SYS_MILLIS();
        if ((WiFi.getMode() & WIFI_MODE_STA) == WIFI_MODE_STA && CONN_SUCC != g_network.end_conn_wifi())
        {
            // In STA mode and not connected to WiFi yet
            return false;
        }
    }
    break;
    case APP_MESSAGE_WIFI_AP:
    {
        // Update request
        g_network.open_ap(AP_SSID);
        m_wifi_status = true;
        m_preWifiReqMillis = GET_SYS_MILLIS();
    }
    break;
    case APP_MESSAGE_WIFI_ALIVE:
    {
        // WiFi switch heartbeat, WiFi will not be turned off as long as the heartbeat is continuously received
        m_wifi_status = true;
        // Update request
        m_preWifiReqMillis = GET_SYS_MILLIS();
    }
    break;
    case APP_MESSAGE_WIFI_DISCONN:
    {
        g_network.close_wifi();
        m_wifi_status = false; // Flag
        // m_preWifiReqMillis = GET_SYS_MILLIS() - WIFI_LIFE_CYCLE;
    }
    break;
    case APP_MESSAGE_UPDATE_TIME:
    {
    }
    break;
    case APP_MESSAGE_MQTT_DATA:
    {
        Serial.println("APP_MESSAGE_MQTT_DATA");
        if (app_exit_flag == 1 && cur_app_index != getAppIdxByName("Heartbeat")) // In other apps
        {
            app_exit_flag = 0;
            (*(appList[cur_app_index]->exit_callback))(NULL); // Exit the current app
        }
        if (app_exit_flag == 0)
        {
            app_exit_flag = 1; // Enter the app, if already in
            cur_app_index = getAppIdxByName("Heartbeat");
            (*(getAppByName("Heartbeat")->app_init))(this); // Execute APP initialization
        }
    }
    break;
    default:
        break;
    }

    return true;
}

void AppController::app_exit()
{
    app_exit_flag = 0; // Exit the APP

    // Clear all requests of this object
    for (std::list<EVENT_OBJ>::iterator event = eventList.begin(); event != eventList.end();)
    {
        if (appList[cur_app_index] == (*event).from)
        {
            event = eventList.erase(event); // Delete the response event
        }
        else
        {
            ++event;
        }
    }

    if (NULL != appList[cur_app_index]->exit_callback)
    {
        // Execute APP exit callback
        (*(appList[cur_app_index]->exit_callback))(NULL);
    }
    app_control_display_scr(appList[cur_app_index]->app_image,
                            appList[cur_app_index]->app_name,
                            LV_SCR_LOAD_ANIM_NONE, true);

    // Restore RGB light HSV color mode
    RgbConfig *cfg = &rgb_cfg;
    RgbParam rgb_setting = {LED_MODE_HSV,
                            cfg->min_value_0, cfg->min_value_1, cfg->min_value_2,
                            cfg->max_value_0, cfg->max_value_1, cfg->max_value_2,
                            cfg->step_0, cfg->step_1, cfg->step_2,
                            cfg->min_brightness, cfg->max_brightness,
                            cfg->brightness_step, cfg->time};
    set_rgb_and_run(&rgb_setting);

    // Set CPU frequency
    if (1 == this->sys_cfg.power_mode)
    {
        setCpuFrequencyMhz(240);
    }
    else
    {
        setCpuFrequencyMhz(80);
    }
    Serial.print(F("CpuFrequencyMhz: "));
    Serial.println(getCpuFrequencyMhz());
}
