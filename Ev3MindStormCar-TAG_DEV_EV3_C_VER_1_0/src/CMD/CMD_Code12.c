/**
 *  CMD_Code12.c
 *
 *  SetMotorPower command source code file.
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
extern int left_motor_power;
extern int right_motor_power;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/
extern const motor_port_t left_motor_port;
extern const motor_port_t right_motor_port;

/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/
const int CMD_DRIVE_DIRECTION_FORWARD = 0;
const int CMD_DRIVE_DIRECTION_BACK = 1;


/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int cmd_drive_direction;
uint8_t cmd_target_motor_output = 0;
uint8_t cmd_target_motor_direction = 0;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
DECLARE_SUB_CMD_CODE_FUNC(cmd_code12_00);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code12_01);
static uint8_t GetPortIndex(motor_port_t port);
/**
 *  @brief  SetMotorPowerコマンド本体。
 *          モーターの出力値を設定する。
 */
void cmd_code12(void) {
    uint8_t res_code = CMD_ERROR_OK;
    uint8_t sub_cmd_code = 0x00;
    uint8_t sub_res_code = 0x00;
    uint8_t res_data_len = 0x00;
    uint8_t (*cmd_code12_sub)(
        uint8_t *cmd, uint8_t cmd_len,
        uint8_t *res, uint8_t *res_len);
    
    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    sub_res_code = sub_cmd_code;

    switch (sub_cmd_code) {
        case 0x00: cmd_code12_sub = cmd_code12_00; break;
        //case 0x01: cmd_code12_sub = cmd_code12_01; break;
        default:cmd_code12_sub = NULL; break;
    }

    /*
     *  コマンド0x12では、コマンドデータ長はサブコマンドコードごとに異なる。
     *  そのため、データ長の確認は、サブコマンド関数の中で実施する。
     */
    if (NULL != cmd_code12_sub) {
        res_code = cmd_code12_sub(
            (uint8_t *)(&rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_TOP]),
            (uint8_t)(rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN]),
            (uint8_t *)(&snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP]),
            (uint8_t *)(&res_data_len));
    } else {
        sub_res_code = 0xFF;
        res_code = CMD_ERROR_INVALID_SUB_CODE;
        res_data_len = 0x00;
    }
   
    //Setup response data.
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x13;  //Response code
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;  //Sub response code
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;  //レスポンスデータ長
    snd_msg_len = 4 + res_data_len;
}

/**
 *  @brief  コマンドコード:0x12/サブコマンドコード：0x00の関数
 *          モーターの目標出力値、および回転方向を決定する。
 *  @param cmd 受信したバイトデータ内の、コマンドデータの先頭へのポインタ
 *  @param cmd_len 受信したバイトデータ内のコマンドデータ長
 *  @param res レスポンスのバイトデータ内の、レスポンスデータへのポインタ
 *  @param res_len レスポンスのバイトデータ内の、レスポンスデータ長
 *
 *  @return コマンド処理の実行結果。成功した場合には「0」を返す。
 *          エラーが発生した場合には、「0｣以外を返す。
 */
static uint8_t cmd_code12_00(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    uint8_t res_code = CMD_ERROR_OK;
    uint8_t cmd_target_motor_output_tmp = 0x00;
    uint8_t cmd_target_motor_direction_tmp = 0x00;
    uint8_t *cmd_data = NULL;

    cmd_data = cmd;
    cmd_target_motor_output_tmp = *cmd_data;
    cmd_data++;
    cmd_target_motor_direction_tmp = *cmd_data;

    //コマンドデータの確認
    if (cmd_target_motor_output_tmp > 100) {
        res_code = CMD_ERROR_INVALID_CMD_DATA;
        *res_len = 0x00;
    }
    if ((0x00 != cmd_target_motor_direction_tmp)
    && (0x01 != cmd_target_motor_direction_tmp))
    {
        res_code = CMD_ERROR_INVALID_CMD_DATA;
        *res_len = 0x00;
    }

    //コマンドデータの反映
    if (CMD_ERROR_OK == res_code) {
        cmd_target_motor_output = cmd_target_motor_output_tmp;
        if (0x00 == cmd_target_motor_direction_tmp) {
            cmd_drive_direction = -1;//後退
        } else {
            cmd_drive_direction = 1;//前進
        }
        
        *res_len = 0x00;
    }

    return res_code;
}

static uint8_t cmd_code12_01(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    uint8_t res_code = CMD_ERROR_OK;
    uint8_t left_index = 0;
    uint8_t right_index = 0;
    uint8_t *cmd_data = NULL;
    uint8_t left_target_motor_output_tmp = 0x00;
    uint8_t left_target_motor_direction_tmp = 0x00;
    uint8_t right_target_motor_output_tmp = 0x00;
    uint8_t right_target_morot_direction_tmp = 0x00;

    if (0x08 != cmd_len) {
        res_code = CMD_ERROR_CMD_DATA_LEN;
        *res_len = 0x00;
    } else {
        //左モーター出力の取得
        left_index = GetPortIndex(left_motor_port);
        cmd_data = cmd + left_index;
        left_target_motor_output_tmp = *cmd_data;
        cmd_data++;
        left_target_motor_direction_tmp = *cmd_data;

        //右モーター出力の取得
        right_index = GetPortIndex(right_motor_port);
        cmd_data = cmd + right_index;
        right_target_motor_output_tmp = *cmd_data;
        cmd_data++;
        right_target_morot_direction_tmp = *cmd_data;

        //各パラメータの確認
        if ((left_target_motor_output_tmp > 100) ||
            (right_target_motor_output_tmp > 100) ||
            ((0x00 != left_target_motor_direction_tmp) &&
            (0x01 != left_target_motor_direction_tmp)) ||
            ((0x00 != right_target_morot_direction_tmp) &&
            (0x01 != right_target_morot_direction_tmp)))
        {
            res_code = CMD_ERROR_INVALID_CMD_DATA;
            *res_len = 0;
        } else {
            /*
             *  パラメータが正常だった場合-値をセットしてレスポンスを返す。
             */
            left_motor_power = left_target_motor_output_tmp;
            if (0x01 == left_target_motor_direction_tmp) {
                left_motor_power *= (-1);//符号反転
            }
            right_motor_power = right_target_motor_output_tmp;
            if (0x01 == right_target_morot_direction_tmp) {
                right_motor_power *= (-1);//符号反転
            }
            //接続されていないデバイス二ついては、予め値を設定
            *(res + 0) = CMD_WARN_NO_DEVICE_CONN;
            *(res + 1) = CMD_WARN_NO_DEVICE_CONN;
            *(res + 2) = CMD_WARN_NO_DEVICE_CONN;
            *(res + 3) = CMD_WARN_NO_DEVICE_CONN;
            *(res + left_index) = CMD_ERROR_OK;
            *(res + right_index) = CMD_ERROR_OK;
            *res_len = 0x04;
            res_code = CMD_ERROR_OK;
        }
    }
    return res_code;
}

/**
 *  @brief  引数で指定されたポートに対するデータの開始位置の
 *          インデックスを返す。
 *
 *  @param  port    検索対象のポート
 *  @return データの開始位置のインデックス
 */
static uint8_t GetPortIndex(motor_port_t port) {
    uint8_t index = 0;
    switch (port) {
        case EV3_PORT_A: index = 0; break;
        case EV3_PORT_B: index = 2; break;
        case EV3_PORT_C: index = 4; break;
        case EV3_PORT_D: index = 6; break;
        default: index = -1; break;
    }

    return index;
}