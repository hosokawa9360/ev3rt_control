/**
 *  CMD_Code16.c
 *
 *  SetSteer command, set steering parameter.
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
extern int target_motor_output;


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
int turn_ratio;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  コマンド0x16(SetSteer)の本体
 */
void cmd_code16(void) {
    uint8_t res_code;
    int turn_ratio_cmd;//コマンドデータ上の回転比

    res_code = CMD_ERROR_OK;

    //コマンドフォーマット確認
    //サブコマンドコード
    if (0x00 != rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE]) {
        res_code = CMD_ERROR_INVALID_SUB_CODE;
    }

    //コマンドデータ長
    if ((CMD_ERROR_OK == res_code) &&   //エラー情報の上書き回避
        (0x01 != rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN]))
    {
        res_code = CMD_ERROR_CMD_DATA_LEN;
    }
    //コマンドデータ
    if (CMD_ERROR_OK == res_code) {
        turn_ratio_cmd = (int)((int8_t)rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_TOP]);
        if ((turn_ratio_cmd < -100) || (100 < turn_ratio_cmd)) {
            res_code = CMD_ERROR_INVALID_CMD_DATA;
        } else {
            turn_ratio = turn_ratio_cmd;
        }
    }

    // レスポンスデータ作成
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x17;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = 0x00;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = 0x00;
    snd_msg_len = 4;
}

void init_cmd16(void) {
    turn_ratio = 0;
}

