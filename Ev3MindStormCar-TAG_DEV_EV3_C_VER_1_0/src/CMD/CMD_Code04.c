/**
 *  CMD_Code04.c
 *
 *  GetBattery command source code file.
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
 *  @brief  Main functon of GetBattery command.
 *          This function returns current value electric current and
 *          voltage value.
 */ 
void cmd_code04(void) {
    uint8_t res_code;
    uint8_t cmd_data_len = 0;
    uint8_t sub_cmd_code = 0;
    uint8_t sub_res_code = 0;
    uint8_t res_data_len = 0;
    int voltage = 0;
    int current = 0;
    uint8_t *res = NULL;

    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    cmd_data_len = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN];

    sub_res_code = sub_cmd_code;
    //コマンドデータ長確認
    if (0x00 != cmd_data_len) {
        sub_res_code = 0xFE;
        res_code = 0xFF;
        res_data_len = 0;
    } else {
        if (0x00 != sub_cmd_code) {
            sub_res_code = 0xFF;
            res_code = 0xFD;
            res_data_len = 0;
        } else {
            voltage = ev3_battery_voltage_mV();
            current = ev3_battery_current_mA();

            res = (uint8_t *)(&snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP]);
            /*
             *  Electric current value(mA) and voltage are both 2byte value.
             *  Each value is set in little endian format in response.
             */
            *res = (uint8_t)(((uint16_t)(voltage)) & 0x00FF);//current lower byte.
            res++;
            *res = (uint8_t)(((uint16_t)(voltage)) >> 8);//current upper byte.
            res++;
            *res = (uint8_t)(((uint16_t)(current)) & 0x00FF);//voltage lower byte.
            res++;
            *res = (uint8_t)(((uint16_t)(current)) >> 8);//voltage upper byte.
            res++;

            res_code = 0x00;
            res_data_len = 4;
        }
    }
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x05;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}
