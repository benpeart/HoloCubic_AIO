/***************************************************
HoloCubic Multifunctional Firmware Source Code
(If you reference this project's source code in your work, please cite the source.)

Integrated with various apps including weather, clock, photo album, special
effects animation, video playback, video projection, and browser file
modification. (Refer to the manual for specific usage of each app.)

  Github repositories：https://github.com/ClimbSnail/HoloCubic_AIO

  Last review/edit by ClimbSnail: 2023/01/14
 ****************************************************/

#include "driver/lv_port_indev.h"
#include "driver/lv_port_fs.h"

#include "common.h"
#include "sys/app_controller.h"

#include "app/app_conf.h"

#include <SPIFFS.h>
#include <esp32-hal.h>
#include <esp32-hal-timer.h>

bool isCheckAction = false;

/*** Component objects ***/
ImuAction *act_info;           // Store data returned by mpu6050
AppController *app_controller; // APP controller

TaskHandle_t handleTaskLvgl;

// Update display in parallel thread.
void TaskLvglUpdate(void *parameter)
{
    // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    for (;;)
    {
        AIO_LVGL_OPERATE_LOCK(lv_timer_handler();)
        vTaskDelay(5);
    }
}

TimerHandle_t xTimerAction = NULL;
void actionCheckHandle(TimerHandle_t xTimer)
{
    // Flag requires detection action
    isCheckAction = true;
}

void my_print(const char *buf)
{
    Serial.printf("%s", buf);
    Serial.flush();
}

