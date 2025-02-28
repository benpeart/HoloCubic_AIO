#include "weather.h"
#include "weather_gui.h"
#include "ESP32Time.h"
#include "sys/app_controller.h"
#include "network.h"
#include "common.h"
#include "ArduinoJson.h"
#include <esp32-hal-timer.h>
#include <map>

#define WEATHER_APP_NAME "Weather"
#define WEATHER_NOW_API "https://www.yiketianqi.com/free/day?appid=%s&appsecret=%s&unescape=1&city=%s"
// v1.yiketianqi.com/api?unescape=1&version=v61
// Update using Amap API documentation https://developer.amap.com/api/webservice/guide/api/weatherinfo
// Create service https://lbs.amap.com/api/webservice/create-project-and-key
// Weather code table https://lbs.amap.com/api/webservice/guide/tools/weather-code/

#define WEATHER_LIVES_API "http://restapi.amap.com/v3/weather/weatherInfo?key=%s&city=%s&extensions=base"
#define WEATHER_DALIY_FORECAST_API "http://restapi.amap.com/v3/weather/weatherInfo?key=%s&city=%s&extensions=all"
#define TIME_API "https://acs.m.taobao.com/gw/mtop.common.getTimestamp/"
#define WEATHER_PAGE_SIZE 2
#define UPDATE_WEATHER 0x01       // Update weather
#define UPDATE_DALIY_WEATHER 0x02 // Update daily weather
#define UPDATE_TIME 0x04          // Update time

// // NTP server information
// const char* ntpServer = "ntp.aliyun.com"; // Alibaba Cloud NTP server
// const long  gmtOffset_sec = 8 * 3600;     // China time zone (UTC+8)
// const int   daylightOffset_sec = 0;       // No daylight saving time offset
// // Use UDP connection
// WiFiUDP ntpUDP;
// // Create NTP client
// NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, 60000); // Sync every 60 seconds
// #define USE_NTP // Enable NTP time retrieval
// bool isUdpInit = false;

// Weather persistent configuration
#define WEATHER_CONFIG_PATH "/weather_2111.cfg"
struct WT_Config
{
    String tianqi_url;                   // tianqiapi URL
    String tianqi_city_code;             // City name or code
    String tianqi_api_key;               // API key
    unsigned long weatherUpdataInterval; // Weather update interval (s)
    unsigned long timeUpdataInterval;    // Date clock update interval (s)
};

static void write_config(WT_Config *cfg)
{
    char tmp[16];
    // Save configuration data in file (persistent)
    String w_data;
    w_data = w_data + cfg->tianqi_url + "\n";
    w_data = w_data + cfg->tianqi_city_code + "\n";
    w_data = w_data + cfg->tianqi_api_key + "\n";
    memset(tmp, 0, 16);
    snprintf(tmp, 16, "%lu\n", cfg->weatherUpdataInterval);
    w_data += tmp;
    memset(tmp, 0, 16);
    snprintf(tmp, 16, "%lu\n", cfg->timeUpdataInterval);
    w_data += tmp;
    g_flashCfg.writeFile(WEATHER_CONFIG_PATH, w_data.c_str());
}

static void read_config(WT_Config *cfg)
{
    // If persistent configuration file is needed, call this function to save data in flash
    // Configuration file name should start with APP name and end with ".cfg" to avoid confusion with multiple APPs
    char info[128] = {0};
    uint16_t size = g_flashCfg.readFile(WEATHER_CONFIG_PATH, (uint8_t *)info);
    info[size] = 0;
    if (size == 0)
    {
        // Default values
        cfg->tianqi_url = "restapi.amap.com/v3/weather/weatherInfo";
        cfg->tianqi_city_code = "北京"; // "110000";
        cfg->tianqi_api_key = "";
        cfg->weatherUpdataInterval = 900000; // Weather update interval 900000 (900s)
        cfg->timeUpdataInterval = 900000;    // Date clock update interval 900000 (900s)
        write_config(cfg);
    }
    else
    {
        // Parse data
        char *param[5] = {0};
        analyseParam(info, 5, param);
        cfg->tianqi_url = param[0];
        cfg->tianqi_city_code = param[1];
        cfg->tianqi_api_key = param[2];
        cfg->weatherUpdataInterval = atol(param[3]);
        cfg->timeUpdataInterval = atol(param[4]);
    }
}

