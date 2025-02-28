#include "LHLXW_GUI.h"
#include "LHLXW_StartAnim.h"
#include "arduino.h"

LV_FONT_DECLARE(APP_OPTION_ico); // Define option character

LHLXW_RUN *lhlxw_run = NULL;

// Function option gradient color style
static const int option_color[5][2] = {
    {0x7303c0,0xec38bc},
    {0xdcffbd,0xcc86d1},
    {0xfc466b,0x3f5efb},
    {0xfbd786,0x1cefff},
    {0x00f260,0x0575e6},
};

// Function option x coordinate constants
static const uint8_t x_zu[5]      = {24,46,74,130,168};
// Function option y coordinate constants
static const uint8_t y_zu[5]      = {88,72,54,72,88};
// Function option width constants
static const uint8_t width_zu[5]  = {50,68,100,68,50};
// Function option height constants
static const uint8_t height_zu[5] = {92,124,160,124,92};

// With the above four arrays, it is enough. Here, for convenience of writing programs, the following arrays are added
static const uint8_t obj_var[5][4][2]={
  //   x        y       w       h
    {{168,24},{88,88},{48,48},{92,92}},   // 4 changes to 0
    {{24,46},{88,72},{48,64},{92,124}},  // 0 changes to 1
    {{46,74},{72,54},{64,92},{124,160}}, // 1 changes to 2
    {{74,130},{54,72},{92,64},{160,124}},// 2 changes to 3
    {{130,168},{72,88},{64,48},{124,92}},// 3 changes to 4
};

// Relationship between layer and option_num
struct tierMode{
    uint8_t tierButton[3]; // Button layer
    char tierText[12]; // Label layer
};
#define OPTION_1  "\xee\x99\xa1" // Eye
#define OPTION_2  "\xee\x98\xab" // Dice
#define OPTION_3  "\xee\x98\x8d" // Heartbeat
#define OPTION_4  "\xee\x98\x9d" // Code
#define OPTION_5  "\xee\x98\xb0" // Emoji
static const struct tierMode tier_mode[5] = {
    {{2,1,3},OPTION_1},
    {{1,2,0},OPTION_2},
    {{0,1,4},OPTION_3},
    {{4,0,3},OPTION_4},
    {{3,4,2},OPTION_5}
};

static void x_cb(lv_obj_t *var,int32_t v){
    lv_obj_set_x(var,v);
}
static void y_cb(lv_obj_t *var,int32_t v){
    lv_obj_set_y(var,v);
}
static void w_cb(lv_obj_t *var,int32_t v){
    lv_obj_set_width(var,v);
}
static void h_cb(lv_obj_t *var,int32_t v){
    lv_obj_set_height(var,v);
}


void LHLXW_GUI_Init(void){
    lhlxw_run->LV_BACKUP_OBJ = lv_scr_act(); // Backup the previous screen to restore it when exiting the APP (it has been tested that not switching to the backup screen when exiting the APP will cause problems)
    lhlxw_run->LV_LHLXW_GUI_OBJ = lv_obj_create(NULL); // Create an empty active page as the main page of the app
    // If the startup animation is placed here, it can avoid occupying a lot of memory at once, but after the animation ends, the appearance of the emoji menu is very abrupt
    // startLog(LV_LHLXW_GUI_OBJ); // Start log animation, after the animation ends, it will switch to the LV_LHLXW_GUI_OBJ page, which is the main page of the APP
    
    lv_obj_set_style_bg_color(lhlxw_run->LV_LHLXW_GUI_OBJ,lv_color_hex(0),LV_STATE_DEFAULT);
   
    for(uint8_t i=0;i<5;i++){
        lhlxw_run->option_fun[i] = lv_btn_create(lhlxw_run->LV_LHLXW_GUI_OBJ);
        lv_obj_set_pos(lhlxw_run->option_fun[i],x_zu[i],y_zu[i]);
        lv_obj_set_size(lhlxw_run->option_fun[i],width_zu[i],height_zu[i]);
        lv_obj_set_style_bg_color(lhlxw_run->option_fun[i], lv_color_hex(option_color[i][0]),LV_STATE_DEFAULT); // Starting color
        lv_obj_set_style_bg_grad_color(lhlxw_run->option_fun[i],lv_color_hex(option_color[i][1]),LV_STATE_DEFAULT); // Ending color
        lv_obj_set_style_bg_grad_dir(lhlxw_run->option_fun[i],LV_GRAD_DIR_VER,LV_STATE_DEFAULT); // Enable gradient color
    }

    lv_obj_move_foreground(lhlxw_run->option_fun[tier_mode[0].tierButton[2]]);
    lv_obj_move_foreground(lhlxw_run->option_fun[tier_mode[0].tierButton[1]]);
    lv_obj_move_foreground(lhlxw_run->option_fun[tier_mode[0].tierButton[0]]);

    lhlxw_run->option_label = lv_label_create(lhlxw_run->LV_LHLXW_GUI_OBJ); // Create a label based on the button
    lv_obj_set_align(lhlxw_run->option_label,LV_ALIGN_CENTER);
    lv_obj_set_style_text_font(lhlxw_run->option_label,&APP_OPTION_ico,LV_STATE_DEFAULT );
    lv_label_set_text(lhlxw_run->option_label,tier_mode[0].tierText);
    // Placing it here will cause the emoji page and the animation page to exist at the same time, which requires a lot of RAM
    startLog(lhlxw_run->LV_LHLXW_GUI_OBJ); // Start log animation, after the animation ends, it will switch to the LV_LHLXW_GUI_OBJ page, which is the main page of the APP
}

