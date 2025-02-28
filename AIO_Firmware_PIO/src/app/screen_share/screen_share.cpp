#include "screen_share.h"
#include "screen_share_gui.h"
#include "common.h"
#include <TJpg_Decoder.h>
#include "sys/app_controller.h"

#define SCREEN_SHARE_APP_NAME "Screen share"

#define JPEG_BUFFER_SIZE 1       // Store a jpeg image (240*240 10000 is roughly enough, normally a frame is about 3000)
#define RECV_BUFFER_SIZE 50000   // Theoretically twice the size of JPEG_BUFFER_SIZE is enough
#define DMA_BUFFER_SIZE 512      // (16*16*2)
#define SHARE_WIFI_ALIVE 20000UL // Maintain wifi heartbeat time (20s)

#define HTTP_PORT 8081 // Set listening port
WiFiServer ss_server;  // Server ss = screen_share
WiFiClient ss_client;  // Client ss = screen_share

// Persistent configuration for weather
#define SCREEN_SHARE_CONFIG_PATH "/screen_share.cfg"
struct SS_Config
{
    uint8_t powerFlag; // Power control (0 low heat 1 performance priority)
};

static void write_config(SS_Config *cfg)
{
    char tmp[16];
    // Save configuration data in a file (persistent)
    String w_data;
    memset(tmp, 0, 16);
    snprintf(tmp, 16, "%u\n", cfg->powerFlag);
    w_data += tmp;
    g_flashCfg.writeFile(SCREEN_SHARE_CONFIG_PATH, w_data.c_str());
}

static void read_config(SS_Config *cfg)
{
    // If persistent configuration files are needed, this function can be called to store data in flash
    // The configuration file name should preferably start with the APP name and end with ".cfg" to avoid confusion when multiple APPs read it
    char info[128] = {0};
    uint16_t size = g_flashCfg.readFile(SCREEN_SHARE_CONFIG_PATH, (uint8_t *)info);
    info[size] = 0;
    if (size == 0)
    {
        // Default value
        cfg->powerFlag = 0; // Power control (0 low heat 1 performance priority)
        write_config(cfg);
    }
    else
    {
        // Parse data
        char *param[1] = {0};
        analyseParam(info, 1, param);
        cfg->powerFlag = atol(param[0]);
    }
}

struct ScreenShareAppRunData
{
    // The amount of data is not large, and for the sake of data structure clarity, memory alignment is not performed here

    boolean tcp_start; // Flag whether to start the web server service, 0 for off 1 for on
    boolean req_sent;  // Flag whether to send wifi request service, 0 for off 1 for on

    uint8_t *recvBuf;              // Receive buffer
    uint8_t *mjpeg_start;          // Points to the beginning of a frame of mpjeg image
    uint8_t *mjpeg_end;            // Points to the end of a frame of mpjeg image
    uint8_t *last_find_pos;        // Last found position
    int32_t bufSaveTail;           // Points to the last data saved in recvBuf
    uint8_t *displayBufWithDma[2]; // Two buffers for FDMA
    bool dmaBufferSel;             // DMA buffer switch flag
    boolean tftSwapStatus;

    unsigned long pre_wifi_alive_millis; // Local timestamp of the last wifi heartbeat sent
};

static SS_Config cfg_data;
static ScreenShareAppRunData *run_data = NULL;

// This next function will be called during decoding of the jpeg file to render each
// 16x16 or 8x8 image tile (Minimum Coding Unit) to the tft->
bool screen_share_tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    // Stop further decoding as image is running off bottom of screen
    if (y >= tft->height())
        return 0;

    // STM32F767 processor takes 43ms just to decode (and not draw) jpeg (-Os compile option)
    // Total time to decode and also draw to TFT:
    // SPI 54MHz=71ms, with DMA 50ms, 71-43 = 28ms spent drawing, so DMA is complete before next MCU block is ready
    // Apparent performance benefit of DMA = 71/50 = 42%, 50 - 43 = 7ms lost elsewhere
    // SPI 27MHz=95ms, with DMA 52ms. 95-43 = 52ms spent drawing, so DMA is *just* complete before next MCU block is ready!
    // Apparent performance benefit of DMA = 95/52 = 83%, 52 - 43 = 9ms lost elsewhere

    // Double buffering is used, the bitmap is copied to the buffer by pushImageDMA() the
    // bitmap can then be updated by the jpeg decoder while DMA is in progress
    uint16_t *dmaBufferPtr;
    if (run_data->dmaBufferSel)
        dmaBufferPtr = (uint16_t *)run_data->displayBufWithDma[0];
    else
        dmaBufferPtr = (uint16_t *)run_data->displayBufWithDma[1];
    run_data->dmaBufferSel = !run_data->dmaBufferSel; // Toggle buffer selection
    //  pushImageDMA() will clip the image block at screen boundaries before initiating DMA
    tft->pushImageDMA(x, y, w, h, bitmap, dmaBufferPtr); // Initiate DMA - blocking only if last DMA is not complete
                                                         // The DMA transfer of image block to the TFT is now in progress...

    // Return 1 to decode next block.
    return true;
}

