#include "Arduino.h"
#include "DigitalRainAnimation.hpp"
#include "sys/app_controller.h"
#include "common.h"

/*
Function: Code Rain
Description: Referenced from https://github.com/0015/TP_Arduino_DigitalRain_Anim recommended by the workshop director
Switch size left and right
*/

/* System variables */
extern bool isCheckAction;
extern ImuAction *act_info;


void codeRain_process(lv_obj_t * ym){
  DigitalRainAnimation<TFT_eSPI> *matrix_effect = new DigitalRainAnimation<TFT_eSPI>();
  bool codeSizeFont = false; // 123564
  lv_obj_t *obj = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(obj, lv_color_hex(0), LV_STATE_DEFAULT);
  lv_scr_load_anim(obj, LV_SCR_LOAD_ANIM_OUT_BOTTOM, 573, 0, false);
  /* Delay 999ms to prevent simultaneous app exit */
  for(uint16_t i=0;i<573;i++){
    lv_timer_handler(); // Let LVGL update the screen so the operator can see the executed actions
    delay(1);
  }
  matrix_effect->init(tft, codeSizeFont);
  unsigned long tempD = 0;
  while(1){
    matrix_effect->loop();

    /* MPU6050 data acquisition */
    if (isCheckAction){
      isCheckAction = false;
      act_info = mpu.getAction();
    }

    /* MPU6050 action response */
    if (RETURN == act_info->active){
      lv_scr_load_anim(ym, LV_SCR_LOAD_ANIM_OUT_TOP, 573, 0, false); // Be sure to wait for the animation to finish before calling the system exit function, otherwise it will cause a system restart
      lv_obj_invalidate(lv_scr_act());                               // Even if the cache has not changed, let lvgl update the entire screen next time
      /* Delay 999ms to prevent simultaneous app exit */
        for(uint16_t i=0;i<898+500;i++){
        lv_timer_handler(); // Let LVGL update the screen so the operator can see the executed actions
        delay(1);
      }
      lv_obj_clean(obj);
      lv_obj_del(obj);
      delete matrix_effect;
      return; // Exit this function
    }else if(TURN_RIGHT == act_info->active){
      if(millis()-tempD > 999){
        codeSizeFont = !codeSizeFont;
        matrix_effect->init(tft, codeSizeFont);
        tempD = millis();
      }
    }else if(TURN_LEFT == act_info->active){
      if(millis()-tempD > 999){
        codeSizeFont = !codeSizeFont;
        matrix_effect->init(tft, codeSizeFont);
        tempD = millis();
      }
    }else if(act_info->active == UP){
        
    } 
    act_info->active = ACTIVE_TYPE::UNKNOWN;
    act_info->isValid = 0;
  }
}
