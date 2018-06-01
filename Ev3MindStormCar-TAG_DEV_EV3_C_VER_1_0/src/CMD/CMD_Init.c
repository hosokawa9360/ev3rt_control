/**
 *  CMD_Init.c
 *
 *  Call initialize function of command.
 */
#include "ev3api.h"
#include "TSK/TSK_Bt.h"

#define COMMAND_DATA_BUF_SIZE       MESSAGE_BUF_SIZE
#define COMMAND_RECV_DATA_BUF_SIZE  COMMAND_DATA_BUF_SIZE
#define COMMAND_SEND_DATA_BUF_SIZE  COMMAND_DATA_BUF_SIZE

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern uint8_t bt_rcv_msg_buf[];
extern uint8_t bt_rcv_msg_len;

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
uint8_t rcv_msg_buf[COMMAND_RECV_DATA_BUF_SIZE];
uint8_t snd_msg_buf[COMMAND_SEND_DATA_BUF_SIZE];
uint8_t rcv_msg_len = 0;
uint8_t snd_msg_len = 0;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
void cmd_reset_buff(void);

/**
 *  @brief  コマンドデータを初期化する。
 */
void init_cmd(void) { cmd_reset_buff(); }

/**
 *  @brief  受信データバッファを初期化する。
 */
void cmd_reset_rcv_buff(void) {
    int idx = 0;

    for (idx = 0; idx < COMMAND_RECV_DATA_BUF_SIZE; idx++) {
        rcv_msg_buf[idx] = 0x00;
    }
    rcv_msg_len = 0;
}

/**
 *  @brief  送信データバッファを初期化する。
 */
void cmd_reset_snd_buff(void) {
    int idx = 0;
    
    for (idx = 0; idx < COMMAND_SEND_DATA_BUF_SIZE; idx++) {
        snd_msg_buf[idx] = 0x00;
    }
    snd_msg_len = 0;
}

/**
 *  @brief  コマンド用の送信・受信データ用のバッファを初期化する。
 *          (cmd_reset_rcv_buff()、cmd_reset_snd_buff()が連続で実行される。)
 */
void cmd_reset_buff(void) {
    cmd_reset_rcv_buff();
    cmd_reset_snd_buff();
}

/**
 *  @brief  Bluetoothから受信したデータを、コマンド処理用のバッファに
 *          コピー(ラッチ)する。
 */
void cmd_latch_buff(void) {
    int idx;

    for (idx = 0; idx < bt_rcv_msg_len; idx++) {
        rcv_msg_buf[idx] = bt_rcv_msg_buf[idx];
    }
    rcv_msg_len = bt_rcv_msg_len;
}