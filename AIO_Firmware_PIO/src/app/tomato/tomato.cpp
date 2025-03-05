#include "tomato.h"
#include "tomato_gui.h"
#include "sys/app_controller.h"
#include "common.h"
#include "ESP32Time.h"
#define TOMATO_APP_NAME "Tomato"
#define ON 1
#define OFF 0

// Dynamic data, needs to be released when the APP lifecycle ends
struct TomatoAppRunData
{
    unsigned long time_start; // Record the milliseconds when the system starts timing
    unsigned long time_ms;    // Milliseconds, corresponding to the countdown display time
    TimeStr t;                // Time structure
    TimeStr t_start;          // Countdown structure
    RgbConfig rgb_cfg;        // Light effect
    bool rgb_fast;            // Enable
    bool rgb_fast_update;     // Flag
    RgbParam rgb_setting;     // RGB parameters
    int time_mode;            // Countdown type
    uint8_t switch_count;     // Switch count, used for debounce
    ACTIVE_TYPE lastAct;
};

// Resident data, can be retained or deleted regardless of the APP lifecycle
struct TomatoAppForeverData
{
};

static bool hadOpened = false;

// Save the parameter information during APP runtime, it is recommended to release it in xxx_exit_callback when closing the APP
static TomatoAppRunData *run_data = NULL;

// You can also add a small amount of constant memory variables (no need to release when exiting, can be read when starting the second time)
// Considering that all APPs share memory, try to minimize the data occupation of forever_data
static TomatoAppForeverData forever_data;

static int tomato_init(AppController *sys)
{
    // Initialize runtime parameters
    tomato_gui_init();
    // Initialize runtime parameters
    run_data = (TomatoAppRunData *)calloc(1, sizeof(TomatoAppRunData));
    run_data->time_start = millis();
    run_data->t_start.second = 0; // Focus time, initialize once
    run_data->t_start.minute = 25;
    run_data->t = run_data->t_start;
    run_data->rgb_fast = 0;
    run_data->rgb_fast_update = 0;
    run_data->switch_count = 0;
    run_data->lastAct = UNKNOWN;
    // run_data->count_down_init = 0;

    run_data->rgb_cfg.mode = 1;
    run_data->rgb_cfg.min_value_0 = 1;
    run_data->rgb_cfg.min_value_1 = 32;
    run_data->rgb_cfg.min_value_2 = 255;
    run_data->rgb_cfg.max_value_0 = 255;
    run_data->rgb_cfg.max_value_1 = 255;
    run_data->rgb_cfg.max_value_2 = 255;
    run_data->rgb_cfg.step_0 = 1;
    run_data->rgb_cfg.step_1 = 1;
    run_data->rgb_cfg.step_2 = 1;
    run_data->rgb_cfg.min_brightness = 0.15;
    run_data->rgb_cfg.max_brightness = 0.25;
    run_data->rgb_cfg.brightness_step = 0.003;
    run_data->rgb_cfg.time = 30;

    run_data->rgb_setting = {LED_MODE_HSV,
                             run_data->rgb_cfg.min_value_0, run_data->rgb_cfg.min_value_1, run_data->rgb_cfg.min_value_2,
                             run_data->rgb_cfg.max_value_0, run_data->rgb_cfg.max_value_1, run_data->rgb_cfg.max_value_2,
                             run_data->rgb_cfg.step_0, run_data->rgb_cfg.step_1, run_data->rgb_cfg.step_2,
                             run_data->rgb_cfg.min_brightness, run_data->rgb_cfg.max_brightness,
                             run_data->rgb_cfg.brightness_step, run_data->rgb_cfg.time};
    return 0;
}
static void time_switch()
{
    switch (run_data->time_mode)
    {
    case -1:
        run_data->time_start = millis();
        run_data->t_start.second = 0;
        run_data->t_start.minute = 5;
        run_data->t = run_data->t_start;
        run_data->rgb_fast = 0;
        run_data->rgb_fast_update = 0;
        break;
    case 0:
        run_data->time_start = millis();
        run_data->t_start.second = 0;
        run_data->t_start.minute = 25;
        run_data->t = run_data->t_start;
        run_data->rgb_fast = 0;
        run_data->rgb_fast_update = 0;
        break;
    case 1:
        run_data->time_start = millis();
        run_data->t_start.second = 0;
        run_data->t_start.minute = 45;
        run_data->t = run_data->t_start;
        run_data->rgb_fast = 0;
        run_data->rgb_fast_update = 0;
        break;
    case 2:
        run_data->time_start = millis();
        run_data->t_start.second = 0;
        run_data->t_start.minute = 15;
        run_data->t = run_data->t_start;
        run_data->rgb_fast = 0;
        run_data->rgb_fast_update = 0;
        break;

    default:
        break;
    }
}
/*********************************************************************************
 *Function:     RGB control
 *Description:  Used for reminders
 *Calls:
 *Called By:
 *Input:
 *Output:
 *Return:
 *Others:       Speed and minimum brightness adjusted
 **********************************************************************************/
