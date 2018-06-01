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
/*                                  �ϐ���`                                 */
/*****************************************************************************/
int bt_task_count = 0;
int cmd_hdl_count = 0;
bool_t bt_task_running;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/
static FLGPTN bt_wait_flg;

/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern bool_t is_connect_bt;
extern uint8_t snd_msg_buf[];
extern uint8_t snd_msg_len;
extern uint8_t bt_rcv_msg_len;

/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/
static const FLGPTN bt_Wait_flg_ptn = (FLGPTN)1; //b'00000001

/*****************************************************************************/
/*                                  �O���֐�                                 */
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
/*                                  �֐�����                                 */
/*****************************************************************************/
void wait_btconnect(void);
void init_bt(void);
void start_bt_task(void);
void restart_bt_task(void);
void wait_bt_task(void);

/**
 *  @brief  Bluetooth�^�X�N
 *          ��M�����R�}���h�f�[�^���������ꍇ�ɂ́A�Ή����鏈�������{���A
 *          ���X�|���X�f�[�^�𑗐M����B
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
 *  Bluetooth��PC�Ɛڑ������܂ő҂B
 *  �ڑ������܂ŁA������Ԃ��Ȃ��B
 */
void wait_btconnect() {
    while (1) {
        port_check_connectoin();
        if (!is_connect_bt) {
            //�m�F����莞�Ԃ̊Ԋu�ōs���A�������グ��
            dly_tsk(100); //
        } else {
            //�ڑ����ꂽ�ꍇ�ɂ́A���̏���/���[�h�Ɉڍs����B
            break;
        }
    }
}

/**
 *  Bluetooth�̃^�X�N�̏�����
 */
void init_bt(void) {
    bt_wait_flg = (FLGPTN)0;

    bt_task_running = false;

    bt_task_count = 0;
    cmd_hdl_count = 0;
}

/**
 *  Bluetooth�ʐM�̃^�X�N���J�n����B
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
 *  @biref  Bluetooth�ʐM�̃^�X�N���I������B
 *          �����ɁA�e�t���O���N���A����B
 */
void stop_bt_task(void) {
    if (true == bt_task_running) {
        bt_task_running = false;
    }
}
