/**
 *  motor_task.c
 *
 *  Run motor.
 */
#include "ev3api.h"
#include "target_test.h"
#include "TSK_Motor.h"

/*****************************************************************************/
/*                               グローバル変数                              */
/*****************************************************************************/
int left_motor_status;
int right_motor_status;
int motor_task_count = 0;
bool_t motor_task_running;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                    定数                                   */
/*****************************************************************************/

/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/
extern void judge_motor_output_limit(void);
extern void calc_motor_power(void);
extern void motor_set_power(void);
extern void motor_get_power(void);
extern void update_drive_direction(void);
extern void judge_target_motor_output(void);
extern void calc_target_motor_outputLR(void);
extern void get_distance(void);
extern void calc_distance_average(void);
extern void judge_dist_safe(void);

/*****************************************************************************/
/*                                   関数                                    */
/*****************************************************************************/
/**
 *  @brief  Task to read sensor value, calcurate motor power output, and
 *          set it to motor.
 */
void motor_task(intptr_t unused) {
    while (motor_task_running) {
        //Read current, actual motor output.
        motor_get_power();

        //Calcurate motor output.
        judge_motor_output_limit();
        judge_target_motor_output();
        calc_target_motor_outputLR();
        calc_motor_power();

        //Set motor output data.
        motor_set_power();

        motor_task_count++;
        dly_tsk(MOTOR_TASK_INTERVAL);
    }
}

/**
 *  @brief  Initialize motor task.
 */
void init_motor_task() {
    motor_task_count = 0;
    
    motor_task_running = false;
}

/**
 *  @brief  Start motor control task.
 */
void start_motor_task() {
    ER ercd;

    if (false == motor_task_running) {
        ercd = act_tsk(MOTOR_TASK);
        if (E_OK == ercd) {
            motor_task_running = true;
        } else {
            motor_task_running = false;
        }
    }
}

/**
 *  @brief  Stop motor control task.
 */
void stop_motor_task() {
    if (true == motor_task_running) {
        motor_task_running = false;
    }
}