static bool readJpegFromBuffer(uint8_t *const end)
{
    // Default read data from run_data->recvBuf
    // The address of the current last data marked by end
    bool isFound = false;                     // Flag whether a complete mjpeg image data is found
    uint8_t *pfind = run_data->last_find_pos; // Pointer to start searching
    if (NULL == run_data->mjpeg_start)
    {
        // Execute when frame header is not found
        while (pfind < end)
        {
            if (*pfind == 0xFF && *(pfind + 1) == 0xD8)
            {
                run_data->mjpeg_start = pfind; // Frame header
                break;
            }
            ++pfind;
        }
        run_data->last_find_pos = pfind;
    }
    else if (NULL == run_data->mjpeg_end)
    {
        // Find frame tail
        while (pfind < end)
        {
            if (*pfind == 0xFF && *(pfind + 1) == 0xD9)
            {
                run_data->mjpeg_end = pfind + 1; // Frame tail, marked as the last 0xD9
                isFound = true;
                break;
            }
            ++pfind;
        }
        run_data->last_find_pos = pfind;
    }
    return isFound;
}

static int screen_share_init(AppController *sys)
{
    // Get configuration information
    read_config(&cfg_data);

    if (0 == cfg_data.powerFlag)
    {
        // Set CPU frequency
        setCpuFrequencyMhz(160);
    }
    else
    {
        setCpuFrequencyMhz(240);
    }

    // Adjust RGB mode HSV color mode
    RgbParam rgb_setting = {LED_MODE_HSV, 0, 128, 32,
                            255, 255, 32,
                            1, 1, 1,
                            150, 250, 1, 30};
    set_rgb_and_run(&rgb_setting);

    screen_share_gui_init();
    // Initialize runtime parameters
    run_data = (ScreenShareAppRunData *)calloc(1, sizeof(ScreenShareAppRunData));
    run_data->tcp_start = 0;
    run_data->req_sent = 0;
    run_data->recvBuf = (uint8_t *)malloc(RECV_BUFFER_SIZE);
    run_data->mjpeg_start = NULL;
    run_data->mjpeg_end = NULL;
    run_data->last_find_pos = run_data->recvBuf;
    run_data->bufSaveTail = 0;
    run_data->displayBufWithDma[0] = (uint8_t *)heap_caps_malloc(DMA_BUFFER_SIZE, MALLOC_CAP_DMA);
    run_data->displayBufWithDma[1] = (uint8_t *)heap_caps_malloc(DMA_BUFFER_SIZE, MALLOC_CAP_DMA);
    run_data->dmaBufferSel = false;
    run_data->pre_wifi_alive_millis = 0;

    tft->initDMA();

    // The decoder must be given the exact name of the rendering function above
    SketchCallback callback = (SketchCallback)&screen_share_tft_output; // Force cast func() type
    TJpgDec.setCallback(callback);
    // The jpeg image can be scaled down by a factor of 1, 2, 4, or 8
    TJpgDec.setJpgScale(1);

    run_data->tftSwapStatus = tft->getSwapBytes();
    tft->setSwapBytes(true);
    // Because in other apps it is directly set to tft, so try not to use TJpgDec's setSwapBytes here
    // TJpgDec.setSwapBytes(true);

    Serial.print(F("To prevent overheating, it is currently limited to medium speed!\n"));
    return 0;
}

