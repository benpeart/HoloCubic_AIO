#ifndef LV_LHLXW_GUI_H__
#define LV_LHLXW_GUI_H__
#include "lvgl.h"

struct LHLXW_RUN
{
    uint8_t option_num;         // Current option number 0-4
    lv_obj_t *LV_LHLXW_GUI_OBJ; // APP UI interface
    lv_obj_t *LV_BACKUP_OBJ;    // Backup system interface
    lv_obj_t *option_fun[5];    // Function options
    lv_obj_t *option_label;     // Option label
};

void LHLXW_GUI_Init(void);
void SWITCH_OPTION(bool _flg_, uint8_t mode);
void LHLXW_GUI_DeInit(void);

#endif
