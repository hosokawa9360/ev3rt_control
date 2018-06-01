/**
 *  CMD_Code00.c
 *
 *  Source code of EchoBack command.
 */
#include "ev3api.h"
#include "CMD.h"

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
extern const int COMMAND_RECV_DATA_BUF_SIZE;
extern const int COMMAND_SEND_DATA_BUF_SIZE;

/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Main function of EchoBack command.
 *          Check and analize command data and setup response data.
 */
void cmd_code00(void) {
    uint8_t res = CMD_ERROR_OK;
    uint8_t cmd_data_len = 0x00;
    uint8_t res_data_len = 0x00;
    uint8_t sub_cmd_code = 0x00;
    uint8_t sub_res_code = 0x00;
    uint8_t *rcv_buf;
    uint8_t *snd_buf;
    int idx = 0;

    rcv_buf = (uint8_t *)(&rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_TOP]);
    snd_buf = (uint8_t *)(&snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP]);
    
    sub_cmd_code = rcv_msg_buf[1];
    cmd_data_len = rcv_msg_buf[2];

    sub_res_code = sub_cmd_code;
    if ((!(0 < cmd_data_len)) || (!(cmd_data_len < 30))) {
        res = CMD_ERROR_CMD_DATA_LEN;
    }
    if (0x00 != sub_cmd_code) {
        res = CMD_ERROR_INVALID_SUB_CODE;
        sub_res_code = 0xFF;
    }
    if (CMD_ERROR_OK == res) {
        for (idx = 0; idx < (int)cmd_data_len; idx++) {
            *snd_buf = *rcv_buf;
            snd_buf++;
            rcv_buf++;
        }
        res_data_len = cmd_data_len;
    } else {
        res_data_len = 0;
    }
    
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x01;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}
