/**
 *  CMD_Code02.c
 *
 *  AppVersion command source code file.
 */
#include "ev3api.h"
#include "CMD.h"
#include "app.h"

/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
extern uint8_t rcv_msg_buf[];
extern uint8_t snd_msg_buf[];
extern uint8_t rcv_msg_len;
extern uint8_t snd_msg_len;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���萔��`                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �O���֐�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/
/**
 *  @brief  Main function of AppVersion Command.
 *          This functoin returns 
 */
void cmd_code02(void) {
    uint8_t res_code = CMD_ERROR_OK;
    uint8_t cmd_data_len = 0;
    uint8_t sub_cmd_code = 0x00;
    uint8_t sub_res_code = 0x00;
    uint8_t res_data_len = 0;
    uint8_t *res_data = NULL;

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
            res_data = (uint8_t *)(&snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP]);
            *res_data = (uint8_t)APP_MAJOR_VERSION;
            res_data++;
            *res_data = (uint8_t)APP_MINOR_VERSION;
            res_data_len = 2;
        }
    }

    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x03;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}

