/**
 *  CMD_Code12.c
 *
 *  SetMotorPower command source code file.
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
extern int left_motor_power;
extern int right_motor_power;

/*****************************************************************************/
/*                                �O���萔��`                               */
/*****************************************************************************/
extern const motor_port_t left_motor_port;
extern const motor_port_t right_motor_port;

/*****************************************************************************/
/*                                  �O���֐�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/
const int CMD_DRIVE_DIRECTION_FORWARD = 0;
const int CMD_DRIVE_DIRECTION_BACK = 1;


/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
int cmd_drive_direction;
uint8_t cmd_target_motor_output = 0;
uint8_t cmd_target_motor_direction = 0;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/
DECLARE_SUB_CMD_CODE_FUNC(cmd_code12_00);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code12_01);
static uint8_t GetPortIndex(motor_port_t port);
/**
 *  @brief  SetMotorPower�R�}���h�{�́B
 *          ���[�^�[�̏o�͒l��ݒ肷��B
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
     *  �R�}���h0x12�ł́A�R�}���h�f�[�^���̓T�u�R�}���h�R�[�h���ƂɈقȂ�B
     *  ���̂��߁A�f�[�^���̊m�F�́A�T�u�R�}���h�֐��̒��Ŏ��{����B
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
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;  //���X�|���X�f�[�^��
    snd_msg_len = 4 + res_data_len;
}

/**
 *  @brief  �R�}���h�R�[�h:0x12/�T�u�R�}���h�R�[�h�F0x00�̊֐�
 *          ���[�^�[�̖ڕW�o�͒l�A����щ�]���������肷��B
 *  @param cmd ��M�����o�C�g�f�[�^���́A�R�}���h�f�[�^�̐擪�ւ̃|�C���^
 *  @param cmd_len ��M�����o�C�g�f�[�^���̃R�}���h�f�[�^��
 *  @param res ���X�|���X�̃o�C�g�f�[�^���́A���X�|���X�f�[�^�ւ̃|�C���^
 *  @param res_len ���X�|���X�̃o�C�g�f�[�^���́A���X�|���X�f�[�^��
 *
 *  @return �R�}���h�����̎��s���ʁB���������ꍇ�ɂ́u0�v��Ԃ��B
 *          �G���[�����������ꍇ�ɂ́A�u0��ȊO��Ԃ��B
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

    //�R�}���h�f�[�^�̊m�F
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

    //�R�}���h�f�[�^�̔��f
    if (CMD_ERROR_OK == res_code) {
        cmd_target_motor_output = cmd_target_motor_output_tmp;
        if (0x00 == cmd_target_motor_direction_tmp) {
            cmd_drive_direction = -1;//���
        } else {
            cmd_drive_direction = 1;//�O�i
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
        //�����[�^�[�o�͂̎擾
        left_index = GetPortIndex(left_motor_port);
        cmd_data = cmd + left_index;
        left_target_motor_output_tmp = *cmd_data;
        cmd_data++;
        left_target_motor_direction_tmp = *cmd_data;

        //�E���[�^�[�o�͂̎擾
        right_index = GetPortIndex(right_motor_port);
        cmd_data = cmd + right_index;
        right_target_motor_output_tmp = *cmd_data;
        cmd_data++;
        right_target_morot_direction_tmp = *cmd_data;

        //�e�p�����[�^�̊m�F
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
             *  �p�����[�^�����킾�����ꍇ-�l���Z�b�g���ă��X�|���X��Ԃ��B
             */
            left_motor_power = left_target_motor_output_tmp;
            if (0x01 == left_target_motor_direction_tmp) {
                left_motor_power *= (-1);//�������]
            }
            right_motor_power = right_target_motor_output_tmp;
            if (0x01 == right_target_morot_direction_tmp) {
                right_motor_power *= (-1);//�������]
            }
            //�ڑ�����Ă��Ȃ��f�o�C�X����ẮA�\�ߒl��ݒ�
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
 *  @brief  �����Ŏw�肳�ꂽ�|�[�g�ɑ΂���f�[�^�̊J�n�ʒu��
 *          �C���f�b�N�X��Ԃ��B
 *
 *  @param  port    �����Ώۂ̃|�[�g
 *  @return �f�[�^�̊J�n�ʒu�̃C���f�b�N�X
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