/**
 *  TSK_Safe.c
 *
 *  Task to judge and set car's safe state.
 */
#include "ev3api.h"
#include "target_test.h"
#include "TSK_Safe.h"

/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���萔��`                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �O���֐�                                 */
/*****************************************************************************/
extern void get_distance(void);
extern void calc_distance_average(void);
extern void judge_dist_safe(void);

/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
int safe_task_count = 0;
bool_t safe_task_running;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �֐��錾                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/
/**
 *  @brief  Task to read ultrasonic sensor value, calcurate motor power,
 *          and judge safe state from these values.
 */
void safe_task(intptr_t unused)
{
    while (true == safe_task_running) {
        get_distance();
        calc_distance_average();
        judge_dist_safe();//��������A���S��Ԃ𔻒�

        safe_task_count++;
        dly_tsk(SAFE_TASK_INTERVAL);
    }
}

/**
 *  @brief  Initialize safe state task.
 */
void init_safe_task() {
    safe_task_count = 0;
    
    safe_task_running = false;
}
 
/**
 *  @brief  Start safe state control task.
 */
void start_safe_task() {
    ER ercd;

    if (false == safe_task_running) {
        ercd = act_tsk(SAFE_TASK);
        if (E_OK == ercd) {
            safe_task_running = true;
        } else {
            safe_task_running = false;
        }
    }
}

/**
 *  @brief  Stop safe state control task.
 */
void stop_safe_task() { 
    if (true == safe_task_running) {
        safe_task_running = false;
    }
}
