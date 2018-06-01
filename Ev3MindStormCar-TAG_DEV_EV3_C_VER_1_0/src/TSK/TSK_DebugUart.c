/**
 *  URT_Debug.c
 *
 *  Send message to UART port for debug
 */
#include "ev3api.h"
#include <stdarg.h>
#include <syssvc/serial.h>
#include "CLC_MotorOutput.h"

#define DEBUG_DISPLAY_LCD
//#define DEBUG_DISPLAY_UART
#if defined(DEBUG_DISPLAY_LCD)
#if defined(DEBUG_DISPLAY_UART)
#error "Both DEBUG_DISPLAY_LCD and DEBUG_DISPLAY_UART are define."
#endif  //defined(DEBUG_DISPLAY_UART)
#endif  //defined(DEBUG_DISPLAY_LCD)
#if !defined(DEBUG_DISPLAY_LCD)
#if !defined(DEBUG_DISPLAY_UART)
#error "DEBUG_DISPLAY_LCD or DEBUG_DISPLAY_UART must be defined."
#endif  //!defined(DEBUG_DISPLAY_UART)
#endif  //!defined(DEBUG_DISPLAY_LCD)

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern int cur_mode;
extern int bt_task_count;
extern int cmd_hdl_count;
extern int mode_task_count;
extern int safe_task_count;
extern int motor_task_count;
extern uint8_t cmd_target_motor_output;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int debug_config = -1;
int debug_task_count = 0;
FILE *debug_file = NULL;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/
static int32_t font_size_width;
static int32_t font_size_height;
static int32_t char_num;
static int32_t line_num;
#define MSG_BUF_SIZE    (64)
static char msg_buf[MSG_BUF_SIZE];

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
//関数宣言
void debug_write_msg(const char *msg, int line_index);

/**
 *  @brief  Initialize debug configuration.
 */
void init_debug_uart(void) {
    ER ret;
    lcdfont_t font_size = EV3_FONT_SMALL;
    
    ev3_lcd_set_font(font_size);
    
    ret = ev3_font_get_size(font_size,
        &font_size_width,
        &font_size_height);
    if (E_OK == ret) {
        debug_config = 0;

        char_num = EV3_LCD_WIDTH / font_size_width;
        line_num = EV3_LCD_HEIGHT / font_size_height;
    } else if (E_ID == ret) {
        debug_config = 1;
    } else {
        debug_config = 2;
    }
}


/**
 *  @brief  Initialize buffer pointed by argument.
 *          The buffer is filled by '\0'.
 *
 *  @param[in,out]  buf     Pointer to buffer to initialize.
 *  @param          buf_len Size of buffer to initialize.
 */
static void reset_buf(char *buf, int buf_len) {
    int idx;
    
    for (idx = 0; idx < buf_len; idx++) {
        *buf = (char)0;
        buf++;
    }
}

/**
 *  @brief  Debug function.
 *          Display debug data on LCD, EV3.
 */
void debug_device_info(void) {
    int32_t line_pos_x = 0;

    reset_buf((char *)&msg_buf[0], MSG_BUF_SIZE);

    sprintf((char *)&msg_buf[0], "APP_MOD:%d", cur_mode);
    debug_write_msg((char *)&msg_buf[0], line_pos_x);
    line_pos_x++;

    sprintf((char *)&msg_buf[0], "BLT_TSK_CNT:%5d", bt_task_count);
    debug_write_msg((char *)&msg_buf[0], line_pos_x);
    line_pos_x++;

    sprintf((char *)&msg_buf[0], "CMD_HDL_CNT:%5d", cmd_hdl_count);
    debug_write_msg((char *)&msg_buf[0], line_pos_x);
    line_pos_x++;

    sprintf((char *)&msg_buf[0], "MOD_TSK_CNT:%5d", mode_task_count);
    debug_write_msg((char *)&msg_buf[0], line_pos_x);
    line_pos_x++;

    sprintf((char *)&msg_buf[0], "SAF_TSK_CNT:%5d", safe_task_count);
    debug_write_msg((char *)&msg_buf[0], line_pos_x);
    line_pos_x++;

    sprintf((char *)&msg_buf[0], "MTR_TSK_CNT:%5d", motor_task_count);
    debug_write_msg((char *)&msg_buf[0], line_pos_x);
    line_pos_x++;

    sprintf((char *)&msg_buf[0], "MTR_TRG_PWR:%5d", cmd_target_motor_output);
    debug_write_msg((char *)&msg_buf[0], line_pos_x);
    line_pos_x++;
}

/**
 *  @brief  Commonly used function.
 *          Display message for debug on LCD.
 *
 *  @param[in,out]  msg Pointer to message to display.
 *  @param          line_index  The row number of message.
 */
void debug_write_msg(const char *msg, int line_index) {
    int32_t line_pos_x = 0;

    //基本的に引数にNULLが指定されることはないが、念のために確認する。
    if (NULL != msg) {
        line_pos_x = font_size_height * ((int32_t)line_index);
        
        ev3_lcd_draw_string((char *)msg, 0, line_pos_x);
    }
}

/**
 *  @brief  Clear debug message.
 */
void debug_clear(void) {
    int line_index;
    int char_index;

    reset_buf((char *)&msg_buf[0], MSG_BUF_SIZE);

    for (char_index = 0; char_index < char_num; char_index++) {
        msg_buf[char_index] = ' ';
    }

    for (line_index = 0; line_index < line_num; line_index++) {
        debug_write_msg((char *)&msg_buf[0], line_index);
    }
}