struct WeatherAppRunData
{
    unsigned long preWeatherMillis; // Previous weather update milliseconds
    unsigned long preTimeMillis;    // Time update counter
    long long preNetTimestamp;      // Previous network timestamp
    long long errorNetTimestamp;    // Network to display time error
    long long preLocalTimestamp;    // Previous local machine timestamp
    unsigned int coactusUpdateFlag; // Forced update flag
    int clock_page;
    unsigned int update_type; // Update type flag

    BaseType_t xReturned_task_update; // Update data asynchronous task
    TaskHandle_t xHandle_task_update; // Update data asynchronous task

    ESP32Time g_rtc; // For time decoding
    Weather wea;     // Save weather conditions
};

static WT_Config cfg_data;
static WeatherAppRunData *run_data = NULL;

enum WEA_EVENT_ID
{
    UPDATE_NOW,
    UPDATE_NTP,
    UPDATE_DAILY
};

/*
Amap weather interface provides weather
https://lbs.amap.com/api/webservice/guide/tools/weather-code
*/
// std::map<String, int> weatherMap = {{"qin", 0}, {"yin", 1}, {"yu", 2}, {"yun", 3}, {"bingbao", 4}, {"wu", 5}, {"shachen", 6}, {"lei", 7}, {"xue", 8}};
std::map<String, int> weatherMap = {
    {"Sunny", 0},
    {"Few Clouds", 0},
    {"Partly Cloudy", 3},
    {"Cloudy", 3},
    {"Overcast", 1},
    {"Windy", 3},
    {"Calm", 3},
    {"Light Breeze", 3},
    {"Gentle Breeze", 3},
    {"Moderate Breeze", 3},
    {"Fresh Breeze", 3},
    {"Strong Breeze", 1},
    {"High Wind", 1},
    {"Gale", 1},
    {"Strong Gale", 1},
    {"Storm", 1},
    {"Violent Storm", 1},
    {"Hurricane", 1},
    {"Tropical Storm", 1},
    {"Haze", 5},
    {"Moderate Haze", 5},
    {"Heavy Haze", 5},
    {"Severe Haze", 5},
    {"Showers", 2},
    {"Thunder Showers", 7},
    {"Thunder Showers with Hail", 4},
    {"Light Rain", 2},
    {"Moderate Rain", 2},
    {"Heavy Rain", 2},
    {"Storm Rain", 2},
    {"Heavy Storm Rain", 2},
    {"Severe Storm Rain", 2},
    {"Strong Showers", 2},
    {"Strong Thunder Showers", 7},
    {"Extreme Rain", 2},
    {"Drizzle", 2},
    {"Rain", 2},
    {"Light to Moderate Rain", 2},
    {"Moderate to Heavy Rain", 2},
    {"Heavy to Storm Rain", 2},
    {"Storm to Heavy Storm Rain", 2},
    {"Heavy Storm to Severe Storm Rain", 2},
    {"Rain and Snow", 8},
    {"Sleet", 8},
    {"Showers and Snow", 8},
    {"Freezing Rain", 4},
    {"Snow", 8},
    {"Snow Showers", 8},
    {"Light Snow", 8},
    {"Moderate Snow", 8},
    {"Heavy Snow", 8},
    {"Blizzard", 8},
    {"Light to Moderate Snow", 8},
    {"Moderate to Heavy Snow", 8},
    {"Heavy to Blizzard", 8},
    {"Dust", 6},
    {"Sand", 6},
    {"Sandstorm", 6},
    {"Strong Sandstorm", 6},
    {"Tornado", 6},
    {"Fog", 5},
    {"Dense Fog", 5},
    {"Strong Dense Fog", 5},
    {"Light Fog", 5},
    {"Heavy Fog", 5},
    {"Severe Dense Fog", 5},
    {"Hot", 0},
    {"Cold", 0},
    {"Unknown", 0}
};

