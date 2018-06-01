/**
 *  CMD_Code06.c
 *
 *  GetSafeState command source code file.
 */
#include "ev3api.h"
#include "CMD.h"

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
extern uint8_t rcv_msg_buf[];
extern uint8_t snd_msg_buf[];
extern uint8_t rcv_msg_len;
extern uint8_t snd_msg_len;
extern int8_t distance_safe_state;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Main function of GetSafeState command.
 *          This function, command, returns safe state calcurated and judged
 *          from distance between ultrasonic sensor on Ev3 and obstacle
 *          in front of the device.
 */
void cmd_code06(void) {
    uint8_t res_code = CMD_ERROR_OK;
    uint8_t cmd_data_len = 0;
    uint8_t sub_cmd_code = 0x00;
    uint8_t sub_res_code = 0x00;
    uint8_t res_data_len = 0;

    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    cmd_data_len = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN];

    sub_res_code = sub_cmd_code;
    if (0x00 != cmd_data_len) {
        res_code = CMD_ERROR_CMD_DATA_LEN;
        res_data_len = 0;
    } else {
        if (0x00 != sub_cmd_code) {
            res_code = CMD_ERROR_INVALID_SUB_CODE;
            res_data_len = 0;

            sub_res_code = CMD_ERROR_INVALID_SUB_CODE;
        } else {
            snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP] = distance_safe_state;
            res_data_len = 1;
        }
    }

    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x07;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}
