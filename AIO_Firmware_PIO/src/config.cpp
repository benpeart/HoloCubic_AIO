#include <WString.h>
#include "common.h"
#include "config.h"

#ifndef NEW_FLASH_FS

/***************************************************
  Since a new file system is used, the functions implemented in config.cpp/config.h
have been deprecated and the code is retained for reference.

  Github repositories：https://github.com/ClimbSnail/HoloCubic_AIO

  Last review/edit by ClimbSnail: 2023/03/14
 ****************************************************/

Preferences prefs;        // Declare Preferences object

void config_read(const char *file_path, Config *cfg)
{
    // cfg->ssid = tf.readFileLine(file_path, 1);        // line-1 for WiFi ssid
    // cfg->password = tf.readFileLine(file_path, 2);    // line-2 for WiFi password
    // return cfg->ssid+cfg->password+cfg->cityname+cfg->language+cfg->weather_key;

    prefs.begin("sys"); // Open namespace "sys"
    cfg->backLight = prefs.getUChar("backLight", 80);
    cfg->rotation = prefs.getUChar("rotation", 4);
    cfg->auto_calibration_mpu = prefs.getUChar("auto_mpu", 1);
    cfg->mpu_order = prefs.getUChar("mpu_order", 0);
    cfg->ssid = prefs.getString("ssid", "");
    cfg->password = prefs.getString("password", "");
    prefs.end(); // Close current namespace

    prefs.begin("zhixin"); // Open namespace "zhixin"
    cfg->cityname = prefs.getString("cityname", "BeiJing");
    cfg->language = prefs.getString("language", "zh-Hans");
    cfg->weather_key = prefs.getString("weather_key", "");
    prefs.end(); // Close current namespace

    prefs.begin("tianqi"); // Open namespace "tianqi"
    cfg->tianqi_appid = prefs.getString("tianqi_aid", "");
    cfg->tianqi_appsecret = prefs.getString("tianqi_as", "");
    cfg->tianqi_addr = prefs.getString("tianqi_addr", "北京");
    prefs.end(); // Close current namespace

    prefs.begin("other"); // Open namespace "other"
    cfg->bili_uid = prefs.getString("bili_uid", "");
    prefs.end(); // Close current namespace

    // if (0 == cfg->auto_calibration_mpu)
    // {
    // Read the calibration data of the mpu
    mpu_config_read(file_path, cfg);
    // }
}

// void config_read(const char *file_path, Config *cfg)
// {
//     // cfg->ssid = tf.readFileLine(file_path, 1);        // line-1 for WiFi ssid
//     // cfg->password = tf.readFileLine(file_path, 2);    // line-2 for WiFi password
//     // return cfg->ssid+cfg->password+cfg->cityname+cfg->language+cfg->weather_key;

//     prefs.begin("sys"); // Open namespace "sys"
//     cfg->backLight = prefs.getUChar("backLight", 100);
//     cfg->rotation = prefs.getUChar("rotation", 4);
//     cfg->auto_calibration_mpu = prefs.getUChar("auto_mpu", 1);
//     cfg->ssid = prefs.getString("ssid", "902");
//     cfg->password = prefs.getString("password", "7#59027#5902");
//     prefs.end(); // Close current namespace

//     prefs.begin("zhixin"); // Open namespace "zhixin"
//     cfg->cityname = prefs.getString("cityname", "BeiJing");
//     // cfg->cityname = prefs.getString("cityname", "北京");
//     cfg->language = prefs.getString("language", "zh-Hans");
//     cfg->weather_key = prefs.getString("weather_key", "SfGOpgf5IPnqgFbke");
//     prefs.end(); // Close current namespace

//     prefs.begin("tianqi"); // Open namespace "tianqi"
//     cfg->tianqi_appid = prefs.getString("tianqi_aid", "84682835");
//     cfg->tianqi_appsecret = prefs.getString("tianqi_as", "35rAfhRZ");
//     cfg->tianqi_addr = prefs.getString("tianqi_addr", "北京");
//     prefs.end(); // Close current namespace