static void task_update(void *parameter); // Asynchronous update task

static int windLevelAnalyse(String str)
{
    int ret = 0;
    for (char ch : str)
    {
        if (ch >= '0' && ch <= '9')
        {
            ret = ret * 10 + (ch - '0');
        }
    }
    return ret;
}

static void get_weather(void)
{
    if (WL_CONNECTED != WiFi.status())
        return;

    HTTPClient http;
    http.setTimeout(1000);
    char api[128] = {0};

    snprintf(api, 128, WEATHER_LIVES_API,
             cfg_data.tianqi_api_key.c_str(),
             cfg_data.tianqi_city_code.c_str());
    Serial.print("API = ");
    Serial.println(api);
    http.begin(api);

    int httpCode = http.GET();
    if (httpCode > 0)
    {
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
            String payload = http.getString();
            DynamicJsonDocument doc(768);
            deserializeJson(doc, payload);
            Serial.println(payload);
            if (doc.containsKey("lives"))
            {
                /*
                {
                "status": "1",
                "count": "1",
                "info": "OK",
                "infocode": "10000",
                "lives": [
                    {
                        "province": "Henan",
                        "city": "Jianxi District",
                        "adcode": "410305",
                        "weather": "Sunny",
                        "temperature": "19",
                        "winddirection": "Northeast",
                        "windpower": "≤3",
                        "humidity": "38",
                        "reporttime": "2024-03-21 18:30:05",
                        "temperature_float": "19.0",
                        "humidity_float": "38.0"
                    }
                ]
            }
                */
                JsonObject weather_live = doc["lives"][0];
                // Get city name in Chinese
                strcpy(run_data->wea.cityname, weather_live["city"].as<String>().c_str());
                // Temperature
                run_data->wea.temperature = weather_live["temperature"].as<int>();
                // Humidity
                run_data->wea.humidity = weather_live["humidity"].as<int>();
                // Weather condition
                run_data->wea.weather_code = weatherMap[weather_live["weather"].as<String>()];
                
                strcpy(run_data->wea.weather, weather_live["weather"].as<String>().c_str());
                // Wind speed
                strcpy(run_data->wea.windDir, weather_live["winddirection"].as<String>().c_str());
                strcpy(run_data->wea.windpower, weather_live["windpower"].as<String>().c_str());
                Serial.printf("wea.windpower  = %s", run_data->wea.windpower);

                // No air quality parameter, can only use wind speed as a rough replacement
                run_data->wea.airQulity = airQulityLevel(run_data->wea.windpower);

                // weather_info.city = weather_live["city"].as<String>();
                // weather_info.weather = weather_live["weather"].as<String>();
                // weather_info.winddirection = weather_live["winddirection"].as<String>();
                // weather_info.windpower = weather_live["windpower"].as<String>();
                // weather_info.temperature = weather_live["temperature"].as<String>();
                // weather_info.humidity = weather_live["humidity"].as<String>();
                // weather_info.animIndex = get_weather_anim(weather_info.weather, getDateTime().hour());
                // weather_info.lastUpdate = millis();

                Serial.println(" Get weather info OK\n");
            }
            else
            {
                // Return value error, record
                Serial.println("[APP] Get weather error,info");
                String err_info = doc["info"];
                Serial.print(err_info);
                Serial.println("");
            }
        }
    }
    else
    {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
}

static long long get_timestamp(void)
{
    // Use local machine clock
    run_data->preNetTimestamp = run_data->preNetTimestamp + (GET_SYS_MILLIS() - run_data->preLocalTimestamp);
    run_data->preLocalTimestamp = GET_SYS_MILLIS();
    return run_data->preNetTimestamp;
}

