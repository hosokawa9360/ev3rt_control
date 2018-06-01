/**
 *  CMD_Main.c
 *
 *  Command handling main source code.
 */
#include "ev3api.h"
#include "CMD.h"

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern uint8_t rcv_msg_buf[];
extern uint8_t snd_msg_buf[];
extern uint8_t rcv_msg_len;
extern uint8_t snd_msg_len;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/
extern void cmd_code00(void);
extern void cmd_code02(void);
extern void cmd_code04(void);
extern void cmd_code06(void);
extern void cmd_code12(void);
extern void cmd_code16(void);
extern void cmd_code20(void);

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
static void cmd_invalid_code(void);

/**
 *  @brief  Main function handling command data.
 *          Judge command code included in received data and call the function
 *          to handle received data.
 */
void cmd_handle_main() {
    char cmd_code = 0;

    cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_CODE];
    switch (cmd_code) {
    case 0x00: cmd_code00(); break;
    case 0x02: cmd_code02(); break;
    case 0x04: cmd_code04(); break;
    case 0x06: cmd_code06(); break;
    case 0x12: cmd_code12(); break;
    case 0x16: cmd_code16(); break;
    case 0x20: cmd_code20(); break;
    default: cmd_invalid_code(); break;
    }
}

/**
 *  @brief  Set up response code to send when the command code included
 *          received data is invalid.
 */
static void cmd_invalid_code(void) {
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0xFF;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = 0x00;
    snd_msg_len = 2; 
}
