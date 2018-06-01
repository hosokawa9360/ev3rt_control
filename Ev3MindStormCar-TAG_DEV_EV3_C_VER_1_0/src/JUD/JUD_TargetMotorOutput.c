/**
 *  JUD_TargetMotorOutput.c
 *
 *  Decide motor output power from that of limit and input.
 */
#include "ev3api.h"

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int target_motor_output;

/*****************************************************************************/
/*                               静的変数定義                                */
/*****************************************************************************/


/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern int8_t motor_output_max;
extern uint8_t cmd_target_motor_output;
extern int cmd_drive_direction;

/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                               静的定数定義                                */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Judge target motor output drive power.
 */
void judge_target_motor_output(void) {
    //モーター出力値のリミット処理
    int target_motor_output_tmp;

    if (1 == cmd_drive_direction) {
        if (motor_output_max < cmd_target_motor_output) {
            target_motor_output = (int)motor_output_max;
        } else {
            target_motor_output = (int)cmd_target_motor_output;
        }
    } else {
        target_motor_output_tmp = (int)cmd_target_motor_output;
        target_motor_output = target_motor_output_tmp * cmd_drive_direction;
    }
}

/**
 *  @brief  Initialize target motor drive power.
 */
void init_motor_output(void) {
    target_motor_output = 0;
}