static long long get_timestamp(String url)
{
    if (WL_CONNECTED != WiFi.status())
        return 0;

    String time = "";
    HTTPClient http;
    http.setTimeout(1000);
    http.begin(url);

    int httpCode = http.GET();
    if (httpCode > 0)
    {
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http.getString();
            Serial.println(payload);
            int time_index = payload.indexOf("\"t\":\"") + 5;       // Find the index after "t":" and +5 to skip the length of "t":"
            int time_end_index = payload.indexOf("\"", time_index); // Find the position of the ending quote
            time = payload.substring(time_index, time_end_index);   // Extract the timestamp

            // Use network timestamp as the standard
            run_data->preNetTimestamp = atoll(time.c_str()) + run_data->errorNetTimestamp + TIMEZERO_OFFSIZE;
            run_data->preLocalTimestamp = GET_SYS_MILLIS();
        }
    }
    else
    {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        // When network timestamp cannot be obtained
        run_data->preNetTimestamp = run_data->preNetTimestamp + (GET_SYS_MILLIS() - run_data->preLocalTimestamp);
        run_data->preLocalTimestamp = GET_SYS_MILLIS();
    }
    http.end();

    return run_data->preNetTimestamp;
}

static void get_daliyWeather(short maxT[], short minT[])
{
    if (WL_CONNECTED != WiFi.status())
        return;

    HTTPClient http;
    http.setTimeout(1000);
    char api[128] = {0};
    snprintf(api, 128, WEATHER_DALIY_FORECAST_API,
             cfg_data.tianqi_api_key.c_str(),
             cfg_data.tianqi_city_code.c_str());
    Serial.print("API = ");
    Serial.println(api);
    http.begin(api);

    int httpCode = http.GET();
    if (httpCode > 0)
    {
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
            String payload = http.getString();
            Serial.println(payload);
            DynamicJsonDocument doc2(4096);
            deserializeJson(doc2, payload);
            // JsonObject sk = doc2.as<JsonObject>();
            // for (int gDW_i = 0; gDW_i < FORECAST_DAYS; ++gDW_i)
            // {
            //     maxT[gDW_i] = sk["data"][gDW_i]["tem_day"].as<int>();
            //     minT[gDW_i] = sk["data"][gDW_i]["tem_night"].as<int>();
            // }

            if (doc2.containsKey("forecasts"))
            {
                JsonObject weather_forecast = doc2["forecasts"][0];
                for (int i = 0; i < FORECAST_DAYS; i++)
                {
                    maxT[i] = weather_forecast["casts"][i]["daytemp"].as<int>();
                    minT[i] = weather_forecast["casts"][i]["nighttemp"].as<int>();
                }
                Serial.println("Get weather cast OK\n");
            }
        }
    }
    else
    {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
}

static void updateTime_RTC(long long timestamp)
{
    struct TimeStr t;
    run_data->g_rtc.setTime(timestamp / 1000);
    t.month = run_data->g_rtc.getMonth() + 1;
    t.day = run_data->g_rtc.getDay();
    t.hour = run_data->g_rtc.getHour(true);
    t.minute = run_data->g_rtc.getMinute();
    t.second = run_data->g_rtc.getSecond();
    t.weekday = run_data->g_rtc.getDayofWeek();
    // Serial.printf("time : %d-%d-%d\n",t.hour, t.minute, t.second);
    display_time(t, LV_SCR_LOAD_ANIM_NONE);
}

static int weather_init(AppController *sys)
{
    tft->setSwapBytes(true);
    weather_gui_init();
    // Get configuration information
    read_config(&cfg_data);

    // Initialize runtime parameters
    run_data = (WeatherAppRunData *)calloc(1, sizeof(WeatherAppRunData));
    memset((char *)&run_data->wea, 0, sizeof(Weather));
    run_data->preNetTimestamp = 1577808000000; // Previous network timestamp initialized to 2020-01-01 00:00:00
    run_data->errorNetTimestamp = 2;
    run_data->preLocalTimestamp = GET_SYS_MILLIS(); // Previous local machine timestamp
    run_data->clock_page = 0;
    run_data->preWeatherMillis = 0;
    run_data->preTimeMillis = 0;
    // Forced update
    run_data->coactusUpdateFlag = 0x01;
    run_data->update_type = 0x00; // Indicates nothing needs to be updated

    // Currently, the task stack size of 5000 is enough, 4000 is not enough
    // To iterate new features in the future, currently set to 8000, tasks may cause stuttering
    run_data->xReturned_task_update = pdFAIL;
    // run_data->xReturned_task_update = xTaskCreate(
    //     task_update,                     /*Task function*/
    //     "Task_update",                   /*Task name string*/
    //     8000,                            /*Stack size in bytes*/
    //     NULL,                            /*Parameter passed as task input*/
    //     1,                               /*Task priority*/
    //     &run_data->xHandle_task_update); /*Task handle*/

    return 0;
}

