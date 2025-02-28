#include "pc_resource_gui.h"

LV_FONT_DECLARE(lv_font_ibmplex_24);
LV_FONT_DECLARE(lv_font_ibmplex_18);
LV_FONT_DECLARE(lv_font_ibmplex_16);

#define MODULE_CPU 0
#define MODULE_GPU 1
#define MODULE_RAM 2
#define MODULE_EXT 3

// Extension component attribute update functions
static void extension_1_update(struct PC_Resource info);
static void extension_2_update(struct PC_Resource info);
static void extension_3_update(struct PC_Resource info);
static void extension_4_update(struct PC_Resource info);
static void extension_5_update(struct PC_Resource info);

// Components
static sensor_module smod[4] = {0};

// Various styles
static lv_style_t default_style;        // Default style
static lv_style_t grid_cont_style;      // Grid layout container style
static lv_style_t grid_cont_cell_style; // Grid layout container cell style
static lv_style_t arc_style;            // Arc tool style
static lv_style_t arc_label_style;      // Arc internal percentage label style
static lv_style_t m_label_style;        // Component label style
static lv_style_t buttom_label_style;   // Component bottom label style
static lv_style_t ext_label_style_1;    // Extension label style 1
static lv_style_t ext_label_style_2;    // Extension label style 2
static lv_style_t ext_label_style_3;    // Extension label style 3

// Interface layout container
static lv_obj_t *cont = NULL;

// Grid layout row cells
static lv_coord_t col_dsc[] = {114, 114, LV_GRID_TEMPLATE_LAST};

// Grid layout column cells
static lv_coord_t row_dsc[] = {114, 114, LV_GRID_TEMPLATE_LAST};

// Current active page
static lv_obj_t *scr = NULL;

// Currently supported interface components
static const char *module_name[4] = {"CPU", "GPU", "RAM", "EXT"};

// Default format text for component bottom labels
static const char *mb_fmt[4] = {"%d.%d℃", "%d.%d℃", "%dMB", NULL};

/**
 * @brief UI style display initialization
 */
void display_pc_resource_gui_init(void)
{
    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, lv_color_hex(0x000000)); // Background color black

    lv_style_init(&grid_cont_style);
    lv_style_set_bg_color(&grid_cont_style, lv_color_hex(0x000000)); // Background color black
    lv_style_set_pad_all(&grid_cont_style, 0);                       // Grid container padding width 0
    lv_style_set_outline_width(&grid_cont_style, 0);                 // Grid container outline width 0
    lv_style_set_border_width(&grid_cont_style, 0);                  // Grid container border width 0
    lv_style_set_pad_row(&grid_cont_style, 3);
    lv_style_set_pad_column(&grid_cont_style, 3);

    lv_style_init(&grid_cont_cell_style);
    lv_style_set_bg_color(&grid_cont_cell_style, lv_color_hex(0x000000));     // Background color black
    lv_style_set_border_color(&grid_cont_cell_style, lv_color_hex(0x00ffff)); // Border color
    lv_style_set_border_opa(&grid_cont_cell_style, LV_OPA_70);                // Border opacity
    lv_style_set_pad_all(&grid_cont_cell_style, 0);                           // Grid cell padding width 0
    lv_style_set_outline_width(&grid_cont_cell_style, 0);                     // Grid cell outline width 0

    lv_style_init(&arc_style);

    lv_style_init(&arc_label_style);
    lv_style_set_bg_color(&arc_label_style, lv_color_hex(0x000000));   // Background color black
    lv_style_set_text_font(&arc_label_style, &lv_font_ibmplex_24);     // Set font
    lv_style_set_text_opa(&arc_label_style, LV_OPA_90);                // Font opacity
    lv_style_set_text_color(&arc_label_style, lv_color_hex(0x00ffff)); // Font color

    lv_style_init(&m_label_style);
    lv_style_set_bg_color(&m_label_style, lv_color_hex(0x000000));   // Background color black
    lv_style_set_text_font(&m_label_style, &lv_font_ibmplex_18);     // Set font
    lv_style_set_text_opa(&m_label_style, LV_OPA_90);                // Font opacity
    lv_style_set_text_color(&m_label_style, lv_color_hex(0x00ffff)); // Font color

    lv_style_init(&buttom_label_style);
    lv_style_set_bg_color(&buttom_label_style, lv_color_hex(0x000000));   // Background color black
    lv_style_set_text_font(&buttom_label_style, &lv_font_ibmplex_16);     // Set font
    lv_style_set_text_opa(&buttom_label_style, LV_OPA_90);                // Font opacity
    lv_style_set_text_color(&buttom_label_style, lv_color_hex(0x00ff00)); // Font color

    lv_style_init(&ext_label_style_1);
    lv_style_set_bg_color(&ext_label_style_1, lv_color_hex(0x000000));   // Background color black
    lv_style_set_text_font(&ext_label_style_1, &lv_font_ibmplex_16);     // Set font
    lv_style_set_text_opa(&ext_label_style_1, LV_OPA_90);                // Font opacity
    lv_style_set_text_color(&ext_label_style_1, lv_color_hex(0xff00ff)); // Font color

    lv_style_init(&ext_label_style_2);
    lv_style_set_bg_color(&ext_label_style_2, lv_color_hex(0x000000));   // Background color black
    lv_style_set_text_font(&ext_label_style_2, &lv_font_ibmplex_16);     // Set font
    lv_style_set_text_opa(&ext_label_style_2, LV_OPA_90);                // Font opacity
    lv_style_set_text_color(&ext_label_style_2, lv_color_hex(0xffffff)); // Font color

    lv_style_init(&ext_label_style_3);
    lv_style_set_bg_color(&ext_label_style_3, lv_color_hex(0x000000));   // Background color black
    lv_style_set_text_font(&ext_label_style_3, &lv_font_ibmplex_16);     // Set font
    lv_style_set_text_opa(&ext_label_style_3, LV_OPA_90);                // Font opacity
    lv_style_set_text_color(&ext_label_style_3, lv_color_hex(0xff0000)); // Font color
}

