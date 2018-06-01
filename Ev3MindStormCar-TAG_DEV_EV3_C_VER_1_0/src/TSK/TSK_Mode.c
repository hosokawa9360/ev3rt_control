/**
 *  TSK_Mode.c
 *
 *  Task of each mode.
 */
#include "ev3api.h"
#include "app.h"
#include "TSK_Mode.h"

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
//センサーの設定
extern bool_t can_continue_mode3;
extern bool_t bt_task_running;
extern bool_t safe_task_running;
extern bool_t motor_task_running;
extern bool_t log_task_running;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
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
/*                                  定数定義                                 */
/*****************************************************************************/
extern const uint8_t APP_MODE_MODE1;
extern const uint8_t APP_MODE_MODE2;
extern const uint8_t APP_MODE_MODE3;
extern const uint8_t APP_MODE_MODe4;

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int mode_task_count;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数宣言                                 */
/*****************************************************************************/

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/

/**
 *  @brief  モード1でのメインタスク
 *          各種初期化を行い、その後モード2に遷移させる。
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
    
    //各種バッファー初期化
    init_bt();
    init_cmd();

    //各種初期化処理完了→モード2に遷移
    ModeTransitionToMode2();
}

/**
 *  @brief  モード2でのメインタスク
 *          Bluetoothでの接続を待ち、接続された後に、モード3へ遷移する。
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
    
    //Bluetooth接続完了
    ModeTransitionToMode3();
}

/**
 *  @brief  モード3でのメインタスク
 */
void task_mode3(intptr_t unused) {

    debug_clear();

    while ((false == bt_task_running) || 
        (false == safe_task_running) ||
        (false == motor_task_running) ||
        (false == log_task_running)) {
        //各タスクをスタート
        start_bt_task();
        start_safe_task();
        start_motor_task();
        start_log_task();
    }
    
    dly_tsk(TASK_MODE3_INTERVAL);//WAIT状態に遷移：他のタスクを実行する。
    
    debug_clear();
    CheckCanContinueMode3();

    mode_task_count = 0;

    //一定時間ごとに、LCDへのデバッグ表示を更新する。
    while (can_continue_mode3) {
        mode_task_count++;


        debug_device_info();
        //LCDの更新周期：50msec(仮設定)
        dly_tsk(TASK_MODE3_INTERVAL);//WAIT状態に遷移：他のタスクを実行する。

        port_check_connectoin(); 
        CheckCanContinueMode3();
    }

    debug_clear();
    //Bluetooth接続解除
    ModeTransitionToMode4();
}

/**
 *  @brief  モード4でのメインタスク。
 *          実行中の定周期処理を停止し、再度モード1に遷移する。
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