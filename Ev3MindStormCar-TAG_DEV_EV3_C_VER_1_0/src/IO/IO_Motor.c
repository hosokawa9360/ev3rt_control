/**
 *  motor_logic
 *
 *  Program to rotate motor.
 */
#include "ev3api.h"
#include "ev3portconf.h"

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int left_motor_config = -1;
int right_motor_config = -1;
int left_motor_power_current;
int right_motor_power_current;

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern int left_motor_power;
extern int right_motor_power;
extern int turn_ratio;

/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/
const motor_port_t left_motor_port = LEFT_MOTOR_PORT;
const motor_port_t right_motor_port = RIGHT_MOTOR_PORT;

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  算出されたモーター出力で、モーターを動作させる。
 */
void motor_set_power(void) {
#if 0
    ev3_motor_steer(left_motor_port, right_motor_port, 
        left_motor_power, turn_ratio);
#else
    ev3_motor_set_power(left_motor_port, left_motor_power);
    ev3_motor_set_power(right_motor_port, right_motor_power);
#endif
}

/**
 *  モーターの動作出力を取得する。
 */
void motor_get_power(void) {
    left_motor_power_current = ev3_motor_get_power(left_motor_port);
    right_motor_power_current = ev3_motor_get_power(right_motor_port);
}

/**
 *  モーターの設定の初期化
 */
void init_motor_config(void) {
    ER ret;

    ret = ev3_motor_config(left_motor_port, MEDIUM_MOTOR);
    if (E_OK == ret) {
        left_motor_config = 0;
    } else if (E_ID == ret) {
        left_motor_config = 1;
    } else if (E_PAR == ret) {
        left_motor_config = 2;
    } else {
        left_motor_config = 3;
    }

    ret = ev3_motor_config(right_motor_port, MEDIUM_MOTOR);
    if (E_OK == ret) {
        right_motor_config = 0;
    } else if (E_ID == ret) {
        right_motor_config = 1;
    } else if (E_PAR == ret) {
        right_motor_config = 2;
    } else {
        right_motor_config = 3;
    }
    
    left_motor_power_current = 0;
    right_motor_power_current = 0;
}
