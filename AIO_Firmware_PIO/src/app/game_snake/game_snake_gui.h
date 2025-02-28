#ifndef APP_GAME_2048_GUI_H
#define APP_GAME_2048_GUI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"

// Define the movement direction of the snake
typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

#define ANIEND                      \
    while (lv_anim_count_running()) \
        lv_task_handler(); // Wait for the animation to complete

    void game_snake_gui_init(void);
    void generate_food();
    void update_direction(Direction dir);
    void display_snake(int gameStatus, lv_scr_load_anim_t anim_type);
    void game_snake_gui_del(void);

#ifdef __cplusplus
} /* extern "C" */
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"
    extern const lv_img_dsc_t app_game_snake;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif