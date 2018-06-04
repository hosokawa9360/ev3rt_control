/**
 *  IO_Port.c
 *
 *  Control I/O port, open, close, read and write.
 */
#include "ev3api.h"
#include <syssvc/serial.h>
//#include "UTIL/util.h"

#define BT_MESSAGE_BUF_SIZE        (32)


#include "ev3api.h"

extern void init_buff(int size, char *buff, char val);
extern int limit_int(int value, int min, int max);

/**
 *  @macro
 *  バッファーの初期化を行う。
 *  バッファーのインデックスを示す変数を、第1引数に指定する。
 *  valで、初期値(初期化する値)を指定する。
 */
#define INIT_BUF_VAL(size, buff, val)    init_buff(size, buff, val)

/**
 *  @macro
 *  バッファーの初期化を行う。
 *  バッファーのインデックスを示す変数を、第1引数に指定する。
 *  バッファーは、全て「0」で初期化する。
 */
#define INIT_BUF(size, buff) INIT_BUF_VAL(size, buff, 0)

#define MESSAGE_BUF_SIZE    (32)
#define BT_TASK_INTERVAL    (10)    //10msec
#define COMMAND_DATA_BUF_SIZE       MESSAGE_BUF_SIZE
#define COMMAND_RECV_DATA_BUF_SIZE  COMMAND_DATA_BUF_SIZE
#define COMMAND_SEND_DATA_BUF_SIZE  COMMAND_DATA_BUF_SIZE
/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
bool_t is_connect_bt;
uint8_t bt_rcv_msg_buf[BT_MESSAGE_BUF_SIZE];
uint8_t bt_rcv_msg_len = 0;

uint8_t rcv_msg_buf[COMMAND_RECV_DATA_BUF_SIZE];
uint8_t snd_msg_buf[COMMAND_SEND_DATA_BUF_SIZE];
uint8_t rcv_msg_len = 0;
uint8_t snd_msg_len = 0;
/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern uint8_t snd_msg_buf[];
extern uint8_t snd_msg_len;

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
 *  引数で指定されたバッファを初期化する。
 */
void init_buff(int size, char *buff, char val) {
    int id;

    for (id = 0; id < size; id++) {
        *buff = val;
        buff++;
    }
}

/**
 *  @brief  ポートの接続状態を確認する。
 */
void port_check_connectoin() {
    is_connect_bt = ev3_bluetooth_is_connected();
}

/**
 *  @brief  ポートとの接続状態を確認の上、データを読み込む。
 *          ポートと接続されていない場合には、読み込んだデータ長は「0」として扱う。
 */
void port_read_data() {
    if (true == is_connect_bt) {
        INIT_BUF(BT_MESSAGE_BUF_SIZE, (char *)(&bt_rcv_msg_buf[0]));
        bt_rcv_msg_len = serial_rea_dat(SIO_PORT_BT, 
            (char *)(&bt_rcv_msg_buf[0]),
            BT_MESSAGE_BUF_SIZE);
    } else {
        bt_rcv_msg_len = 0;
    }
}

/**
 *  @brief  Bluetoothの送信データを、ポートに書き込む。
 *          書き込む際にBluetoothが接続されていない場合には、何もしない。
 *          また、書き込むデータが設定されていない場合にも、何もしない。
 */
void port_write_data() {
    if ((true == is_connect_bt) && (snd_msg_len > 0)) {
        /*
         *  Bluetoothポートが接続され、かつ一定以上の送信データがセット
         *  されていた場合に、データを送信する。
         */
        serial_wri_dat(SIO_PORT_BT,
            (char *)(&snd_msg_buf[0]),
            snd_msg_len);
    }
}

/**
 *  @brief  IOポートを初期化する。
 *          ポートの接続状態(を示すフラグ)、およびBluetoothデータ受信バッファの
 *          初期化を行う。
 */
void init_io_port() {
    INIT_BUF(BT_MESSAGE_BUF_SIZE, (char *)(&bt_rcv_msg_buf[0]));

    bt_rcv_msg_len = 0;
    is_connect_bt = false;
}

/**
 *  @brief  IOポート、受信データの有無(受信データの長さ)を初期化する。
 *          (受信データの内容は、初期化しない。)
 */
void port_reset() { bt_rcv_msg_len = 0; }
