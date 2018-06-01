/**
 *  judge_motor_outout_limit
 *
 *  Calc max motor output power from state of safe distance.
 */
#include "ev3api.h"

/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
int8_t motor_output_max;


/*****************************************************************************/
/*                               �ÓI�ϐ���`                                */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern int8_t distance_safe_state;


/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/
extern const int8_t CAR_SAFE_STATE_SAFE;
extern const int8_t CAR_SAFE_STATE_ATTN;
extern const int8_t CAR_SAFE_STATE_DANG;
extern const int8_t CAR_SAFE_STATE_STOP;

const int8_t MOTOR_OUTPUT_LIMIT_STATE_SAFE = 100;
const int8_t MOTOR_OUTPUT_LIMIT_STATE_ATTN = 30;
const int8_t MOTOR_OUTPUT_LIMIT_STATE_DANG = 20;
const int8_t MOTOR_OUTPUT_LIMIT_STATE_STOP = 0;

/*****************************************************************************/
/*                               �ÓI�萔��`                                */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/
/**
 *  @brief  Judge motor output power max limitation from current safe state.
 */
void judge_motor_output_limit(void) {
    if (CAR_SAFE_STATE_SAFE == distance_safe_state) {
        motor_output_max = MOTOR_OUTPUT_LIMIT_STATE_SAFE;
    } else if (CAR_SAFE_STATE_ATTN == distance_safe_state) {
        motor_output_max = MOTOR_OUTPUT_LIMIT_STATE_ATTN;
    } else if (CAR_SAFE_STATE_DANG == distance_safe_state) {
        motor_output_max = MOTOR_OUTPUT_LIMIT_STATE_DANG;
    } else if (CAR_SAFE_STATE_STOP == distance_safe_state) {
        motor_output_max = MOTOR_OUTPUT_LIMIT_STATE_STOP;
    } else {
        motor_output_max = MOTOR_OUTPUT_LIMIT_STATE_STOP;
    }
}

/**
 *  @brief  Initialize motor output power max limitation.
 */
void init_motor_output_limit(void) {
    motor_output_max = MOTOR_OUTPUT_LIMIT_STATE_SAFE;
}
