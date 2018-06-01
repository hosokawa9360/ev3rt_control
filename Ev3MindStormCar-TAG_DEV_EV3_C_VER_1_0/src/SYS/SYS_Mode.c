/**
 *  Sys_Mode.c
 *
 *  Change Mode
 */
#include "ev3api.h"
#include "app.h"

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern bool_t is_connect_bt;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/
const uint8_t APP_MODE_MODE1 = 0x01;
const uint8_t APP_MODE_MODE2 = 0x02;
const uint8_t APP_MODE_MODE3 = 0x03;
const uint8_t APP_MODE_MODe4 = 0x04;

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int cur_mode;
bool_t can_continue_mode3;
bool_t IsMode1Running;
bool_t IsMode2Running;
bool_t IsMode3Running;
bool_t IsMode4Running;

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
 *  @brief  モード1へ、モードを遷移させる。
 */
void ModeTransitionToMode1(void) {
    cur_mode = 1;
    act_tsk(MODE_1_TASK);
    
    IsMode1Running = true;
    IsMode2Running = false;
    IsMode3Running = false;
    IsMode4Running = false;
}

/**
 *  @brief  モード2へ、モードを遷移させる。
 */
void ModeTransitionToMode2(void) {
    cur_mode = 2;

    act_tsk(MODE_2_TASK);
    
    IsMode1Running = false;
    IsMode2Running = true;
    IsMode3Running = false;
    IsMode4Running = false;
}

/**
 *  @brief  モード3へ、モードを遷移させる。
 */
void ModeTransitionToMode3(void) {
    cur_mode = 3;
    can_continue_mode3 = true;

    act_tsk(MODE_3_TASK);

    IsMode1Running = false;
    IsMode2Running = false;
    IsMode3Running = true;
    IsMode4Running = false;
}

/**
 *  @brief  モード3を継続可能か否かの判定
 */
void CheckCanContinueMode3(void) {
    if (is_connect_bt) {
        can_continue_mode3 = true;
    } else {
        can_continue_mode3 = false;
    }
}

/**
 *  @brief  モード4へ、モードを遷移させる。
 */
void ModeTransitionToMode4() {
    cur_mode = 4;

    act_tsk(MODE_4_TASK);

    IsMode1Running = false;
    IsMode2Running = false;
    IsMode3Running = false;
    IsMode4Running = true;
}