/* Switch options */
void SWITCH_OPTION(bool _flg_,uint8_t mode){
    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_time(&a1,607);
    lv_anim_set_path_cb(&a1,lv_anim_path_ease_in);
    for(uint8_t i=0;i<5;i++){
        lv_anim_set_var(&a1,lhlxw_run->option_fun[i]);
        for(uint8_t ii=0;ii<4;ii++){
            if(_flg_) // Left to right
                lv_anim_set_values(&a1,obj_var[(i+mode)%5][ii][0],obj_var[(i+mode)%5][ii][1]);
            else // Right to left
                lv_anim_set_values(&a1,obj_var[(i+mode+1)%5][ii][1],obj_var[(i+mode+1)%5][ii][0]);
            switch(ii){
                case 0: // x changes
                    lv_anim_set_exec_cb(&a1,(lv_anim_exec_xcb_t)x_cb);
                break;
                case 1: // y changes
                    lv_anim_set_exec_cb(&a1,(lv_anim_exec_xcb_t)y_cb);
                break;
                case 2: // width changes
                    lv_anim_set_exec_cb(&a1,(lv_anim_exec_xcb_t)w_cb);
                break;
                case 3: // height changes
                    lv_anim_set_exec_cb(&a1,(lv_anim_exec_xcb_t)h_cb);
                break;
            }
            lv_anim_start(&a1);
        }
    }
    lv_obj_move_foreground(lhlxw_run->option_fun[tier_mode[mode].tierButton[2]]);
    lv_obj_move_foreground(lhlxw_run->option_fun[tier_mode[mode].tierButton[1]]);
    lv_obj_move_foreground(lhlxw_run->option_fun[tier_mode[mode].tierButton[0]]);
    lv_label_set_text(lhlxw_run->option_label,tier_mode[mode].tierText);
    lv_obj_move_foreground(lhlxw_run->option_label);
}

void LHLXW_GUI_DeInit(void){
    // Switch pages and delete the old screen at the same time (do not use the delete function that comes with this function, wait for execution to complete and then delete manually)
    lv_scr_load_anim(lhlxw_run->LV_BACKUP_OBJ, LV_SCR_LOAD_ANIM_OUT_BOTTOM, 573, 0, false); // Be sure to wait for the animation to end before calling the system exit function, otherwise it will cause the system to restart

    // Adding a delay here is to prevent calling the system exit function or deleting the animation object before the animation is completed, causing system errors
    for(uint16_t i=0;i<573;i++){
        lv_task_handler();
        delay(1);
    }
    // If you want to delete the object manually, you must delete it after the object's animation is completed, otherwise there will be problems
    lv_obj_clean(lhlxw_run->LV_LHLXW_GUI_OBJ); // Delete all child items of the object
    lv_obj_del(lhlxw_run->LV_LHLXW_GUI_OBJ); // Delete the object (it has been tested that it will release memory and will not cause memory leaks)
}
