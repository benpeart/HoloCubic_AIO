# An English fork of the HoloCubic_AIO (All in one for HoloCubic) code
The purpose of this fork is to make it easier for me (as an English speaker) to use and in the future modify the code. The only changes so far are to translate it from Chinese to English.

# HoloCubic_AIO (All in one for HoloCubic)
### _You can also read a translated version of this file [in English 英文版](https://github.com/ClimbSnail/HoloCubic_AIO/blob/main/README_English.md) or [in Korean 한국어](./README_English.md)._

`Holocubic` was originally an open-source project by `Zhihui Jun`. This project is an independent third-party firmware project running on `HoloCubic hardware`.

AIO stands for All in one, aiming to integrate as many functions as possible into the Holocubic AIO firmware and adhere to open source. Currently, the firmware source code has reached `20k+` lines, and the upper computer source code has `4k` lines (excluding font library images). We sincerely invite everyone to jointly develop AIO firmware, upper computer, and peripherals to meet the needs of more people.

In addition, the code of this firmware is completely open source for everyone to learn and play. If you use this project for secondary open source or partial reference, please appropriately indicate the reference source.

* Original author's project link: https://github.com/peng-zhihui/HoloCubic
* This project's address: https://github.com/ClimbSnail/HoloCubic_AIO (latest version)
* Or https://gitee.com/ClimbSnailQ/HoloCubic_AIO