/**
 * @brief UI interface display initialization
 */
void display_pc_resource_init(void)
{
    lv_obj_t *act_obj = lv_scr_act(); // Get the current active page
    if (act_obj == scr)
        return;

    pc_resource_gui_release();
    lv_obj_clean(act_obj); // Clear the previous page

    scr = lv_obj_create(NULL);
    lv_obj_add_style(scr, &default_style, LV_STATE_DEFAULT);

    // Create interface container
    cont = lv_obj_create(scr);
    lv_obj_add_style(cont, &grid_cont_style, LV_STATE_DEFAULT);
    lv_obj_set_size(cont, 240, 240);
    lv_obj_center(cont);
    lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);

    for (int i = 0; i < 4; i++)
    {
        uint8_t col = i % 2;
        uint8_t row = i / 2;

        lv_obj_t *cell = lv_obj_create(cont); // Create a cell
        lv_obj_add_style(cell, &grid_cont_cell_style, LV_STATE_DEFAULT);
        lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row, 1); // Row and column cell scaling ratio 1

        smod[i].name = module_name[i];
        if (strcmp(smod[i].name, "EXT")) // Non-extension component
        {
            // Create utilization arc
            lv_obj_t *arc = lv_arc_create(cell);
            lv_obj_set_size(arc, 80, 80);
            lv_obj_align(arc, LV_ALIGN_TOP_RIGHT, 0, 0);
            lv_obj_remove_style(arc, NULL, LV_PART_KNOB);  // Remove knob part style
            lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE); // Not clickable
            lv_arc_set_rotation(arc, 270);                 // Rotate 0 degrees to 12 o'clock position
            lv_arc_set_range(arc, 0, 100);                 // Set range 0~100
            lv_arc_set_bg_angles(arc, 0, 360);             // Arc 360°
            lv_arc_set_value(arc, 50);
            lv_obj_add_style(arc, &arc_style, LV_STATE_DEFAULT);

            // Create arc internal percentage label
            lv_obj_t *arc_label = lv_label_create(arc);
            lv_obj_add_style(arc_label, &arc_label_style, LV_STATE_DEFAULT); // Add style
            lv_label_set_text_fmt(arc_label, "%d", 50);
            lv_obj_center(arc_label); // Center align

            // Create component label
            lv_obj_t *m_label = lv_label_create(cell);
            lv_obj_set_width(m_label, 23);
            lv_obj_add_style(m_label, &m_label_style, LV_STATE_DEFAULT); // Add style
            lv_label_set_text_fmt(m_label, "%s", module_name[i]);
            lv_obj_align(m_label, LV_ALIGN_TOP_LEFT, 5, -5); // Set align

            // Create component bottom label
            lv_obj_t *b_label = lv_label_create(cell);
            lv_obj_add_style(b_label, &buttom_label_style, LV_STATE_DEFAULT); // Add style
            lv_label_set_text_fmt(b_label, mb_fmt[i], 35, 4);
            lv_obj_align(b_label, LV_ALIGN_BOTTOM_RIGHT, -5, -2); // Set align

            smod[i].usage_rate_arc = arc;
            smod[i].usage_rate_label = arc_label;
            smod[i].module_label = m_label;
            smod[i].buttom_label = b_label;
        }
        else // Extension component, only use the extension attributes of the component
        {
            // Create network upload speed label
            lv_obj_t *net_up_label = lv_label_create(cell);
            lv_obj_set_width(net_up_label, 114);                                  // Set label width for long text mode scrolling
            lv_label_set_long_mode(net_up_label, LV_LABEL_LONG_SCROLL);           // Long text mode
            lv_obj_add_style(net_up_label, &ext_label_style_1, LV_STATE_DEFAULT); // Add style
            lv_label_set_text_fmt(net_up_label, "\uf093%d.%dKB/s", 12346, 5);
            lv_obj_align(net_up_label, LV_ALIGN_TOP_LEFT, 0, 0); // Set align

            // Create network download speed label
            lv_obj_t *net_down_label = lv_label_create(cell);
            lv_obj_set_width(net_down_label, 114);                                  // Set label width for long text mode scrolling
            lv_label_set_long_mode(net_down_label, LV_LABEL_LONG_SCROLL);           // Long text mode
            lv_obj_add_style(net_down_label, &ext_label_style_1, LV_STATE_DEFAULT); // Add style
            lv_label_set_text_fmt(net_down_label, "\uf019%d.%dKB/s", 22441, 5);
            lv_obj_align_to(net_down_label, net_up_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0); // Set align

            // Create CPU clock label
            lv_obj_t *cpu_clock_label = lv_label_create(cell);
            lv_obj_set_width(cpu_clock_label, 114);                                  // Set label width for long text mode scrolling
            lv_label_set_long_mode(cpu_clock_label, LV_LABEL_LONG_SCROLL);           // Long text mode
            lv_obj_add_style(cpu_clock_label, &ext_label_style_2, LV_STATE_DEFAULT); // Add style
            lv_label_set_text_fmt(cpu_clock_label, "\uf2db%dMHz", 4211);
            lv_obj_align_to(cpu_clock_label, net_down_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0); // Set align

            // Create CPU power label
            lv_obj_t *cpu_power_label = lv_label_create(cell);
            lv_obj_set_width(cpu_power_label, 114);                                  // Set label width for long text mode scrolling
            lv_label_set_long_mode(cpu_power_label, LV_LABEL_LONG_SCROLL);           // Long text mode
            lv_obj_add_style(cpu_power_label, &ext_label_style_2, LV_STATE_DEFAULT); // Add style
            lv_label_set_text_fmt(cpu_power_label, "\uf2db%d.%dW", 21, 4);
            lv_obj_align_to(cpu_power_label, cpu_clock_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0); // Set align

            // Create GPU power label
            lv_obj_t *gpu_power_label = lv_label_create(cell);
            lv_obj_set_width(gpu_power_label, 114);                                  // Set label width for long text mode scrolling
            lv_label_set_long_mode(gpu_power_label, LV_LABEL_LONG_SCROLL);           // Long text mode
            lv_obj_add_style(gpu_power_label, &ext_label_style_3, LV_STATE_DEFAULT); // Add style
            lv_label_set_text_fmt(gpu_power_label, "\uf109%d.%dW", 124, 8);
            lv_obj_align_to(gpu_power_label, cpu_power_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, -2); // Set align

            smod[i].extension_label_1 = net_up_label;    // Extension attribute 1->net upload speed
            smod[i].extension_label_2 = net_down_label;  // Extension attribute 2->net download speed
            smod[i].extension_label_3 = cpu_clock_label; // Extension attribute 3->CPU clock
            smod[i].extension_label_4 = cpu_power_label; // Extension attribute 4->CPU power
            smod[i].extension_label_5 = gpu_power_label; // Extension attribute 5->GPU power

            // Set extension update functions
            smod[i].extension_update[0] = extension_1_update;
            smod[i].extension_update[1] = extension_2_update;
            smod[i].extension_update[2] = extension_3_update;
            smod[i].extension_update[3] = extension_4_update;
            smod[i].extension_update[4] = extension_5_update;
        }
    }
}