static void weather_process(AppController *sys,
                            const ImuAction *act_info)
{
    lv_scr_load_anim_t anim_type = LV_SCR_LOAD_ANIM_NONE;

    if (RETURN == act_info->active)
    {
        sys->app_exit();
        return;
    }
    else if (GO_FORWORD == act_info->active)
    {
        // Indirect forced update
        run_data->coactusUpdateFlag = 0x01;
        delay(500); // To prevent many requests after indirect forced update, causing display stuttering
    }
    else if (TURN_RIGHT == act_info->active)
    {
        anim_type = LV_SCR_LOAD_ANIM_MOVE_RIGHT;
        run_data->clock_page = (run_data->clock_page + 1) % WEATHER_PAGE_SIZE;
    }
    else if (TURN_LEFT == act_info->active)
    {
        anim_type = LV_SCR_LOAD_ANIM_MOVE_LEFT;
        // Equivalent to clock_page = (clock_page + WEATHER_PAGE_SIZE - 1) % WEATHER_PAGE_SIZE;
        // +3 to avoid data overflow to negative numbers, causing modulo logic errors
        run_data->clock_page = (run_data->clock_page + WEATHER_PAGE_SIZE - 1) % WEATHER_PAGE_SIZE;
    }

    // Interface refresh
    if (run_data->clock_page == 0)
    {
        display_weather(run_data->wea, anim_type);
        if (0x01 == run_data->coactusUpdateFlag || doDelayMillisTime(cfg_data.weatherUpdataInterval, &run_data->preWeatherMillis, false))
        {
            sys->send_to(WEATHER_APP_NAME, CTRL_NAME,
                         APP_MESSAGE_WIFI_CONN, (void *)UPDATE_NOW, NULL);
            sys->send_to(WEATHER_APP_NAME, CTRL_NAME,
                         APP_MESSAGE_WIFI_CONN, (void *)UPDATE_DAILY, NULL);
        }

        if (0x01 == run_data->coactusUpdateFlag || doDelayMillisTime(cfg_data.timeUpdataInterval, &run_data->preTimeMillis, false))
        {
            // Try to sync clock on the network
            sys->send_to(WEATHER_APP_NAME, CTRL_NAME,
                         APP_MESSAGE_WIFI_CONN, (void *)UPDATE_NTP, NULL);
        }
        else if (GET_SYS_MILLIS() - run_data->preLocalTimestamp > 400)
        {
            updateTime_RTC(get_timestamp());
        }
        run_data->coactusUpdateFlag = 0x00; // Cancel forced update flag
        display_space();
        delay(30);
    }
    else if (run_data->clock_page == 1)
    {
        // Only get future weather once when switching interface
        display_curve(run_data->wea.daily_max, run_data->wea.daily_min, anim_type);
        delay(300);
    }
}

static void weather_background_task(AppController *sys,
                                    const ImuAction *act_info)
{
    // This function is a background task, the main controller will call this function every minute
    // This function should try to call "resident data" only, other variables may have been released due to lifecycle reasons
}

static int weather_exit_callback(void *param)
{
    weather_gui_del();

    // Kill asynchronous task
    if (run_data->xReturned_task_update == pdPASS)
    {
        vTaskDelete(run_data->xHandle_task_update);
    }
    run_data->xReturned_task_update = pdFAIL;

    // Release runtime data
    if (NULL != run_data)
    {
        free(run_data);
        run_data = NULL;
    }
    return 0;
}

