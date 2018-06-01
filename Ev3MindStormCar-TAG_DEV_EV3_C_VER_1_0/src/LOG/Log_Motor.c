/**
 *  Log_Motor.c
 *
 *  Make log file data of motor.
 */
#include "ev3api.h"

/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
FILE *motor_log = NULL;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/
static const char *motor_log_file_name = "motor_log.csv";
static const char *motor_log_format = "LFT,RGT,LCR,RCR,LTRG,RTRG\n";
//Order:left_motor_power, right_motor_power,
//left_motor_power_current, right_motor_power_current

/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern int left_motor_power;
extern int right_motor_power;
extern int left_motor_power_current;
extern int right_motor_power_current;
extern int target_motor_output_left;
extern int target_motor_output_right;

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
 *  @brief  Open logging file of motor.
 */
void init_motor_log(void)
{
    motor_log = fopen(motor_log_file_name, "a");
    if (NULL != motor_log) {
        fprintf(motor_log, (const char *)motor_log_format);
    }
}

/**
 *  @brief  Finalize loggin file of motor.
 */
void fin_motor_log(void)
{
    if (NULL != motor_log) { fclose(motor_log); }
}

/**
 *  @brief  Logging motor data, target and current motor power.
 */
void logging_motor(void)
{
    if (NULL != motor_log) {
        fprintf(motor_log,
            "%d,%d,%d,%d,%d,%d\n",
            left_motor_power, right_motor_power,
            left_motor_power_current, right_motor_power_current,
            target_motor_output_left, target_motor_output_right);
    }
}