/**
 * @brief UI interface data update
 * @param sensorInfo Sensor data
 */
void display_pc_resource(struct PC_Resource sensorInfo)
{
    display_pc_resource_init();

    // Update CPU component
    lv_arc_set_value(smod[MODULE_CPU].usage_rate_arc, sensorInfo.cpu_usage); // CPU utilization
    lv_label_set_text_fmt(smod[MODULE_CPU].usage_rate_label, "%d", sensorInfo.cpu_usage);
    lv_label_set_text_fmt(smod[MODULE_CPU].buttom_label, mb_fmt[MODULE_CPU],
                          sensorInfo.cpu_temp / 10, sensorInfo.cpu_temp % 10); // CPU temperature

    // Update GPU component
    lv_arc_set_value(smod[MODULE_GPU].usage_rate_arc, sensorInfo.gpu_usage); // GPU utilization
    lv_label_set_text_fmt(smod[MODULE_GPU].usage_rate_label, "%d", sensorInfo.gpu_usage);
    lv_label_set_text_fmt(smod[MODULE_GPU].buttom_label, mb_fmt[MODULE_GPU],
                          sensorInfo.gpu_temp / 10, sensorInfo.gpu_temp % 10); // GPU temperature

    // Update RAM component
    lv_arc_set_value(smod[MODULE_RAM].usage_rate_arc, sensorInfo.ram_usage); // RAM utilization
    lv_label_set_text_fmt(smod[MODULE_RAM].usage_rate_label, "%d", sensorInfo.ram_usage);
    lv_label_set_text_fmt(smod[MODULE_RAM].buttom_label, mb_fmt[MODULE_RAM],
                          sensorInfo.ram_use); // RAM used amount

    // Update extension component
    for (int i = 0; i < MAX_EXTENSION_NUM; i++)
    {
        if (smod[MODULE_EXT].extension_update[i] != NULL)
            smod[MODULE_EXT].extension_update[i](sensorInfo);
    }

    lv_scr_load(scr);
}

