#include "eye_functions.h"
#include "sys/app_controller.h"
#include "eye.h"

/*
Function: Eye animation
Instructions: Left/Right to switch eye styles
Others:
Referenced from https://learn.adafruit.com/animated-electronic-eyes/software
and AIO_FIRMWARE_PIO/lib/TFT_eSPI/examples/Generic/Animated_Eyes_1
Did not use the modified version as it is not open source.

Compilation instructions: There is a mode_eye macro in eye.h
When EYE_MIN is 0, all modes are enabled, with four iris effects
When it is 1, only one iris effect is enabled, only 0, 1, 2 are effective, which greatly reduces memory usage
00: Small default
01: Large default
02: Dual default

03: Small dragon
04: Large dragon
05: Dual dragon

06: Small goat
07: Large goat
08: Dual goat

09: Small noSclera
10: Large noSclera
11: Dual noSclera
*/

/* System variables */
extern bool isCheckAction;
extern ImuAction *act_info;

eye_run *e_run = NULL;

// 128 has about 61 frames, tested 1024 also has only about 63 frames (in original size)
// Changing to 240*240 size, transferring data from pbuffer to pbuffer_m takes a lot of time, and the screen refresh range also increases
// Changing to 240*240 size, pbuffer length must be 128 to ensure rendering a whole line at a time, the screen actually updates two lines (rendering 128 pixels at a time, updating 240*2 pixels at a time)
uint16_t *pbuffer = NULL;   // Buffer for eye rendering algorithm
uint16_t *pbuffer_m = NULL; // Buffer for actual screen refresh (size of one screen line, 240*2)

// Called by updateEye
bool eye_loop(void)
{
    /* MPU6050 data acquisition */
    if (isCheckAction)
    {
        isCheckAction = false;
        act_info = mpu.getAction();

        /* MPU6050 action response */
        if (RETURN == act_info->active)
        {
            tft->fillRect(0, 0, 240, 240, 0);
            e_run->eye_flg = false;
            return true; // Exit this function
        }
        else if (TURN_RIGHT == act_info->active)
        {
            if (millis() - e_run->tempD > 1099)
            {
                tft->fillRect(0, 0, 240, 240, 0);
                e_run->mode_eye--;

#if EYE_MIN
                if (e_run->mode_eye > 11)
                    e_run->mode_eye = 3;
#else
                if (e_run->mode_eye > 11)
                    e_run->mode_eye = 11;
#endif

                if (e_run->mode_eye > 11)
                    e_run->mode_eye = 11;
                e_run->tempD = millis();
            }
        }
        else if (TURN_LEFT == act_info->active)
        {
            if (millis() - e_run->tempD > 1099)
            {
                tft->fillRect(0, 0, 240, 240, 0);
                e_run->mode_eye++;

#if EYE_MIN
                e_run->mode_eye %= 3;
#else
                e_run->mode_eye %= 12;
#endif

                e_run->tempD = millis();
            }
        }
        else if (act_info->active == UP)
        {
        }
        act_info->active = ACTIVE_TYPE::UNKNOWN;
        act_info->isValid = 0;
    }
    return false;
}

void eye_process(lv_obj_t *ym)
{
    lv_obj_t *obj = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0), LV_STATE_DEFAULT);
    lv_scr_load_anim(obj, LV_SCR_LOAD_ANIM_OUT_BOTTOM, 573, 0, false);
    for (uint16_t i = 0; i < 573; i++)
    {
        lv_timer_handler(); // Let LVGL update the screen so the operator can see the executed actions
        delay(1);           //
    }
    e_run = (eye_run *)malloc(sizeof(eye_run));
    pbuffer = (uint16_t *)malloc(128 * 2);
    pbuffer_m = (uint16_t *)malloc(240 * 2);
    initEyes();
    e_run->eye_flg = true;
    e_run->mode_eye = 0;
    e_run->tempD = 0;
    while (e_run->eye_flg)
    {
        updateEye();
    }
    free(pbuffer);
    free(pbuffer_m);
    free(e_run);
    lv_scr_load_anim(ym, LV_SCR_LOAD_ANIM_OUT_TOP, 573, 0, false); // Wait for the animation to finish before calling the system exit function, otherwise it will cause a system restart
    lv_obj_invalidate(lv_scr_act());                               // Even if the cache hasn't changed, let lvgl update the entire screen next time
    /* Delay 999ms to prevent simultaneous app exit */
    for (uint16_t i = 0; i < 898 + 500; i++)
    {
        lv_timer_handler(); // Let LVGL update the screen so the operator can see the executed actions
        delay(1);           //
    }
    lv_obj_clean(obj);
    lv_obj_del(obj);
}

// Space usage Eye type Whether to adopt
// 68.3 default v
// 66.5 cat x
// 70.6 doe x
// 67.8 goat x
// 65.3 owl x
// 72.0 dragon
// 65.3 nauga x
// 72.0 noSclera x
// 68.3 newt v
// 68.3 terminator v