static void rgb_ctrl()
{
    // Serial.print(run_data->rgb_fast);
    // Serial.println("     rgb_fast");
    // Serial.print(run_data->rgb_fast_update);
    // Serial.println("     rgb_fast_update");
    if (run_data->rgb_fast_update == 0)
    {
        if (run_data->rgb_fast == 1)
        {
            run_data->rgb_cfg.time = 10;
            // run_data->rgb_cfg.min_brightness = 0.01;
            // run_data->rgb_cfg.brightness_step = 0.05;
            // run_data->rgb_cfg.max_brightness = 0.95;
            // run_data->rgb_cfg.step_0 = 0;
            // run_data->rgb_cfg.step_1 = 0;
            // run_data->rgb_cfg.step_2 = 0;
            run_data->rgb_cfg.mode = 1;
            run_data->rgb_cfg.min_value_0 = 1;
            run_data->rgb_cfg.min_value_1 = 32;
            run_data->rgb_cfg.min_value_2 = 255;
            run_data->rgb_cfg.max_value_0 = 255;
            run_data->rgb_cfg.max_value_1 = 255;
            run_data->rgb_cfg.max_value_2 = 255;
            //  Serial.println("set low");
            run_data->rgb_cfg.step_0 = 1;
            run_data->rgb_cfg.step_1 = 1;
            run_data->rgb_cfg.step_2 = 1;
            run_data->rgb_cfg.min_brightness = 0.01;
            run_data->rgb_cfg.max_brightness = 1;
            run_data->rgb_cfg.brightness_step = 0.072;
            //  Serial.println("set fast");
        }
        else
        {
            run_data->rgb_cfg.mode = 1;
            run_data->rgb_cfg.min_value_0 = 1;
            run_data->rgb_cfg.min_value_1 = 32;
            run_data->rgb_cfg.min_value_2 = 255;
            run_data->rgb_cfg.max_value_0 = 255;
            run_data->rgb_cfg.max_value_1 = 255;
            run_data->rgb_cfg.max_value_2 = 255;
            //  Serial.println("set low");
            run_data->rgb_cfg.step_0 = 1;
            run_data->rgb_cfg.step_1 = 1;
            run_data->rgb_cfg.step_2 = 1;
            run_data->rgb_cfg.min_brightness = 0.15;
            run_data->rgb_cfg.max_brightness = 0.25;
            run_data->rgb_cfg.brightness_step = 0.001;
            run_data->rgb_cfg.time = 50;
        }
        run_data->rgb_setting = {LED_MODE_HSV,
                                 run_data->rgb_cfg.min_value_0, run_data->rgb_cfg.min_value_1, run_data->rgb_cfg.min_value_2,
                                 run_data->rgb_cfg.max_value_0, run_data->rgb_cfg.max_value_1, run_data->rgb_cfg.max_value_2,
                                 run_data->rgb_cfg.step_0, run_data->rgb_cfg.step_1, run_data->rgb_cfg.step_2,
                                 run_data->rgb_cfg.min_brightness, run_data->rgb_cfg.max_brightness,
                                 run_data->rgb_cfg.brightness_step, run_data->rgb_cfg.time};
        set_rgb_and_run(&(run_data->rgb_setting));
        run_data->rgb_fast_update = 1;
    }
}
static void rgb_reset()
{

    run_data->rgb_cfg.mode = 1;
    run_data->rgb_cfg.min_value_0 = 1;
    run_data->rgb_cfg.min_value_1 = 32;
    run_data->rgb_cfg.min_value_2 = 255;
    run_data->rgb_cfg.max_value_0 = 255;
    run_data->rgb_cfg.max_value_1 = 255;
    run_data->rgb_cfg.max_value_2 = 255;
    //  Serial.println("set low");
    run_data->rgb_cfg.step_0 = 1;
    run_data->rgb_cfg.step_1 = 1;
    run_data->rgb_cfg.step_2 = 1;
    run_data->rgb_cfg.min_brightness = 0.15;
    run_data->rgb_cfg.max_brightness = 0.25;
    run_data->rgb_cfg.brightness_step = 0.001;
    run_data->rgb_cfg.time = 50;
    run_data->rgb_setting = {LED_MODE_HSV,
                             run_data->rgb_cfg.min_value_0, run_data->rgb_cfg.min_value_1, run_data->rgb_cfg.min_value_2,
                             run_data->rgb_cfg.max_value_0, run_data->rgb_cfg.max_value_1, run_data->rgb_cfg.max_value_2,
                             run_data->rgb_cfg.step_0, run_data->rgb_cfg.step_1, run_data->rgb_cfg.step_2,
                             run_data->rgb_cfg.min_brightness, run_data->rgb_cfg.max_brightness,
                             run_data->rgb_cfg.brightness_step, run_data->rgb_cfg.time};
    set_rgb_and_run(&(run_data->rgb_setting));
}
static void tomato_process(AppController *sys, const ImuAction *act_info)
{
    static int count = 0;
    static int count_down_reset = ON;
    if (!hadOpened)
    {
        delay(750);
        run_data->time_start = millis();
        hadOpened = true;
    }
    if (RETURN == act_info->active)
    {
        count = 0;
        count_down_reset = ON;
        hadOpened = false;
        sys->app_exit(); // Exit APP
        return;
    }

    if (GO_FORWORD == act_info->active)
    {
        unsigned long currentTime = millis();
        unsigned long elapsedTime = currentTime - run_data->time_start;

        if (count <= 42)
        {
            if (elapsedTime >= 700)
            {
                run_data->time_start = currentTime;
                if (count_down_reset == ON)
                {
                    run_data->time_start = millis();
                    count_down_reset = (count > 1) ? OFF : ON;
                    count = (count > 1) ? count : 0;
                }
                if (run_data->t.second != 0)
                {
                    count_down_reset = ON;
                }
                else if (run_data->t_start.minute < 99)
                {
                    run_data->t_start.minute += 1;
                }
            }
        }
        else
        {
            if (elapsedTime >= 300)
            {
                run_data->time_start = currentTime;
                if (count_down_reset == ON)
                {
                    run_data->time_start = millis();
                    count_down_reset = (count > 1) ? OFF : ON;
                    count = (count > 1) ? count : 0;
                }
                if (run_data->t.second != 0)
                {
                    count_down_reset = ON;
                }
                else if (run_data->t_start.minute < 99)
                {
                    run_data->t_start.minute += 1;
                }
            }
        }
        if (count <= 42)
        {
            count++;
        }
        return;
    }

    if (TURN_LEFT == act_info->active || TURN_RIGHT == act_info->active)
    {
        count = 0;
        count_down_reset = ON;
        static int last_mode;
        run_data->switch_count <<= 2;
        run_data->switch_count |= 3;      // Write 11 and shift
        if (run_data->switch_count > 0xf) // Only switch if triggered continuously
        {
            if (run_data->time_mode >= -1 && run_data->time_mode <= 2)

                if (run_data->lastAct != act_info->active)
                {
                    if (TURN_LEFT == act_info->active)
                    {
                        run_data->switch_count = 0X00;
                        run_data->time_mode -= 1;
                        if (run_data->time_mode >= -1 && run_data->time_mode <= 2)
                        {
                            run_data->t_start.minute = 5;
                            delay(50);
                            run_data->time_start = millis();
                        }
                    }
                    else if (TURN_RIGHT == act_info->active)
                    {
                        run_data->switch_count = 0X00;
                        run_data->time_mode += 1;
                        if (run_data->time_mode >= -1 && run_data->time_mode <= 2)
                        {
                            run_data->t_start.minute = 45;
                            delay(50);
                            run_data->time_start = millis();
                        }
                    }
                    if (run_data->time_mode > 2) // Limit
                        run_data->time_mode = 2;
                    if (run_data->time_mode < -1)
                        run_data->time_mode = -1;
                    if (last_mode != run_data->time_mode)
                    {
                        time_switch(); // Run when mode switch occurs
                    }
                    last_mode = run_data->time_mode;
                }
        }
        run_data->lastAct = act_info->active;
    }
    else // Debounce, not triggered, write 00 and shift
    {
        run_data->switch_count <<= 2;
        run_data->switch_count &= ~3;
    }

    if (millis() - run_data->time_start > 800)
    {
        run_data->lastAct = UNKNOWN;
    }

    if (run_data->t.minute == 0 && run_data->t.second == 0 && run_data->rgb_fast == 0) // Time's up, RGB flashing reminder
    {
        run_data->rgb_fast = 1;
        run_data->rgb_fast_update = 0;
    }
    rgb_ctrl();
    if (run_data->rgb_fast == 0) // Continue calculating time if not time's up
    {
        unsigned long ms_count = 999 + (run_data->t_start.second + run_data->t_start.minute * 60) * 1000; // Countdown duration in ms, add 999ms to display x minutes 00 seconds, otherwise it will flash directly
        run_data->time_ms = ms_count - (millis() - run_data->time_start);                                 // Countdown duration minus elapsed time is the time to display
        run_data->t.second = run_data->time_ms % 60000 / 1000;
        run_data->t.minute = run_data->time_ms / 60 / 1000;
    }
    // Serial.print(run_data->rgb_fast);
    display_tomato(run_data->t, run_data->time_mode);
    delay(100);
}