/**
 * @brief UI interface object release
 */
void pc_resource_gui_release(void)
{
    if (scr != NULL)
    {
        lv_obj_clean(scr);

        scr = NULL;
        cont = NULL;
        memset(smod, 0, sizeof(smod));
    }
}

/**
 * @brief Extension object 1 data update function -> net upload speed
 * @param sensorInfo Sensor data
 */
static void extension_1_update(struct PC_Resource info)
{
    int num = info.net_upload_speed / 10;
    int mini_num = info.net_upload_speed % 10;

    lv_label_set_text_fmt(smod[MODULE_EXT].extension_label_1, "\uf093%d.%dKB/s", num, mini_num);
}

/**
 * @brief Extension object 2 data update function -> net download speed
 * @param sensorInfo Sensor data
 */
static void extension_2_update(struct PC_Resource info)
{
    int num = info.net_download_speed / 10;
    int mini_num = info.net_download_speed % 10;

    lv_label_set_text_fmt(smod[MODULE_EXT].extension_label_2, "\uf019%d.%dKB/s", num, mini_num);
}

/**
 * @brief Extension object 3 data update function -> CPU clock
 * @param sensorInfo Sensor data
 */
static void extension_3_update(struct PC_Resource info)
{
    lv_label_set_text_fmt(smod[MODULE_EXT].extension_label_3, "\uf2db%dMHz", info.cpu_freq);
}

/**
 * @brief Extension object 4 data update function -> CPU power
 * @param sensorInfo Sensor data
 */
static void extension_4_update(struct PC_Resource info)
{
    int num = info.cpu_power / 10;
    int mini_num = info.cpu_power % 10;

    lv_label_set_text_fmt(smod[MODULE_EXT].extension_label_4, "\uf2db%d.%dW", num, mini_num);
}

/**
 * @brief Extension object 5 data update function -> GPU power
 * @param sensorInfo Sensor data
 */
static void extension_5_update(struct PC_Resource info)
{
    int num = info.gpu_power / 10;
    int mini_num = info.gpu_power % 10;

    lv_label_set_text_fmt(smod[MODULE_EXT].extension_label_5, "\uf109%d.%dW", num, mini_num);
}
