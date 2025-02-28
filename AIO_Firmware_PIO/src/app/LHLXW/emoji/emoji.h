#ifndef EMOJI_H
#define EMOJI_H

#include "lvgl.h"
#include "sys/app_controller.h"
#include "../../media_player/decoder.h" // Decoder base class


struct EMOJI_RUN{
    uint8_t emoji_var;              // Current emoji index
    uint8_t mpu6050key_var;         // MPU6050 state value after entering the APP, left tilt is 2, right tilt is 1, others are 0
    uint8_t emoji_Maxnum;           // Total number of emojis (manually input as SPIFFS is not used, i.e., read SD card configuration file)
    bool emoji_mode;                // App running mode, true for selecting emoji, false for playing emoji
    PlayDecoderBase *emoji_decoder; // Emoji video decoder
    File emoji_file;                // Emoji video file
    lv_obj_t *EMOJI_GUI_OBJ;        // EMOJI UI interface
    lv_indev_t *indev_mpu6050key;   // Input device pointer
    lv_group_t *optionListGroup;    // APP option list group, used to associate input devices
};
void emoji_process(lv_obj_t *ym);

#endif