static void stop_share_config()
{
    run_data->tcp_start = 0;
    run_data->req_sent = 0;
    // Close server
    ss_server.stop();
    ss_server.close();
}

static void screen_share_process(AppController *sys,
                                 const ImuAction *action)
{
    lv_scr_load_anim_t anim_type = LV_SCR_LOAD_ANIM_NONE;

    if (RETURN == action->active)
    {
        sys->app_exit();
        return;
    }

    if (0 == run_data->tcp_start && 0 == run_data->req_sent)
    {
        // Pre-display
        display_screen_share(
            "Screen Share",
            WiFi.softAPIP().toString().c_str(),
            "8081",
            "Wait connect ....",
            LV_SCR_LOAD_ANIM_NONE);
        // If the web service is not turned on and the ap request is not sent, the message here has no effect (fill in NULL)
        // sys->send_to(SCREEN_SHARE_APP_NAME, CTRL_NAME,
        //              APP_MESSAGE_WIFI_AP, NULL, NULL);
        // Use STA mode
        sys->send_to(SCREEN_SHARE_APP_NAME, CTRL_NAME,
                     APP_MESSAGE_WIFI_CONN, NULL, NULL);
        run_data->req_sent = 1; // Mark as ap request sent
    }
    else if (1 == run_data->tcp_start)
    {
        if (doDelayMillisTime(SHARE_WIFI_ALIVE, &run_data->pre_wifi_alive_millis, false))
        {
            // Send wifi heartbeat
            sys->send_to(SCREEN_SHARE_APP_NAME, CTRL_NAME,
                         APP_MESSAGE_WIFI_ALIVE, NULL, NULL);
        }

        if (ss_client.connected())
        {
            // If the client is connected client.connected()
            if (ss_client.available())
            {
                ss_client.write("no");                                                                 // Send the current frame not written instruction to the host computer
                int32_t read_count = ss_client.read(&run_data->recvBuf[run_data->bufSaveTail], 10000); // Read data to buffer
                run_data->bufSaveTail += read_count;

                unsigned long deal_time = GET_SYS_MILLIS();
                bool get_mjpeg_ret = readJpegFromBuffer(run_data->recvBuf + run_data->bufSaveTail);

                if (true == get_mjpeg_ret)
                {
                    ss_client.write("ok"); // Send the next frame send instruction to the host computer
                    tft->startWrite();     // Must use startWrite first to keep the TFT chip select low and the DMA and SPI channel settings remain configured
                    uint32_t frame_size = run_data->mjpeg_end - run_data->mjpeg_start + 1;
                    // Draw the image at 0,0 in the upper left corner - in this sketch, DMA requests are handled in the callback tft_output()
                    JRESULT jpg_ret = TJpgDec.drawJpg(0, 0, run_data->mjpeg_start, frame_size);
                    tft->endWrite(); // Must use endWrite to release the TFT chip select and release the SPI channel
                    // Remaining frame size
                    uint32_t left_frame_size = &run_data->recvBuf[run_data->bufSaveTail] - run_data->mjpeg_end;
                    memcpy(run_data->recvBuf, run_data->mjpeg_end + 1, left_frame_size);
                    Serial.printf("Frame size: %d ", frame_size);
                    Serial.print("MCU processing speed: ");
                    Serial.print(1000.0 / (GET_SYS_MILLIS() - deal_time), 2);
                    Serial.print("Fps\n");

                    run_data->last_find_pos = run_data->recvBuf;
                    run_data->bufSaveTail = 0;
                    // Data reset
                    run_data->mjpeg_start = NULL;
                    run_data->mjpeg_end = NULL;
                }
                else if (run_data->bufSaveTail > RECV_BUFFER_SIZE)
                {
                    run_data->last_find_pos = run_data->recvBuf;
                    run_data->bufSaveTail = 0;
                    // Data reset
                    run_data->mjpeg_start = NULL;
                    run_data->mjpeg_end = NULL;
                    ss_client.write("ok"); // Send the next frame send instruction to the host computer
                }
            }
        }
        else
        {
            // Establish client
            ss_client = ss_server.available();
            if (ss_client.connected())
            {
                Serial.println(F("Controller was connected!"));
                ss_client.write("ok"); // Send the next frame send instruction to the host computer
            }

            // Pre-display
            display_screen_share(
                "Screen Share",
                WiFi.localIP().toString().c_str(),
                "8081",
                "Wait connect ....",
                LV_SCR_LOAD_ANIM_NONE);

            unsigned long timeout = GET_SYS_MILLIS();
            while (ss_client.available() == 0)
            {
                if (GET_SYS_MILLIS() - timeout > 2000)
                {
                    Serial.print(F("Controller was disconnect!"));
                    Serial.println(F(" >>> Client Timeout !"));
                    ss_client.stop();
                    return;
                }
            }
        }
    }
}

