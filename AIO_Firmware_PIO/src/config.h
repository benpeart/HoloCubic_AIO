#define NEW_FLASH_FS
#ifndef NEW_FLASH_FS

/***************************************************
  Since a new file system is used, the functions implemented in config.cpp/config.h
have been deprecated and the code is retained for reference.

  Github repositories：https://github.com/ClimbSnail/HoloCubic_AIO

  Last review/edit by ClimbSnail: 2023/03/14
 ****************************************************/

#ifndef CONFIG_H
#define CONFIG_H
#include <WString.h>
#include <Preferences.h>

extern Preferences prefs;       // Declare Preferences object

struct MPU_Config
{
    int16_t x_gyro_offset;
    int16_t y_gyro_offset;
    int16_t z_gyro_offset;

    int16_t x_accel_offset;
    int16_t y_accel_offset;
    int16_t z_accel_offset;
};

struct Config
{
    String ssid;
    String password;
    String cityname;              // Displayed city
    String language;              // Address code for weather query
    String weather_key;           // Zhixin weather api_key (secret key)
    String tianqi_appid;          // tianqiapid's appid
    String tianqi_appsecret;      // tianqiapid's appsecret
    String tianqi_addr;           // tianqiapid's address (fill in Chinese)
    String bili_uid;              // bilibili's uid
    uint8_t backLight;            // Screen brightness (1-100)
    uint8_t rotation;             // Screen rotation direction
    uint8_t auto_calibration_mpu; // Whether to automatically calibrate the gyroscope: 0 to disable automatic calibration, 1 to enable automatic calibration
    uint8_t mpu_order;
    MPU_Config mpu_config; // Save the calibration data of the mpu
};

void config_read(const char *file_path, Config *cfg);

void config_save(const char *file_path, Config *cfg);

void mpu_config_read(const char *file_path, Config *cfg);

void mpu_config_save(const char *file_path, Config *cfg);

#endif

#endif