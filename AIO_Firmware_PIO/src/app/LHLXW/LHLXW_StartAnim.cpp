#include "LHLXW_StartAnim.h"
#include "arduino.h"

#define LCD_W 240
#define LCD_H 240
#define log_bar_w 118
#define tim_log_bar 1000 // bar auto-increment duration, unit ms
#define log_anim_bg "S:/LH&LXW/log_anim/bg.bin"

static void anim_x_cb1(lv_obj_t *var,int32_t v){
    lv_obj_set_y(var,v);
}
static void anim_x_cb2(lv_obj_t *var,int32_t v){
    lv_obj_set_y(var,v);
}
static void anim_x_cb3(lv_obj_t *var,int32_t v){
    lv_obj_set_style_text_opa(var,v,LV_STATE_DEFAULT);
}
static void anim_x_cb4(lv_obj_t *var,int32_t v){
    lv_obj_set_style_img_opa(var,v,0);
}

void startLog(lv_obj_t *ym){
    
    // Create a log anim screen and switch to this screen
    lv_obj_t *LOG_SCR = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(LOG_SCR,lv_color_hex(0),LV_STATE_DEFAULT); // Set the background color of this active page to black
    lv_scr_load(LOG_SCR);
    // Refresh screen and cache
    lv_obj_invalidate(LOG_SCR);
    // lv_task_handler();
    // Create log anim background image
    lv_obj_t *bg_img = lv_img_create(LOG_SCR);
    lv_img_set_src(bg_img,log_anim_bg);
    // Set background transparency to 0
    lv_obj_set_style_img_opa(bg_img, 0,0);
    // Create a bar component
    lv_obj_t* log_bar = lv_bar_create(bg_img);
    lv_obj_set_pos(log_bar,(LCD_W-log_bar_w)/2,LCD_H/2-10);

    // Set bar indicator background color and transparency to visible (0xa8ff78,0x78ffd6)
    lv_obj_set_style_bg_color( log_bar, lv_color_hex(0x00f260),LV_STATE_DEFAULT|LV_PART_INDICATOR); // Gradient start color
    lv_obj_set_style_bg_grad_color(log_bar,lv_color_hex(0x0575e6),LV_STATE_DEFAULT|LV_PART_INDICATOR); // Gradient end color
    lv_obj_set_style_bg_grad_dir(log_bar,LV_GRAD_DIR_HOR,LV_STATE_DEFAULT|LV_PART_INDICATOR); // Enable gradient color
    lv_obj_set_style_bg_opa(log_bar,255,LV_STATE_DEFAULT|LV_PART_INDICATOR);
    // Set bar main background color and transparency to invisible
    lv_obj_set_style_bg_color(log_bar,lv_color_hex(0),LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(log_bar,0,LV_STATE_DEFAULT);
    // Set bar shape to strip shape
    lv_obj_set_size(log_bar,log_bar_w,5);
    lv_bar_set_range(log_bar,0,log_bar_w); // Set value range (range should be set before setting value!)
    lv_obj_set_style_anim_time( log_bar, tim_log_bar,LV_STATE_DEFAULT ); // Animation should also be set before setting value, otherwise the effect will not be seen (time unit is ms)
    lv_bar_set_mode(log_bar,LV_BAR_MODE_NORMAL); // Draw from zero value to current value (current value can be less than 0)
    lv_obj_update_layout(log_bar); // Update configuration to component
    lv_bar_set_value(log_bar,log_bar_w,LV_ANIM_ON); // Set the bar value to the specified value, it will be completed within tim_log_bar time

    // Set log label, not inserting memory card will cause label position to be incorrect
    lv_obj_t* log_label = lv_label_create(bg_img);
    lv_obj_align(log_label,LV_ALIGN_CENTER,0,10); // Center based on image and offset down by 10
    lv_obj_set_style_text_font(log_label,&lv_font_montserrat_24,LV_STATE_DEFAULT ); // Need to enable the corresponding macro of this font in lv_conf.h
    lv_label_set_text(log_label,"LH&LXW");
    lv_obj_set_style_text_color(log_label,lv_color_hex(0xa8a078),LV_STATE_DEFAULT); // Do not set gradient color here, because the gradient color of characters is based on individual characters
    lv_obj_set_style_text_opa(log_label,0,LV_STATE_DEFAULT); // Set background color transparency

    // log bar coordinate change animation
    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1,log_bar);
    lv_anim_set_values(&a1,LCD_H/2-10,LCD_H/2+10);
    lv_anim_set_time(&a1,800);
    lv_anim_set_exec_cb(&a1,(lv_anim_exec_xcb_t)anim_x_cb1);
    lv_anim_set_path_cb(&a1,lv_anim_path_ease_out);
    lv_anim_set_delay(&a1, 700); // Start this animation 1000-700=300ms before the value change is completed

    // log label coordinate change animation
    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2,log_label);
    lv_anim_set_values(&a2,20-10,5-10);
    lv_anim_set_time(&a2,1100);
    lv_anim_set_exec_cb(&a2,(lv_anim_exec_xcb_t)anim_x_cb2);
    lv_anim_set_path_cb(&a2,lv_anim_path_linear);
    lv_anim_set_delay(&a2, 700); // Synchronize bar coordinate changes

    // log label transparency change animation
    lv_anim_t a3;
    lv_anim_init(&a3);
    lv_anim_set_var(&a3,log_label);
    lv_anim_set_values(&a3,0,255);
    lv_anim_set_time(&a3,1500);
    lv_anim_set_exec_cb(&a3,(lv_anim_exec_xcb_t)anim_x_cb3);
    lv_anim_set_path_cb(&a3,lv_anim_path_linear);
    lv_anim_set_delay(&a3, 700);

    // log background color transparency change animation
    lv_anim_t a4;
    lv_anim_init(&a4);
    lv_anim_set_var(&a4,bg_img);
    lv_anim_set_values(&a4,0,255);
    lv_anim_set_time(&a4,1400);
    lv_anim_set_exec_cb(&a4,(lv_anim_exec_xcb_t)anim_x_cb4);
    lv_anim_set_path_cb(&a4,lv_anim_path_ease_in);

    // Switch log anim page
    lv_scr_load(LOG_SCR);

    // Start animation
    lv_anim_start(&a1);
    lv_anim_start(&a2);
    lv_anim_start(&a3);
    lv_anim_start(&a4);
    
    // Wait for animation to end
    // You can also use the lv_anim_set_ready_cb function to achieve this
    for(uint16_t i=0;i<2000;i++){
        lv_task_handler();
        delay(1);
    }
    // Smooth transition to the emoji menu, while deleting the old screen (do not use the delete function that comes with this function, delete it manually after execution)
    lv_scr_load_anim(ym, LV_SCR_LOAD_ANIM_OUT_BOTTOM, 573, 0, false); // Upward animation, switch to this page

    // Add delay here to prevent system errors caused by deleting animation objects before the animation is completed
    for(uint16_t i=0;i<573;i++){
        lv_task_handler();
        delay(1);
    }

    // Delete all components of the startup log animation
    lv_obj_clean(LOG_SCR);
    lv_obj_del(LOG_SCR);
}
