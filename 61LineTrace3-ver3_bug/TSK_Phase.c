/**
 *  TSK_Mode.c
 *
 *  Task of each mode.
 */
#include "ev3api.h"
#include "app.h"

#include <string.h>
#include <stdio.h>
#include "Port.h"
#include "ColorSensor.h"
#include "TouchSensor.h"
#include "Motor.h"
#include "Pid.h"
#include "TSK_Phase.h"
#include "SYS_Phase.h"

using namespace ev3api;
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

extern void port_check_connectoin();

extern void CheckCanContinueMode3(void);
extern void wait_btconnect();

extern void init_Pid(void);
extern void Pid(float kp, float ki, float kd);
/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/
extern const uint8_t APP_MODE_MODE1;
extern const uint8_t APP_MODE_MODE2;
extern const uint8_t APP_MODE_MODE3;
extern const uint8_t APP_MODE_MODE4;

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int mode_task_count;
TouchSensor *touch;
ColorSensor *color;
Motor *motorR;
Motor *motorL;
/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/

/*****************************************************************************/
/*                                  関数宣言                                 */
/*****************************************************************************/
void task_phase1(intptr_t unused);
void task_phase2(intptr_t unused);
void task_phase3(intptr_t unused);
void task_phase4(intptr_t unused);
/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/

/**
 *  @brief 　フェーズ1でのメインタスク
 *          各種初期化を行い、その後モード2に遷移させる。
 */
void task_phase1(intptr_t unused)
{
    *touch = new TouchSensor(PORT_1);
    *color = new ColorSensor(PORT_2);
    *motorR = new Motor(PORT_A);
    *motorL = new Motor(PORT_B);
    init_pid();

    //各種初期化処理完了→フェーズ2に遷移
    PhaseTransitionToPhase2();
}

/**
 *  @brief  フェーズ2でのメインタスク
 *          Bluetoothでの接続を待ち、接続された後に、モード3へ遷移する。
 */
void task_phase2(intptr_t unused)
{
    //dumy タッチボタンを押した->Bluetooth接続完了
    while (touch->isPressed() == false)
    {
    }
     ev3_lcd_draw_string("Go!", 20, 20);
   
    //Bluetooth接続完了
    PhaseTransitionToPhase3();
}

/**
 *  @brief  フェーズ3でのメインタスク
 */
void task_phase3(intptr_t unused)
{

    ev3_lcd_set_font(EV3_FONT_MEDIUM);
    char m[32];

    ev3_lcd_draw_string(m, 20, 20);

    motorR->reset();
    motorL->reset();
    while (touch->isPressed() == false)
    {
        Pid(0.7, 0.3, 0.03);
        tslp_tsk(1); //制御を一度OSに戻す
    }
    delete (motorR);
    delete (motorL);
    delete (color);
    ext_tsk();
    /*
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
    */
    PhaseTransitionToPhase4();
}

/**
 *  @brief  フェーズ4でのメインタスク。
 *          実行中の定周期処理を停止し、再度モード1に遷移する。
 */
void task_phase4(intptr_t unused)
{
    /*
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
*/
    PhaseTransitionToPhase1();
}