//     prefs.begin("other"); // Open namespace "other"
//     cfg->bili_uid = prefs.getString("bili_uid", "344470052");
//     prefs.end(); // Close current namespace

//     // if (0 == cfg->auto_calibration_mpu)
//     // {
//     // Read the calibration data of the mpu
//     mpu_config_read(file_path, cfg);
//     // }
// }

void config_save(const char *file_path, Config *cfg)
{
    // String line("\n");
    // String res = cfg->ssid + line + cfg->password + line + cfg->cityname + line + cfg->language + line + cfg->weather_key;
    // Serial.println(res);
    // tf.deleteFile(file_path);
    // tf.writeFile(file_path, res.c_str());

    prefs.begin("sys"); // Open namespace "sys"
    prefs.putUChar("backLight", cfg->backLight);
    prefs.putUChar("rotation", cfg->rotation);
    prefs.putUChar("auto_mpu", cfg->auto_calibration_mpu);
    prefs.putUChar("mpu_order", cfg->mpu_order);
    prefs.putString("ssid", cfg->ssid);
    prefs.putString("password", cfg->password);
    prefs.end(); // Close current namespace

    prefs.begin("zhixin"); // Open namespace "zhixin"
    prefs.putString("cityname", cfg->cityname);
    prefs.putString("language", cfg->language);
    prefs.putString("weather_key", cfg->weather_key);
    prefs.end(); // Close current namespace

    prefs.begin("tianqi"); // Open namespace "tianqi"
    prefs.putString("tianqi_aid", cfg->tianqi_appid);
    prefs.putString("tianqi_as", cfg->tianqi_appsecret);
    prefs.putString("tianqi_addr", cfg->tianqi_addr);
    prefs.end(); // Close current namespace

    prefs.begin("other"); // Open namespace "other"
    prefs.putString("bili_uid", cfg->bili_uid);
    prefs.end(); // Close current namespace

    // config_read("/wifi.txt", &g_cfg);
    // // Immediately change the screen direction
    // screen.setBackLight(g_cfg.backLight / 100.0);
    // tft->setRotation(g_cfg.rotation);
    // mpu.setOrder(g_cfg.mpu_order);
}

void mpu_config_read(const char *file_path, Config *cfg)
{

    prefs.begin("MPU_Config"); // Open namespace "MPU_Config"
    cfg->mpu_config.x_gyro_offset = prefs.getInt("x_gyro_offset", 0);
    cfg->mpu_config.y_gyro_offset = prefs.getInt("y_gyro_offset", 0);
    cfg->mpu_config.z_gyro_offset = prefs.getInt("z_gyro_offset", 0);
    cfg->mpu_config.x_accel_offset = prefs.getInt("x_accel_offset", 0);
    cfg->mpu_config.y_accel_offset = prefs.getInt("y_accel_offset", 0);
    cfg->mpu_config.z_accel_offset = prefs.getInt("z_accel_offset", 0);
    prefs.end(); // Close current namespace
}

void mpu_config_save(const char *file_path, Config *cfg)
{
    prefs.begin("MPU_Config"); // Open namespace "MPU_Config"
    prefs.putInt("x_gyro_offset", cfg->mpu_config.x_gyro_offset);
    prefs.putInt("y_gyro_offset", cfg->mpu_config.y_gyro_offset);
    prefs.putInt("z_gyro_offset", cfg->mpu_config.z_gyro_offset);
    prefs.putInt("x_accel_offset", cfg->mpu_config.x_accel_offset);
    prefs.putInt("y_accel_offset", cfg->mpu_config.y_accel_offset);
    prefs.putInt("z_accel_offset", cfg->mpu_config.z_accel_offset);

    prefs.end(); // Close current namespace
}

#endif