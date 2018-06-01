/**
 *  CMD_Code16.c
 *
 *  SetSteer command, set steering parameter.
 */
#include "ev3api.h"
#include "CMD.h"

/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern uint8_t rcv_msg_buf[];
extern uint8_t snd_msg_buf[];
extern uint8_t rcv_msg_len;
extern uint8_t snd_msg_len;
extern int target_motor_output;


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
int turn_ratio;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/
/**
 *  @brief  �R�}���h0x16(SetSteer)�̖{��
 */
void cmd_code16(void) {
    uint8_t res_code;
    int turn_ratio_cmd;//�R�}���h�f�[�^��̉�]��

    res_code = CMD_ERROR_OK;

    //�R�}���h�t�H�[�}�b�g�m�F
    //�T�u�R�}���h�R�[�h
    if (0x00 != rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE]) {
        res_code = CMD_ERROR_INVALID_SUB_CODE;
    }

    //�R�}���h�f�[�^��
    if ((CMD_ERROR_OK == res_code) &&   //�G���[���̏㏑�����
        (0x01 != rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN]))
    {
        res_code = CMD_ERROR_CMD_DATA_LEN;
    }
    //�R�}���h�f�[�^
    if (CMD_ERROR_OK == res_code) {
        turn_ratio_cmd = (int)((int8_t)rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_TOP]);
        if ((turn_ratio_cmd < -100) || (100 < turn_ratio_cmd)) {
            res_code = CMD_ERROR_INVALID_CMD_DATA;
        } else {
            turn_ratio = turn_ratio_cmd;
        }
    }

    // ���X�|���X�f�[�^�쐬
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x17;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = 0x00;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = 0x00;
    snd_msg_len = 4;
}

void init_cmd16(void) {
    turn_ratio = 0;
}

