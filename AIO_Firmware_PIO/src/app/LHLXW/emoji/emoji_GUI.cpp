#include "lvgl.h"
#include "EMOJI.h"
#include "../LHLXW_StartAnim.h"
#include "stdlib.h"
#include "sys/app_controller.h"

extern EMOJI_RUN *emj_run;

void next_emoji(void){
    lv_group_focus_next(emj_run->optionListGroup);
}
void prev_emoji(void){
    lv_group_focus_prev(emj_run->optionListGroup);
}

// APP input device key value read callback function (lvgl will call it periodically with LV_INDEV_DEF_READ_PERIOD)
// After exiting the APP, the created input device indev_mpu6050key is deleted, so the system (lvgl) will no longer call it
static void mpu6050key_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data){
    // uint8_t act_key = mpu6050key_var; // Changed by LHLXW_process function action->active value
    if(emj_run->mpu6050key_var!=0){ // mpu6050key_var is changed by LHLXW_process function action->active value
        data->state = LV_INDEV_STATE_PR;
        switch(emj_run->mpu6050key_var){
            case 1:
                data->key = LV_KEY_NEXT; // Next
            break;
            case 2:
                data->key = LV_KEY_PREV; // Previous
            break;
        }
    }else{
        data->state = LV_INDEV_STATE_REL;
    }
}

// Focus change callback function
// The reason for writing a callback function to change the current selected emoji number is that trying to write this function in mpu6050key_read function or
// LHLXW_process function will cause the emoji_var value to not match the focused emoji when quickly changing the focus
void focus_alter_cb(){
    if(emj_run->emoji_mode){
        if(emj_run->mpu6050key_var == 1){ // Scroll down
            emj_run->emoji_var++;
            if(emj_run->emoji_var>emj_run->emoji_Maxnum)emj_run->emoji_var = 1;
        }else{ // Scroll up
            emj_run->emoji_var--;
            if(emj_run->emoji_var<1)emj_run->emoji_var = emj_run->emoji_Maxnum;
        }
        emj_run->mpu6050key_var = 0;
    }
}

// emoji GUI initialization
void EMOJI_GUI_Init(void){
    emj_run->EMOJI_GUI_OBJ = lv_obj_create(NULL); // Create an empty active page as the app main page

    lv_obj_set_style_bg_color(emj_run->EMOJI_GUI_OBJ,lv_color_hex(0),LV_STATE_DEFAULT); // Set the background color of this active page to black

    static lv_indev_drv_t mpu6050key_driver; // Create input device (must use static, otherwise it will cause system reboot)
    lv_indev_drv_init(&mpu6050key_driver); // Initialize input device
    mpu6050key_driver.type = LV_INDEV_TYPE_KEYPAD; // Set input device type to keyboard
    mpu6050key_driver.read_cb = mpu6050key_read; // Keyboard value read function (lvgl will call it periodically with LV_INDEV_DEF_READ_PERIOD)
    emj_run->indev_mpu6050key = lv_indev_drv_register(&mpu6050key_driver); // Register driver device, return pointer to new device
    emj_run->optionListGroup= lv_group_create(); // Create a group
    lv_indev_set_group(emj_run->indev_mpu6050key, emj_run->optionListGroup); // Associate input device with group
    
    char *path = (char*)malloc(38); // Must use char* type, cannot use uint8_t*
    lv_obj_t *option_obj; // Button component
    lv_obj_t *optionImg_obj; // Image component, cannot be selected directly with image button component

    for(uint8_t i = 0;i<emj_run->emoji_Maxnum; i++){
        option_obj = lv_btn_create(emj_run->EMOJI_GUI_OBJ); // Create button component based on empty page
        lv_obj_set_size(option_obj,60,60); // Set size
        lv_obj_set_style_bg_color(option_obj,lv_color_hex(0),LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(option_obj,lv_color_hex(0x00ff00),LV_STATE_FOCUSED); // Set background color
        lv_obj_set_x(option_obj,15+(i%3)*75); // Set coordinates
        lv_obj_set_y(option_obj,15+(i/3)*75); // Set coordinates
        lv_group_add_obj(emj_run->optionListGroup,option_obj); // Add button to group

        optionImg_obj = lv_img_create(option_obj); // Create image component based on button component
        lv_obj_align(optionImg_obj,LV_ALIGN_CENTER,0,-1); // Align to center of button component, offset up by 1
        sprintf(path,"S:/LH&LXW/emoji/images/image%d.bin",i+1); // Icon path
        lv_img_set_src(optionImg_obj,path); // Set image source
    }
    lv_group_set_focus_cb(emj_run->optionListGroup,(lv_group_focus_cb_t)focus_alter_cb);
    lv_scr_load_anim(emj_run->EMOJI_GUI_OBJ, LV_SCR_LOAD_ANIM_OUT_BOTTOM, 580, 0, false); // Before calling system exit function, must wait for animation to finish, otherwise it will cause system reboot
    /* Adding delay here to prevent system error caused by calling system exit function or deleting animation object before animation is completed */
    for(uint16_t i=0;i<780;i++){
        lv_task_handler();
        delay(1);
    }
    free(path);
}


void EMOJI_GUI_DeInit(lv_obj_t *ym){
    lv_indev_delete(emj_run->indev_mpu6050key); // Delete input device
    lv_group_del(emj_run->optionListGroup); // Delete APP option list group
    /* Switch page, and delete old screen (do not use the delete function of this function, manually delete after execution) */
    lv_scr_load_anim(ym, LV_SCR_LOAD_ANIM_OUT_TOP, 580, 0, false); // Before calling system exit function, must wait for animation to finish, otherwise it will cause system reboot

    /* Adding delay here to prevent system error caused by calling system exit function or deleting animation object before animation is completed */
    for(uint16_t i=0;i<780;i++){
        lv_task_handler();
        delay(1);
    }
    /* If you want to manually delete the object, you must delete it after the animation is completed, otherwise there will be problems */
    lv_obj_clean(emj_run->EMOJI_GUI_OBJ); // Delete all child items of the object
    lv_obj_del(emj_run->EMOJI_GUI_OBJ); // Delete object (tested to release memory, no memory leak)
}
