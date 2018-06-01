/**
 *  Log_ClcMotor.c
 *
 *  Write parameters derived in calculation.
 */
#include "ev3api.h"
#include "CLC_MotorOutput.h"

/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
FILE *clc_motor_log = NULL;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/
static const char *clc_motor_log_file_name = "clc_motor_log.csv";
static const char *clc_motor_log_format = "LP,LI,RP,RI\n";//No D Term of PID
//Order:left_power,right_power

/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern power_t left_power;
extern power_t right_power;

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
 *  @brief  Open logging file of paramter in calculating motor power.
 */
void init_clc_motor_log(void)
{
    clc_motor_log = fopen(clc_motor_log_file_name, "a");
    if (NULL != clc_motor_log) {
        fprintf(clc_motor_log, (const char *)clc_motor_log_format);
    }

}

/**
 *  @brief  Close logging file.
 */
void fin_clc_motor_log(void) 
{
    if (NULL != clc_motor_log) { fclose(clc_motor_log); }
}

/**
 *  @brief  Logging parameter in calculating motor power.
 */
void logging_clc_motor(void)
{
    if (NULL != clc_motor_log) {
        fprintf(clc_motor_log,
            "%d,%d,%d,%d\n",
            left_power.diff, left_power.integral,
            right_power.diff, right_power.integral);
    }
}