### Developers
* AIO framework development and part of the APP writing: [ClimbSnail](https://github.com/ClimbSnail)
* 2048 game application development: [AndyXFuture](https://github.com/AndyXFuture)
* New weather clock application development: [PuYuuu](https://github.com/PuYuuu)
* BiliBili fan application development: [cnzxo](https://github.com/cnzxo/)
* Anniversary and heartbeat application development: [WoodwindHu](https://github.com/WoodwindHu)
* PC resource monitoring application development: [Jumping99](https://github.com/Jumping99)
* Multi-functional animation application development: [LHYHHD](https://github.com/LHYHHD)
* Developers are continuously joining...

_**Welcome to join the AIO internal test QQ discussion group**_

* Group 1 number: `755143193`
* Group 2 number: `860112883`
* Group 3 number: `676732387`
* Group 4 number: `749207817`
* Group 5 number: `866784418`

![QQ_Group](https://gitee.com/ClimbSnailQ/Project_Image/raw/master/OtherProject/holocubic_qq_group.jpg)

### Main Features
1. Aggregates various apps, including weather, clock, photo album, special effects animation, video playback, computer screen projection, web settings, etc. (Refer to the manual for specific usage of each app)
2. The system starts and the screen displays normally regardless of whether the TF card is inserted, whether the MPU6050 is soldered correctly, or whether it is connected to WiFi (must be 2.4G WiFi).
3. The program is relatively modular and low-coupling.
4. Provides a web interface for network configuration and other settings. Note: Refer to `APP Introduction` for specific operations.
5. The web interface supports both IP access and direct domain name access http://holocubic (some browsers may not support it well).
6. Provides file upload to the SD card via the web interface (including deletion), no need to remove the SD card to update pictures.
7. Provides a complete set of upper computer software and open-source upper computer source code. https://github.com/ClimbSnail/HoloCubic_AIO_Tool

### This firmware is designed with a low-coupling framework, which is more conducive to the realization of multiple functions
Bilibili function operation demonstration video link: https://www.bilibili.com/video/BV1wS4y1R7YF/

![HomePage](Image/holocubic_main.jpg)

![HomePage](Image/holocubic_home.png)

![UploadPage](Image/holocubic_upload.png)

![SettingPage](Image/holocubic_setting.png)


### Firmware Flashing Tool (No need to set up any IDE environment)
Download the upper computer in the group to flash the firmware.
1. `bootloader_dio_40m.bin` bootloader.
2. `partitions.bin` partition file
3. `boot_app0.bin`
4. The latest firmware `HoloCubic_AIO_XXX.bin`

The `HoloCubic_AIO_XXX.bin` file is updated with each version update, while the other three files basically remain unchanged.

Place the above three files and `CubicAIO_Tool.exe` in the same directory, double-click to run `CubicAIO_Tool.exe`, select the latest firmware `HoloCubic_AIO_XXX.bin` in the software, and you can flash the firmware.

Upper computer operation demonstration video link: https://b23.tv/5e6uDh

The upper computer, like the AIO firmware, adheres to open source. Open source address: https://github.com/ClimbSnail/HoloCubic_AIO_Tool

![AIO_TOOL](Image/holocubic_aio_tool.png)

![AIO_TOOL](https://gitee.com/ClimbSnailQ/Project_Image/raw/master/OtherProject/holocubic_aio_tool.png)

### Boot Precautions
Since the small TV uses the MPU6050 gyroscope accelerometer, it needs to be placed naturally (not held by hand) for the first 3 seconds after power-on to wait for the sensor to initialize. After the initialization is complete, the RGB light will be fully lit, and then normal operation can be performed. Whether or not the memory card is inserted does not affect normal booting. If the 6050 is soldered incorrectly, the attitude reading will be confused after initialization (phenomenon: the application will keep switching).

### Function Switching Instructions:
1. The file system of the TF card is fat32. TF is not a necessary hardware, but functions such as photo albums and video playback depend on it. If you plan to use a memory card, it is best to place all the files and folders in the `place to memory card` directory of this project in the root directory of the TF card before using the memory card.
2. Whether or not the TF memory card is inserted does not affect booting, but it affects the functions of certain apps (explained in each app introduction).
3. Shake left and right for `0.5s` to switch and select various apps.
4. Tilt forward for `1s` to enter the current page's app, and more functions will be integrated in the future. Similarly, tilt backward for 1s to exit the app.

### APP Introduction

##### Web Configuration Service (Web Server)
1. Operating conditions: None. Note: WiFi and other information are stored in flash, and the memory card does not affect the connection of WiFi functions.
2. After enabling, it will display `Web Server Start`. The small TV starts AP mode, established on `AP_IP` (marked on the screen's service interface), and the AP mode hotspot name is `HoloCubic_AIO` with no password.
3. When starting to use, the computer should be in the same network environment (same subnet) as `HoloCubic`. If WiFi has not been connected before, use the computer to connect to the hotspot name `HoloCubic_AIO` with no password released by HoloCubic.
4. Enter `Local_IP` or `AP_IP` ( http://192.168.4.2 also supports direct domain name access http://holocubic ) in the browser address bar to enter the management settings background. It is recommended to use `IP address` to access.
5. The webpage can set system parameters, weather app parameters, photo album parameters, player parameters, etc.
6. Due to the large number of current apps, switching and searching are cumbersome. You can also configure `auto-start app` in the `Web Server`.

##### File Manager
Function: Manage files on the memory card through a wireless network.

1. Running APP conditions: WiFi must be configured normally. The memory card must be inserted. To avoid insufficient power during WiFi connection causing a restart, ensure sufficient USB port power supply. Some functions are still under development.
2. After entering the `Holocubic` file manager, it will automatically connect to the configured WiFi and display the IP address.
3. Incomplete: Enter the IP address of your `Holocubic` in the file manager software of the upper computer (the port can be left unchanged) and click connect.

Note: The file manager temporarily uses `Windows Explorer`. Enter ftp://holocubic:aio@192.168.123.241 in the address bar (192.168.123.241 is the IP address displayed on my small TV. If prompted to enable access, enable it).

##### Photo Album (Picture)
1. Running APP conditions: The memory card must be inserted, and the root directory of the memory card must contain the `image/` directory (you can also use the `Web Server service` app to upload photos through the browser). The `image/` directory must contain image files (jpg or bin).
2. Convert the images to be played into a certain format (.jpg or .bin) and save them in the `image/` directory. The image file name must be in English characters or numbers (but cannot start with a number).
3. After entering the photo album app with the firmware, it will read the image files in the `image/` directory.
4. The `WebServer` webpage can set additional functions.

About image conversion: Use the attached upper computer for conversion (resolution is arbitrary, the software will automatically compress to the specified resolution).
* Common weather images are converted to C arrays in Indexed 16 colors format.
* Uncommon images can be converted to (True color with alpha, choose Binary RGB565) bin files and stored on the SD card, saving some program storage space for adding functions. Supports conversion to jpg images.

##### Video Playback (Media)
1. Running APP conditions: The memory card must be inserted, and the root directory of the memory card must contain the `movie/` directory.
2. Convert the videos to be played (preferably with an aspect ratio of 1:1) using the conversion tool provided with this firmware to the target file (mjpeg or rgb format) and store them in the `movie/` directory. The video file name must be in English characters or numbers (but cannot start with a number).
3. After running the player app, it will read the video files in the `movie/` directory.
4. Under default power, it enters low power mode after 90s of no action and enters secondary low power mode after 120s, with the specific performance being a decrease in playback frame rate.
5. The `WebServer` webpage can set additional functions.

##### Screen Share, Computer Screen Projection (Screen share)
1. Running APP conditions: No memory card is needed, but the WiFi password needs to be set using the `Web Server service` app (ensure it can connect to the router). To avoid insufficient power during WiFi connection causing a restart, ensure sufficient USB port power supply.
2. The upper computer currently uses third-party software, and an independent screen projection upper computer will be developed later to improve performance.
3. This screen projection upper computer uses the upper computer of [Superddg](https://gitee.com/superddg123/esp32-TFT/tree/master). If the screen is stuck, you can lower the image quality to improve the frame rate.
4. The `WebServer` webpage can set additional functions.

##### Weather, Clock (Weather)
There are two weather clock apps
###### New weather
1. The new version is designed by `PuYuuu` imitating the `misaka` clock interface. It uses the Gaode Weather API.
2. Running APP conditions: Must be in a connected state.
3. To use the new weather clock, modify the `city name (accurate city code)` and `API personal key` in the "Web Server" webpage service. (Reference code table for city codes: https://lbs.amap.com/api/webservice/download, method to obtain the key: https://lbs.amap.com/api/webservice/create-project-and-key)
###### Old weather
1. The old version UI design imitates [CWEIB](https://github.com/CWEIB)
2. Running APP conditions: Must be in a connected state and set the location and weather_key. In most cases, it can work normally without inserting a memory card.
3. Generally, it can work without a memory card, but some weather icons are stored in the memory card (due to insufficient internal flash). Copy the `weather/` folder provided with the firmware to the root directory of the TF card.
4. To use the old weather clock, modify the `Xinzhi Weather city name` and `key (private key)` in the "Web Server" webpage service. (Application address: https://seniverse.com. The program uses the v3 version of the API by default)

Note: Even if disconnected from the network, the clock still runs. (It is best to connect to WiFi when booting, as it will automatically synchronize the clock. It will intermittently try to synchronize the clock during use)

##### Special Effects Animation (Idea)
1. Running APP conditions: None. Built-in several special effects animations.

Note: The function was ported from the group member "Xiaofeixia". Thanks!

##### 2048 APP
1. The `2048` game was written by the group member `AndyXFuture` and agreed to be integrated into the AIO firmware by `ClimbSnail`. The original project link is `https://github.com/AndyXFuture/HoloCubic-2048-anim`
2. Running APP conditions: None. As long as the screen can light up.
3. Operation note: In the game, the `up` and `down` operations are the same actions as the original `enter` and `exit`. The system distinguishes actions by operation duration. In the game, `up` and `down` operate normally, while `enter` and `exit` require tilting for 1 second to trigger.

##### BiliBili APP
1. Running APP conditions: The memory card must contain a folder named `bilibili`. WiFi must be configured normally. To avoid insufficient power during WiFi connection causing a restart, ensure sufficient USB port power supply.
2. `UID` viewing method: Open Bilibili on the computer browser and log in to the account. Then open a blank page in the browser and paste this URL https://space.bilibili.com/ and press Enter. A string of pure numbers will automatically appear at the end of the URL, which is the UID.
3. Before using it for the first time, fill in the `UID` code on the `WebServer App` webpage.
4. Add a `avatar.bin` image of your Bilibili avatar with a resolution of `100*100` to the `bilibili` folder on the memory card (you can use the AIO upper computer to convert it).

Note: The program was written by `cnzxo`.

##### Anniversary
1. Running APP conditions: Connected state
2. Before using it for the first time, fill in the anniversary name and date on the `WebServer App` webpage. Currently, two anniversaries can be set. The supported characters for the anniversary name are `birthday, graduation, raising a small dinosaur, planting potatoes, wife, girlfriend, parents, grandparents, siblings, marriage anniversary`. If the anniversary name contains characters not in this range, please generate the font file yourself and replace the `src\app\anniversary\msyhbd_24.c` file. The date format is `2022.5.8`. If the year is set to 0, it is considered an annual anniversary (such as a birthday).

Note: The anniversary and heartbeat are reproduced from the [LizCubic](https://github.com/qingehao/LizCubic) project. The program was written by `WoodwindHu`.

##### Heartbeat
1. Running APP conditions: Connected state (performance mode needs to be enabled), an open MQTT server with port 1883, and two HoloCubics.
2. Before using it for the first time, fill in the configuration on the `WebServer App` webpage. The role can be 0 or 1, representing the two interacting HoloCubics. The client_id is the unique identifier of the device. Here, set these two HoloCubics to the same QQ number. Fill in the address of your MQTT server in mqtt_server, and fill in the port number. The username and password depend on the specific server configuration.
3. After setting the heartbeat app, it will automatically connect to the network and enable the MQTT client. After receiving a message from another HoloCubic, it will automatically enter the app. Entering the app normally will automatically send a message to another HoloCubic.
4. The group occasionally updates free services. For specific configuration parameters, ask the admin or group members.

Note: The anniversary and heartbeat are reproduced from the [LizCubic](https://github.com/qingehao/LizCubic) project. The program was written by `WoodwindHu`.

##### Stock Market Real-time Viewing (Stock)
1. Running APP conditions: WiFi must be configured normally. To avoid insufficient power during WiFi connection causing a restart, ensure sufficient USB port power supply.
2. Before using it for the first time, modify the `stock code` you want on the `WebServer App` webpage.

Note: The program was written by `redwolf`.

##### PC Resource Monitoring (PC Resource)
1. Running conditions: WiFi must be configured normally. The PC and HoloCubic must be in the same subnet. Set the PC's service IP address in the `WebServer APP` (refer to the tutorial for details).
2. Download [AIDA64](https://www.aida64.com/downloads), install AIDA64 on the PC, and import the configuration file `aida64_setting.rslcd` (located in the `AIO_Firmware_PIO\src\app\pc_resource` directory or in the group files).

Note: The specific operation steps are long, see the group document. This app was developed by `Jumping99`.

##### Multi-functional Animation (LH&LXW)

Download the firmware with the LH&LXW app for the transparent small TV, enter the system, select the LH&LXW app, tilt backward to enter the app, tilt forward to exit the app, and tilt left/right to select different functions, tilt backward to enter the selected function.

【Function Description】

Function 1: Code Rain; after entering this function - tilt left/right to switch the size of the code rain, tilt forward to exit this function.

Function 2: Cyber Photo Album; after entering this function - tilt left to stop automatic switching, tilt right to resume automatic switching, tilt backward to switch between static and dynamic, tilt forward to exit this function.

Before entering this function, ensure that your memory card contains the following files
```
1. ./LH&LXW/cyber/imgx.cyber stores the images to be displayed (x is 0~99)
2. ./LH&LXW/cyber/cyber_num.txt stores the number of images to be displayed (00~99). For example, if there are 7 images, write 07
Note: The number of images in ./LH&LXW/cyber/imgx.cyber must be equal to the number of image files entered by the user in ./LH&LXW/cyber/cyber_num.txt
```
The .cyber format image files are generated by the following python code:
```python
import cv2
img_path = './123.jpg' # Input image path (image size must be 48x40)
out_path = './123.cyber' # Output file path
img = cv2.imread(img_path)
img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
with open(out_path, 'wb') as f:
    for a in img:
        for b in a:
            f.write(b)
```

Function 3: QQ Super Emoji; after entering this function - tilt left/right to select different emojis, tilt backward to play the current emoji, tilt forward to exit playback during playback, and tilt forward to exit this function when selecting emojis. During playback, it automatically loops for 33.3 seconds and then plays the next one. During playback, you can manually switch by tilting left/right.

Before entering this function, ensure that your memory card contains the following files
```
1. ./LH&LXW/emoji/videos/videox.mjpeg stores the videos to be played (size 240x240) (x is 0~99)
2. ./LH&LXW/emoji/images/imagex.bin stores the covers of the videos to be played (size 60x60) (x is 0~99)
3. ./LH&LXW/emoji/emoji_num.txt stores the number of videos to be played (00~99). For example, if there are 7 videos, write 07

Note: The number of videos in ./LH&LXW/emoji/videos/ must be equal to the number of covers in ./LH&LXW/emoji/images/ and must be equal to the number of videos entered by the user in ./LH&LXW/emoji/emoji_num.txt.
```
Function 4: Eyeball; after entering this function - tilt left/right to switch eye styles, tilt forward to exit this function.

Function 5: Dynamic Heart; after entering this function - shake the small TV, and the particles forming the ♥ will also shake. After stopping shaking, the particles will gather into the shape of ♥ again, tilt forward to exit this function.

APP demonstration video: [LVGL Menu #Transparent Small TV#LVGL Development] https://www.bilibili.com/video/BV1wK421173C/?share_source=copy_web&vd_source=68337adbea96c8cef50403a4b2809df6


### About Compiling Project Code
1. This project code is developed based on the ESP32-Pico Arduino platform in the PlatformIO plugin on vscode. You can find specific tutorials on `Bilibili`. Recommended tutorial: [https://b23.tv/kibhGD](https://b23.tv/kibhGD)
2. Remember to modify the `upload_port` field in the `platformio.ini` file under the project to the corresponding COMM port.
3. If you want to shield some built-in files, modify the corresponding `APP macro` in `AIO_Firmware_PIO\src\app\app_conf.h` to `0` to shield them.
4. The latest version no longer requires you to modify the SPI pin in the SPI library. The `lib` directory of this project contains an SPI library with the SPI pin already modified. The following is the operation of the previous version (can be ignored)

~~Then you need to modify an official library file to use it normally (otherwise it will cause the memory card to fail to read):
Both PlatformIO and ArduinoIDE users need to install the ESP32 Arduino firmware support package (there are many tutorials on Baidu). Regardless of the development method, you need to modify the default MISO pin in the `SPI` library to `26`. For example, the package path of arduinoIDE is `esp32\hardware\esp32\1.0.4\libraries\SPI\src\SPI.cpp` file, **modify the following code to change MISO to 26**:~~
```
    if(sck == -1 && miso == -1 && mosi == -1 && ss == -1) {
        _sck = (_spi_num == VSPI) ? SCK : 14;
        _miso = (_spi_num == VSPI) ? MISO : 12; // Change to 26
        _mosi = (_spi_num == VSPI) ? MOSI : 13;
        _ss = (_spi_num == VSPI) ? SS : 15;
```
~~This is because the screen and SD card are connected using two hardware SPIs, and the default MISO pin of HSPI is 12. In ESP32, 12 is used to set the flash level during power-on. Pulling it up before power-on will cause the chip to fail to start. Therefore, we replace the default pin with 26.~~

### Program Framework Diagram

![HoloCubic_AIO_Frame](Image/holocubic_AIO_Frame.png)

![HoloCubic_AIO_Frame](https://gitee.com/ClimbSnailQ/Project_Image/raw/master/OtherProject/holocubic_AIO_Frame.png)

AIO framework explanation link: https://www.bilibili.com/video/BV1jh411a7pV?p=4

For UI design, you can follow tools such as `Edgeline` and `gui-guider`.

PlatformIO simulator: https://github.com/lvgl/lv_platformio

Application icons (128*128): You can download vector icons from Alibaba: https://www.iconfont.cn/

Error location code during debugging: `xtensa-esp32-elf-addr2line -pfiaC -e firmware_name.elf Backtrace address information`

For learning about lvgl, refer to: `http://lvgl.100ask.org`, `http://lvgl.100ask.net`

Lvgl font generation can use: `LvglFontTool V0.4` placed in the Doc directory

Extract all Chinese characters in the c file: You can use the `Script/get_font.py` script in the project to extract. `python get_font.py path of the font.c file`

### Acknowledgements
* ESP32 memory distribution: https://blog.csdn.net/espressif/article/details/112956403
* Video playback: https://github.com/moononournation/RGB565_video
* FTP reference document: https://blog.csdn.net/zhubao124/article/details/81662775
* ESP32 Arduino running dual-core: https://www.yiboard.com/thread-1344-1-1.html
* Forced portal authentication: https://blog.csdn.net/xh870189248/article/details/102892766
* Thanks to the authors of the open-source libraries used in the `lib` directory

