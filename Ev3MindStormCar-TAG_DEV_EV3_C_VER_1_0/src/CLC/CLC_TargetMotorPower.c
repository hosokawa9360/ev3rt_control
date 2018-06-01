/**
 *  @file   CLC_TargetMotorPower.c
 *
 *  @detail �w�肳�ꂽ�ڕW�o�͂ɁA�^�[����𔽉f����B
 */
#include "ev3api.h"
#include "util.h"

#define TARGET_MOTOR_OUTPUT_MAX     (50)
#define TARGET_MOTOR_OUTPUT_MIN     (-50)


/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
int target_motor_output_left;
int target_motor_output_right;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern int turn_ratio;
extern int target_motor_output;

/*****************************************************************************/
/*                                �O���萔��`                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �O���֐�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/
/**
 *  @brief  Reflect the turn ration into calcurated value.
 */
void calc_target_motor_outputLR(void) {
    int target_motor_output_left_tmp;
    int target_motor_output_right_tmp;
    int prov_output;

    //Calcurate left motor output.
    target_motor_output_left_tmp =
        (target_motor_output * (100 + turn_ratio)) / 100;
    //Calcurate right motor output.
    target_motor_output_right_tmp =
        (target_motor_output * (100 - turn_ratio)) / 100;

    /*
     *  TODO:
     *      Add code to limit the motor output power in the case
     *      output exceeds threshold value.
     */
    if (((target_motor_output_left_tmp < -50) ||
        (50 < target_motor_output_left_tmp)) &&
        ((-50 <= target_motor_output_right_tmp) &&
        (target_motor_output_right_tmp <= 50)))
    {
        //Case that only left output power exceeds threshold value.
        target_motor_output_left_tmp = limit_int(
            target_motor_output_left_tmp,
            TARGET_MOTOR_OUTPUT_MIN,
            TARGET_MOTOR_OUTPUT_MAX);
        prov_output = (target_motor_output_left_tmp * 100) / (100 + turn_ratio);
        target_motor_output_right_tmp =
            (prov_output * (100 - turn_ratio)) / 100;
    } else if (((-50 <= target_motor_output_left_tmp) &&
        (target_motor_output_left_tmp <= 50)) &&
        ((target_motor_output_right_tmp < -50) ||
        (50 < target_motor_output_right_tmp)))
    {
        //Case that only right output power exceeds threshold value.
        target_motor_output_right_tmp = limit_int(
            target_motor_output_right_tmp,
            TARGET_MOTOR_OUTPUT_MIN,
            TARGET_MOTOR_OUTPUT_MAX);
        prov_output = (target_motor_output_right_tmp * 100) / (100 - turn_ratio);
        target_motor_output_left_tmp =
            (prov_output * (100 + turn_ratio)) / 100;
    } else if (((target_motor_output_left_tmp < -50) ||
        (50 < target_motor_output_left_tmp)) &&
        ((target_motor_output_right_tmp < -50) ||
        (50 < target_motor_output_right_tmp)))
    {
        //Both side output power exceeds threshold value.
        target_motor_output_left_tmp =
            (target_motor_output * (100 + turn_ratio)) / 400;
        target_motor_output_right_tmp =
            (target_motor_output * (100 - turn_ratio)) / 400;
    }

    target_motor_output_left = target_motor_output_left_tmp;
    target_motor_output_right = target_motor_output_right_tmp;
}