static int tomato_exit_callback(void *param)
{
    tomato_gui_del();
    rgb_reset();
    if (run_data != NULL)
    {
        // Release resources
        free(run_data);
        run_data = NULL;
        Serial.println("EXIT\n");
    }
    return 0;
}
static void tomato_message_handle(const char *from, const char *to, APP_MESSAGE_TYPE type, void *message, void *ext_info)
{
    switch (type)
    {
    case APP_MESSAGE_WIFI_CONN:
    {
        // get_timestamp(TIME_API);
    }
    }
}
static void tomato_background_task(AppController *sys,
                                   const ImuAction *act_info)
{
    // This function is a background task, the main controller will call this function every minute
    // This function should only call "resident data", other variables may have been released due to the lifecycle

    // Send request. If it is a wifi-related message, the tomato_message_handle function will be automatically called after the request is completed
    // sys->send_to(tomato_APP_NAME, CTRL_NAME,
    //              APP_MESSAGE_WIFI_CONN, (void *)run_data->val1, NULL);

    // You can also remove your own background task, it is most appropriate to place it in a controllable place in this APP
    // sys->remove_backgroud_task();

    // Add delay if needed
    // delay(300);
}

APP_OBJ tomato_app = {TOMATO_APP_NAME, &app_tomato_icon, "Author Fjl\nVersion 1.0.0\n",
                      tomato_init, tomato_process, tomato_background_task,
                      tomato_exit_callback, tomato_message_handle};
