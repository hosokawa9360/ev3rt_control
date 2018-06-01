/**
 *  Bluetooth task
 *
 *  Task to send data, message throw bluetooth SPP.
 */
#include "ev3api.h"
#include <syssvc/serial.h>
#include "TSK_Bt.h"
#include "UTIL/util.h"

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int bt_task_count = 0;
int cmd_hdl_count = 0;
bool_t bt_task_running;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/
static FLGPTN bt_wait_flg;

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern bool_t is_connect_bt;
extern uint8_t snd_msg_buf[];
extern uint8_t snd_msg_len;
extern uint8_t bt_rcv_msg_len;

/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/
static const FLGPTN bt_Wait_flg_ptn = (FLGPTN)1; //b'00000001

/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/
extern void port_check_connectoin(void);
extern void port_read_data(void);
extern void port_write_data(void);
extern void port_reset(void);
extern void CmdTask(intptr_t unused);
extern void wakeup_cmd_task(void);
extern void restart_cmd_task(void);
extern void cmd_sequence(void);

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
void wait_btconnect(void);
void init_bt(void);
void start_bt_task(void);
void restart_bt_task(void);
void wait_bt_task(void);

/**
 *  @brief  Bluetoothタスク
 *          受信したコマンドデータがあった場合には、対応する処理を実施し、
 *          レスポンスデータを送信する。
 */
void BtTask(intptr_t unused) {
    while (bt_task_running) {
        bt_task_count++;

        port_check_connectoin();
        port_read_data();
        if (0 < bt_rcv_msg_len) {
            cmd_hdl_count++;
            
            cmd_sequence();
            port_write_data();
            port_reset();
        }
        dly_tsk(BT_TASK_INTERVAL);
    }
}

/**
 *  BluetoothでPCと接続されるまで待つ。
 *  接続されるまで、処理を返さない。
 */
void wait_btconnect() {
    while (1) {
        port_check_connectoin();
        if (!is_connect_bt) {
            //確認を一定時間の間隔で行い、効率を上げる
            dly_tsk(100); //
        } else {
            //接続された場合には、次の処理/モードに移行する。
            break;
        }
    }
}

/**
 *  Bluetoothのタスクの初期化
 */
void init_bt(void) {
    bt_wait_flg = (FLGPTN)0;

    bt_task_running = false;

    bt_task_count = 0;
    cmd_hdl_count = 0;
}

/**
 *  Bluetooth通信のタスクを開始する。
 */
void start_bt_task(void) {
    ER ercd;
    if (false == bt_task_running) {
        ercd = act_tsk(BTTASK);
        if (E_OK == ercd) {
            bt_task_running = true;
        } else {
            bt_task_running = false;
        }
    }
}

/**
 *  @biref  Bluetooth通信のタスクを終了する。
 *          同時に、各フラグをクリアする。
 */
void stop_bt_task(void) {
    if (true == bt_task_running) {
        bt_task_running = false;
    }
}