static void task_update(void *parameter)
{
    // Data update task
    while (true)
    {
        if (run_data->update_type & UPDATE_WEATHER)
        {
            get_weather();
            run_data->update_type &= (~UPDATE_WEATHER);
        }
        if (run_data->update_type & UPDATE_TIME)
        {
            get_timestamp(TIME_API); // nowapi time API
            run_data->update_type &= (~UPDATE_TIME);
        }
        if (run_data->update_type & UPDATE_DALIY_WEATHER)
        {
            get_daliyWeather(run_data->wea.daily_max, run_data->wea.daily_min);
            run_data->update_type &= (~UPDATE_DALIY_WEATHER);
        }
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}

static void weather_message_handle(const char *from, const char *to,
                                   APP_MESSAGE_TYPE type, void *message,
                                   void *ext_info)
{
    switch (type)
    {
    case APP_MESSAGE_WIFI_CONN:
    {
        Serial.println(F("----->weather_event_notification"));
        int event_id = (int)message;
        switch (event_id)
        {
        case UPDATE_NOW:
        {
            Serial.print(F("weather update.\n"));
            run_data->update_type |= UPDATE_WEATHER;

            // Update process, use the following code or replace with asynchronous task
            get_weather();
        };
        break;
        case UPDATE_NTP:
        {
            Serial.print(F("ntp update.\n"));
            run_data->update_type |= UPDATE_TIME;

            // Update process, use the following code or replace with asynchronous task
            long long timestamp = get_timestamp(TIME_API); // nowapi time API
        };
        break;
        case UPDATE_DAILY:
        {
            Serial.print(F("daliy update.\n"));
            run_data->update_type |= UPDATE_DALIY_WEATHER;

            // Update process, use the following code or replace with asynchronous task
            get_daliyWeather(run_data->wea.daily_max, run_data->wea.daily_min);
        };
        break;
        default:
            break;
        }
    }
    break;
    case APP_MESSAGE_GET_PARAM:
    {
        char *param_key = (char *)message;
        if (!strcmp(param_key, "tianqi_url"))
        {
            snprintf((char *)ext_info, 128, "%s", cfg_data.tianqi_url.c_str());
        }
        else if (!strcmp(param_key, "tianqi_city_code"))
        {
            snprintf((char *)ext_info, 32, "%s", cfg_data.tianqi_city_code.c_str());
        }
        else if (!strcmp(param_key, "tianqi_api_key"))
        {
            snprintf((char *)ext_info, 40, "%s", cfg_data.tianqi_api_key.c_str());
        }
        else if (!strcmp(param_key, "weatherUpdataInterval"))
        {
            snprintf((char *)ext_info, 32, "%lu", cfg_data.weatherUpdataInterval);
        }
        else if (!strcmp(param_key, "timeUpdataInterval"))
        {
            snprintf((char *)ext_info, 32, "%lu", cfg_data.timeUpdataInterval);
        }
        else
        {
            snprintf((char *)ext_info, 32, "%s", "NULL");
        }
    }
    break;
    case APP_MESSAGE_SET_PARAM:
    {
        char *param_key = (char *)message;
        char *param_val = (char *)ext_info;
        if (!strcmp(param_key, "tianqi_url"))
        {
            cfg_data.tianqi_url = param_val;
        }
        else if (!strcmp(param_key, "tianqi_city_code"))
        {
            cfg_data.tianqi_city_code = param_val;
        }
        else if (!strcmp(param_key, "tianqi_api_key"))
        {
            cfg_data.tianqi_api_key = param_val;
        }
        else if (!strcmp(param_key, "weatherUpdataInterval"))
        {
            cfg_data.weatherUpdataInterval = atol(param_val);
        }
        else if (!strcmp(param_key, "timeUpdataInterval"))
        {
            cfg_data.timeUpdataInterval = atol(param_val);
        }
    }
    break;
    case APP_MESSAGE_READ_CFG:
    {
        read_config(&cfg_data);
    }
    break;
    case APP_MESSAGE_WRITE_CFG:
    {
        write_config(&cfg_data);
    }
    break;
    default:
        break;
    }
}

APP_OBJ weather_app = {WEATHER_APP_NAME, &app_weather, "",
                       weather_init, weather_process, weather_background_task,
                       weather_exit_callback, weather_message_handle};
