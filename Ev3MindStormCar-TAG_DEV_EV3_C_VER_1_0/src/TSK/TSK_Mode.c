/**
 *  TSK_Mode.c
 *
 *  Task of each mode.
 */
#include "ev3api.h"
#include "app.h"
#include "TSK_Mode.h"

/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
//�Z���T�[�̐ݒ�
extern bool_t can_continue_mode3;
extern bool_t bt_task_running;
extern bool_t safe_task_running;
extern bool_t motor_task_running;
extern bool_t log_task_running;

/*****************************************************************************/
/*                                �O���萔��`                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �O���֐�                                 */
/*****************************************************************************/
extern void init_bt(void);
extern void init_cmd(void);
extern void init_cmd_task(void);
extern void init_led_color(void);
extern void init_debug_uart(void);
extern void init_sonic_sensor(void);
extern void init_distance_averate(void);
extern void init_dist_safe(void);
extern void init_motor_task(void);
extern void init_motor_config(void);
extern void init_motor_output_limit(void);
extern void init_motor_output(void);
extern void init_motor_power(void);
extern void init_log(void);

extern void port_check_connectoin();

extern void ModeTransitionToMode1();
extern void ModeTransitionToMode2();
extern void ModeTransitionToMode3();
extern void ModeTransitionToMode4();
extern void CheckCanContinueMode3(void);
extern void wait_btconnect();

extern void start_bt_task(void);
extern void start_safe_task(void);
extern void start_log_task(void);
extern void stop_bt_task(void);
extern void stop_safe_task(void);
extern void start_motor_task(void);
extern void stop_motor_task(void);
extern void stop_log_task(void);

extern void set_led_color_off(void);
extern void set_led_color_red(void);
extern void set_led_color_green(void);
extern void set_led_color_orange(void);

extern void debug_clear(void);
extern void debug_device_info(void);
extern void debug_write_msg(const char *msg, int line_index);

extern void fin_log(void);

/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/
extern const uint8_t APP_MODE_MODE1;
extern const uint8_t APP_MODE_MODE2;
extern const uint8_t APP_MODE_MODE3;
extern const uint8_t APP_MODE_MODe4;

/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
int mode_task_count;

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
 *  @brief  ���[�h1�ł̃��C���^�X�N
 *          �e�평�������s���A���̌ヂ�[�h2�ɑJ�ڂ�����B
 */
void task_mode1(intptr_t unused) {
    init_led_color();
    init_debug_uart();
    init_sonic_sensor();
    init_distance_averate();
    init_dist_safe();
    init_motor_task();
    init_motor_config();
    init_motor_output();
    init_motor_output_limit();
    init_motor_power();
    init_log();
    debug_clear();
    
    set_led_color_off();
    
    //�e��o�b�t�@�[������
    init_bt();
    init_cmd();

    //�e�평�����������������[�h2�ɑJ��
    ModeTransitionToMode2();
}

/**
 *  @brief  ���[�h2�ł̃��C���^�X�N
 *          Bluetooth�ł̐ڑ���҂��A�ڑ����ꂽ��ɁA���[�h3�֑J�ڂ���B
 */
void task_mode2(intptr_t unused) {

    debug_clear();
    debug_write_msg((const char*)"APP_MOD:2", 0);
    debug_write_msg((const char *)"BLUETOOTH:DISCONN", 1);
    
    set_led_color_orange();
    wait_btconnect();
    set_led_color_off();
    
    debug_clear();
    debug_write_msg((const char*)"APP_MOD:2", 0);
    debug_write_msg((const char *)"BLUETOOTH:CONNECT", 1);
    
    //Bluetooth�ڑ�����
    ModeTransitionToMode3();
}

/**
 *  @brief  ���[�h3�ł̃��C���^�X�N
 */
void task_mode3(intptr_t unused) {

    debug_clear();

    while ((false == bt_task_running) || 
        (false == safe_task_running) ||
        (false == motor_task_running) ||
        (false == log_task_running)) {
        //�e�^�X�N���X�^�[�g
        start_bt_task();
        start_safe_task();
        start_motor_task();
        start_log_task();
    }
    
    dly_tsk(TASK_MODE3_INTERVAL);//WAIT��ԂɑJ�ځF���̃^�X�N�����s����B
    
    debug_clear();
    CheckCanContinueMode3();

    mode_task_count = 0;

    //��莞�Ԃ��ƂɁALCD�ւ̃f�o�b�O�\�����X�V����B
    while (can_continue_mode3) {
        mode_task_count++;


        debug_device_info();
        //LCD�̍X�V�����F50msec(���ݒ�)
        dly_tsk(TASK_MODE3_INTERVAL);//WAIT��ԂɑJ�ځF���̃^�X�N�����s����B

        port_check_connectoin(); 
        CheckCanContinueMode3();
    }

    debug_clear();
    //Bluetooth�ڑ�����
    ModeTransitionToMode4();
}

/**
 *  @brief  ���[�h4�ł̃��C���^�X�N�B
 *          ���s���̒�����������~���A�ēx���[�h1�ɑJ�ڂ���B
 */
void task_mode4(intptr_t unused) {
    debug_clear();

    set_led_color_red();

    dly_tsk(50);

    while ((true == bt_task_running) ||
        (true == safe_task_running) ||
        (true == motor_task_running) ||
        (true == log_task_running)) {
        stop_bt_task();
        stop_safe_task();
        stop_motor_task();
        stop_log_task();
        dly_tsk(50);
    }

    ModeTransitionToMode1();
}