void setup()
{
    Serial.begin(115200);

    Serial.println(F("\nAIO (All in one) version " AIO_VERSION "\n"));
    Serial.flush();
    // MAC ID can be used as a unique chip identifier
    Serial.print(F("ChipID(EfuseMac): "));
    Serial.println(ESP.getEfuseMac());
    // flash run mode
    // Serial.print(F("FlashChipMode: "));
    // Serial.println(ESP.getFlashChipMode());
    // Serial.println(F("FlashChipMode value: FM_QIO = 0, FM_QOUT = 1, FM_DIO = 2, FM_DOUT = 3, FM_FAST_READ = 4, FM_SLOW_READ = 5, FM_UNKNOWN = 255"));

    app_controller = new AppController(); // APP controller

    // Needs to be initialized in Setup
    if (!SPIFFS.begin(true))
    {
        Serial.println("SPIFFS Mount Failed");
        return;
    }

#ifdef PEAK
    pinMode(CONFIG_BAT_CHG_DET_PIN, INPUT);
    pinMode(CONFIG_ENCODER_PUSH_PIN, INPUT_PULLUP);
    /* Power enable hold */
    Serial.println("Power: Waiting...");
    pinMode(CONFIG_POWER_EN_PIN, OUTPUT);
    digitalWrite(CONFIG_POWER_EN_PIN, LOW);
    digitalWrite(CONFIG_POWER_EN_PIN, HIGH);
    Serial.println("Power: ON");
    log_e("Power: ON");
#endif

    // config_read(NULL, &g_cfg);   // Old configuration file reading method
    app_controller->read_config(&app_controller->sys_cfg);
    app_controller->read_config(&app_controller->mpu_cfg);
    app_controller->read_config(&app_controller->rgb_cfg);

    /*** Init screen ***/
    screen.init(app_controller->sys_cfg.rotation,
                app_controller->sys_cfg.backLight);

    /*** Init on-board RGB ***/
    rgb.init();
    rgb.setBrightness(0.05).setRGB(0, 64, 64);

    /*** Init ambient-light sensor ***/
    ambLight.init(ONE_TIME_H_RESOLUTION_MODE);

    /*** Init micro SD-Card ***/
    tf.init();

    lv_fs_fatfs_init();

    // Update display in parallel thread.
    // BaseType_t taskLvglReturned = xTaskCreate(
    //     TaskLvglUpdate,
    //     "LvglThread",
    //     8 * 1024,
    //     nullptr,
    //     TASK_LVGL_PRIORITY,
    //     &handleTaskLvgl);
    // if (taskLvglReturned != pdPASS)
    // {
    //     Serial.println("taskLvglReturned != pdPASS");
    // }
    // else
    // {
    //     Serial.println("taskLvglReturned == pdPASS");
    // }

#if LV_USE_LOG
    lv_log_register_print_cb(my_print);
#endif /*LV_USE_LOG*/

    app_controller->init();

    // "Install" the APP into the controller
#if APP_WEATHER_USE
    app_controller->app_install(&weather_app);
#endif
#if APP_WEATHER_OLD_USE
    app_controller->app_install(&weather_old_app);
#endif
#if APP_TOMATO_USE
    app_controller->app_install(&tomato_app);
#endif
#if APP_PICTURE_USE
    app_controller->app_install(&picture_app);
#endif
#if APP_MEDIA_PLAYER_USE
    app_controller->app_install(&media_app);
#endif
#if APP_SCREEN_SHARE_USE
    app_controller->app_install(&screen_share_app);
#endif
#if APP_FILE_MANAGER_USE
    app_controller->app_install(&file_manager_app);
#endif

    app_controller->app_install(&server_app);

#if APP_IDEA_ANIM_USE
    app_controller->app_install(&idea_app);
#endif
#if APP_BILIBILI_FANS_USE
    app_controller->app_install(&bilibili_app);
#endif
#if APP_SETTING_USE
    app_controller->app_install(&settings_app);
#endif
#if APP_GAME_2048_USE
    app_controller->app_install(&game_2048_app);
#endif
#if APP_GAME_SNAKE_USE
    app_controller->app_install(&game_snake_app);
#endif
#if APP_ANNIVERSARY_USE
    app_controller->app_install(&anniversary_app);
#endif
#if APP_HEARTBEAT_USE
    app_controller->app_install(&heartbeat_app, APP_TYPE_BACKGROUND);
#endif
#if APP_STOCK_MARKET_USE
    app_controller->app_install(&stockmarket_app);
#endif
#if APP_PC_RESOURCE_USE
    app_controller->app_install(&pc_resource_app);
#endif
#if APP_LHLXW_USE
    app_controller->app_install(&LHLXW_app);
#endif
    // Auto-start APP
    app_controller->app_auto_start();

    // Prioritize screen display to speed up visual boot time
    app_controller->main_process(&mpu.action_info);

    /*** Init IMU as input device ***/
    // lv_port_indev_init();

    mpu.init(app_controller->sys_cfg.mpu_order,
             app_controller->sys_cfg.auto_calibration_mpu,
             &app_controller->mpu_cfg); // Initialization is time-consuming

    /*** Mark the completion of MPU6050 initialization ***/
    RgbConfig *rgb_cfg = &app_controller->rgb_cfg;
    // Initialize RGB light in HSV color mode
    RgbParam rgb_setting = {LED_MODE_HSV,
                            rgb_cfg->min_value_0, rgb_cfg->min_value_1, rgb_cfg->min_value_2,
                            rgb_cfg->max_value_0, rgb_cfg->max_value_1, rgb_cfg->max_value_2,
                            rgb_cfg->step_0, rgb_cfg->step_1, rgb_cfg->step_2,
                            rgb_cfg->min_brightness, rgb_cfg->max_brightness,
                            rgb_cfg->brightness_step, rgb_cfg->time};
    // Run RGB task
    set_rgb_and_run(&rgb_setting, RUN_MODE_TASK);

    // Initialize action data to avoid null pointer
    act_info = mpu.getAction();
    // Define an action detection timer for mpu6050
    xTimerAction = xTimerCreate("Action Check",
                                200 / portTICK_PERIOD_MS,
                                pdTRUE, (void *)0, actionCheckHandle);
    xTimerStart(xTimerAction, 0);
}

void loop()
{
    screen.routine();

#ifdef PEAK
    // Adapt to Zhihui Jun's PEAK
    if (!mpu.Encoder_GetIsPush())
    {
        Serial.println("mpu.Encoder_GetIsPush()1");
        delay(1000);
        if (!mpu.Encoder_GetIsPush())
        {
            Serial.println("mpu.Encoder_GetIsPush()2");
            // Adapt to Peak's shutdown function
            digitalWrite(CONFIG_POWER_EN_PIN, LOW);
        }
    }
#endif
    if (isCheckAction)
    {
        isCheckAction = false;
        act_info = mpu.getAction();
    }
    app_controller->main_process(act_info); // Run the current process
    // Serial.println(ambLight.getLux() / 50.0);
    // rgb.setBrightness(ambLight.getLux() / 500.0);
}