static void screen_background_task(AppController *sys,
                                   const ImuAction *act_info)
{
    // This function is a background task, the main controller will call this function every minute
    // This function should try to call "resident data" only, other variables may have been released due to lifecycle reasons
}

static int screen_exit_callback(void *param)
{
    stop_share_config();
    screen_share_gui_del();
    if (NULL != run_data->recvBuf)
    {
        free(run_data->recvBuf);
        run_data->recvBuf = NULL;
    }

    if (NULL != run_data->displayBufWithDma[0])
    {
        free(run_data->displayBufWithDma[0]);
        run_data->displayBufWithDma[0] = NULL;
    }
    if (NULL != run_data->displayBufWithDma[1])
    {
        free(run_data->displayBufWithDma[1]);
        run_data->displayBufWithDma[1] = NULL;
    }

    // Restore previous driver parameters
    tft->setSwapBytes(run_data->tftSwapStatus);

    // Restore RGB light HSV color mode
    RgbParam rgb_setting = {LED_MODE_HSV,
                            1, 32, 255,
                            255, 255, 255,
                            1, 1, 1,
                            150, 250, 1, 30};
    set_rgb_and_run(&rgb_setting);

    // Release runtime data
    if (NULL != run_data)
    {
        free(run_data);
        run_data = NULL;
    }
    return 0;
}

static void screen_message_handle(const char *from, const char *to,
                                  APP_MESSAGE_TYPE type, void *message,
                                  void *ext_info)
{
    switch (type)
    {
    case APP_MESSAGE_WIFI_CONN:
    {
        Serial.print(F("APP_MESSAGE_WIFI_CONN enable\n"));
        display_screen_share(
            "Screen Share",
            WiFi.localIP().toString().c_str(),
            "8081",
            "Connect succ",
            LV_SCR_LOAD_ANIM_NONE);
        run_data->tcp_start = 1;
        ss_server.begin(HTTP_PORT); // Server starts listening on port number
        ss_server.setNoDelay(true);
    }
    break;
    case APP_MESSAGE_WIFI_AP:
    {
        Serial.print(F("APP_MESSAGE_WIFI_AP enable\n"));
        display_screen_share(
            "Screen Share",
            WiFi.softAPIP().toString().c_str(),
            "8081",
            "Connect succ",
            LV_SCR_LOAD_ANIM_NONE);
        run_data->tcp_start = 1;
        // ss_server.begin(HTTP_PORT); // Server starts listening on port number
        // ss_server.setNoDelay(true);
    }
    break;
    case APP_MESSAGE_WIFI_ALIVE:
    {
        // Response to wifi heartbeat maintenance can do nothing
    }
    break;
    case APP_MESSAGE_GET_PARAM:
    {
        char *param_key = (char *)message;
        if (!strcmp(param_key, "powerFlag"))
        {
            snprintf((char *)ext_info, 32, "%u", cfg_data.powerFlag);
        }
        else
        {
            snprintf((char *)ext_info, 32, "%s", "NULL");
        }
    }
    break;
    case APP_MESSAGE_SET_PARAM:
    {
        char *param_key = (char *)message;
        char *param_val = (char *)ext_info;
        if (!strcmp(param_key, "powerFlag"))
        {
            cfg_data.powerFlag = atol(param_val);
        }
    }
    break;
    case APP_MESSAGE_READ_CFG:
    {
        read_config(&cfg_data);
    }
    break;
    case APP_MESSAGE_WRITE_CFG:
    {
        write_config(&cfg_data);
    }
    break;
    default:
        break;
    }
}

APP_OBJ screen_share_app = {SCREEN_SHARE_APP_NAME, &app_screen, "",
                            screen_share_init, screen_share_process, screen_background_task,
                            screen_exit_callback, screen_message_handle};
