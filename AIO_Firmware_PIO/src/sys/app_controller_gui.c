#include "app_controller_gui.h"
// #include "lvgl.h"

// Must be defined as global or static
static lv_obj_t *app_scr = NULL;
static lv_obj_t *app_scr_t = NULL;
static lv_obj_t *pre_app_image = NULL;
static lv_obj_t *pre_app_name = NULL;
static lv_obj_t *now_app_image = NULL;
static lv_obj_t *now_app_name = NULL;
const void *pre_img_path = NULL;

static lv_style_t default_style;
static lv_style_t app_name_style;

LV_FONT_DECLARE(lv_font_montserrat_24);

void app_control_gui_init(void)
{
    if (NULL != app_scr)
    {
        lv_obj_clean(app_scr);
        app_scr = NULL;
    }

    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, lv_color_hex(0x000000));
    lv_style_set_radius(&default_style, 0); // Set control corner radius
    // Set border width
    lv_style_set_border_width(&default_style, 0);

    lv_style_init(&app_name_style);
    lv_style_set_text_opa(&app_name_style, LV_OPA_COVER);
    lv_style_set_text_color(&app_name_style, lv_color_white());
    lv_style_set_text_font(&app_name_style, &lv_font_montserrat_24);

    // APP icon page
    app_scr = lv_obj_create(NULL);
    lv_obj_add_style(app_scr, &default_style, LV_STATE_DEFAULT);
    // Set scrollbar to not display
    lv_obj_set_style_bg_opa(app_scr, LV_OPA_0,
                            LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    // lv_obj_set_size(app_scr, 240, 240);
    // lv_obj_align(app_scr, LV_ALIGN_CENTER, 0, 0);
    // lv_scr_load(app_scr);

    // To eliminate the partial white screen issue at startup, add the following layer (consider deleting or improving)
    app_scr_t = lv_obj_create(app_scr);
    lv_obj_add_style(app_scr_t, &default_style, LV_STATE_DEFAULT);
    lv_obj_set_size(app_scr_t, 240, 240);
    lv_obj_align(app_scr_t, LV_ALIGN_CENTER, 0, 0);
    lv_scr_load(app_scr_t);
}

void app_control_gui_release(void)
{
    if (NULL != app_scr)
    {
        lv_obj_clean(app_scr);
        app_scr = NULL;
    }
}

void display_app_scr_init(const void *src_img_path, const char *app_name)
{
    lv_obj_t *act_obj = lv_scr_act(); // Get the current active page
    if (act_obj == app_scr)
    {
        // Prevent some apps that do not use lvgl from exiting, causing the screen to not update without other actions
        lv_scr_load_anim(app_scr, LV_SCR_LOAD_ANIM_NONE, 300, 300, false);
        return;
    }

    lv_obj_clean(act_obj); // Clear the previous page
    pre_app_image = lv_img_create(app_scr);
    pre_img_path = src_img_path; // Save history
    lv_img_set_src(pre_app_image, src_img_path);
    lv_obj_align(pre_app_image, LV_ALIGN_CENTER, 0, -20);

    // Add the APP name
    pre_app_name = lv_label_create(app_scr);
    lv_obj_add_style(pre_app_name, &app_name_style, LV_STATE_DEFAULT);
    // lv_label_set_recolor(pre_app_name, true); // First enable text recolor function
    lv_label_set_text(pre_app_name, app_name);
    lv_obj_align_to(pre_app_name, pre_app_image, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    lv_scr_load_anim(app_scr, LV_SCR_LOAD_ANIM_NONE, 300, 300, false);
}

void app_control_display_scr(const void *src_img, const char *app_name, lv_scr_load_anim_t anim_type, bool force)
{
    // force indicates whether to force refresh the page, true means force refresh
    if (true == force)
    {
        display_app_scr_init(src_img, app_name);
        return;
    }

    if (src_img == pre_img_path)
    {
        return;
    }

    pre_img_path = src_img;
    int now_start_x;
    int now_end_x;
    int old_start_x;
    int old_end_x;

    if (LV_SCR_LOAD_ANIM_MOVE_LEFT == anim_type)
    {
        // 120 is half the screen size, the application icon is specified as 128, half is exactly 64
        now_start_x = -120 - 64;
        now_end_x = 0;
        old_start_x = 0;
        old_end_x = 120 + 64;
    }
    else
    {
        // 120 is half the screen size, the application icon is specified as 128, half is exactly 64
        now_start_x = 120 + 64;
        now_end_x = 0;
        old_start_x = 0;
        old_end_x = -120 - 64;
    }

    now_app_image = lv_img_create(app_scr);
    lv_img_set_src(now_app_image, src_img);
    lv_obj_align(now_app_image, LV_ALIGN_CENTER, 0, -20);
    // Add the APP name
    now_app_name = lv_label_create(app_scr);
    lv_obj_add_style(now_app_name, &app_name_style, LV_STATE_DEFAULT);
    // lv_label_set_recolor(now_app_name, true); // First enable text recolor function
    lv_label_set_text(now_app_name, app_name);
    // Delete the original APP name
    lv_obj_del(pre_app_name);
    pre_app_name = now_app_name;
    lv_obj_align_to(now_app_name, now_app_image, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    static lv_anim_t now_app;
    lv_anim_init(&now_app);
    lv_anim_set_exec_cb(&now_app, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_var(&now_app, now_app_image);
    lv_anim_set_values(&now_app, now_start_x, now_end_x);
    uint32_t duration = lv_anim_speed_to_time(400, now_start_x, now_end_x); // Calculate time
    lv_anim_set_time(&now_app, duration);
    lv_anim_set_path_cb(&now_app, lv_anim_path_linear); // Set an animation path

    static lv_anim_t pre_app;
    lv_anim_init(&pre_app);
    lv_anim_set_exec_cb(&pre_app, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_var(&pre_app, pre_app_image);
    lv_anim_set_values(&pre_app, old_start_x, old_end_x);
    duration = lv_anim_speed_to_time(400, old_start_x, old_end_x); // Calculate time
    lv_anim_set_time(&pre_app, duration);
    lv_anim_set_path_cb(&pre_app, lv_anim_path_linear); // Set an animation path

    lv_anim_start(&now_app);
    lv_anim_start(&pre_app);
    ANIEND_WAIT
    lv_task_handler(); // Eliminate the issue of "stuttering" after ANIEND_WAIT execution

    lv_obj_del(pre_app_image); // Delete the previous image
    pre_app_image = now_app_image;
}