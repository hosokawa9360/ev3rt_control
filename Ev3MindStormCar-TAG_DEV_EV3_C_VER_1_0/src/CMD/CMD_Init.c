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
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern uint8_t bt_rcv_msg_buf[];
extern uint8_t bt_rcv_msg_len;

/*****************************************************************************/
/*                                �O���萔��`                               */
/*****************************************************************************/

/*****************************************************************************/
/*                                  �O���֐�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
uint8_t rcv_msg_buf[COMMAND_RECV_DATA_BUF_SIZE];
uint8_t snd_msg_buf[COMMAND_SEND_DATA_BUF_SIZE];
uint8_t rcv_msg_len = 0;
uint8_t snd_msg_len = 0;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/
void cmd_reset_buff(void);

/**
 *  @brief  �R�}���h�f�[�^������������B
 */
void init_cmd(void) { cmd_reset_buff(); }

/**
 *  @brief  ��M�f�[�^�o�b�t�@������������B
 */
void cmd_reset_rcv_buff(void) {
    int idx = 0;

    for (idx = 0; idx < COMMAND_RECV_DATA_BUF_SIZE; idx++) {
        rcv_msg_buf[idx] = 0x00;
    }
    rcv_msg_len = 0;
}

/**
 *  @brief  ���M�f�[�^�o�b�t�@������������B
 */
void cmd_reset_snd_buff(void) {
    int idx = 0;
    
    for (idx = 0; idx < COMMAND_SEND_DATA_BUF_SIZE; idx++) {
        snd_msg_buf[idx] = 0x00;
    }
    snd_msg_len = 0;
}

/**
 *  @brief  �R�}���h�p�̑��M�E��M�f�[�^�p�̃o�b�t�@������������B
 *          (cmd_reset_rcv_buff()�Acmd_reset_snd_buff()���A���Ŏ��s�����B)
 */
void cmd_reset_buff(void) {
    cmd_reset_rcv_buff();
    cmd_reset_snd_buff();
}

/**
 *  @brief  Bluetooth�����M�����f�[�^���A�R�}���h�����p�̃o�b�t�@��
 *          �R�s�[(���b�`)����B
 */
void cmd_latch_buff(void) {
    int idx;

    for (idx = 0; idx < bt_rcv_msg_len; idx++) {
        rcv_msg_buf[idx] = bt_rcv_msg_buf[idx];
    }
    rcv_msg_len = bt_rcv_msg_len;
}