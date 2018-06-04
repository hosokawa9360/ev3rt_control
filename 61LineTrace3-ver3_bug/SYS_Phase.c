/**
 *  Sys_Phase.c
 *
 *  Change Phase
 */
#include "ev3api.h"
#include "app.h"
#include "SYS_Phase.h"

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
const uint8_t APP_PHASE_PHASE1 = 0x01;
const uint8_t APP_PHASE_PHASE2 = 0x02;
const uint8_t APP_PHASE_PHASE3 = 0x03;
const uint8_t APP_PHASE_PHASE4 = 0x04;

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int cur_phase;
bool_t IsPhase1Running;
bool_t IsPhase2Running;
bool_t IsPhase3Running;
bool_t IsPhase4Running;

bool_t can_continue_Phase3;

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
 *  @brief  フェーズ1へ、フェーズを遷移させる。
 */
void PhaseTransitionToPhase1(void) {
    cur_phase = 1;
    act_tsk(PHASE_1_TASK);
    
    IsPhase1Running = true;
    IsPhase2Running = false;
    IsPhase3Running = false;
    IsPhase4Running = false;
}

/**
 *  @brief  フェーズ1へ、フェーズを遷移させる。
 */
void PhaseTransitionToPhase2(void) {
    cur_phase = 2;

    act_tsk(PHASE_2_TASK);
    
    IsPhase1Running = false;
    IsPhase2Running = true;
    IsPhase3Running = false;
    IsPhase4Running = false;
}

/**
 *  @brief  モード3へ、モードを遷移させる。
 */
void PhaseTransitionToPhase3(void) {
    cur_phase = 3;
    can_continue_Phase3 = true;

    act_tsk(PHASE_3_TASK);

    IsPhase1Running = false;
    IsPhase2Running = false;
    IsPhase3Running = true;
    IsPhase4Running = false;
}

/**
 *  @brief  モード3を継続可能か否かの判定
 */
void CheckCanContinuePhase3(void) {
    if (is_connect_bt) {
        can_continue_Phase3 = true;
    } else {
        can_continue_Phase3 = false;
    }
}

/**
 *  @brief  モード4へ、モードを遷移させる。
 */
void PhaseTransitionToPhase4() {
    cur_phase = 4;

    act_tsk(PHASE_4_TASK);

    IsPhase1Running = false;
    IsPhase2Running = false;
    IsPhase3Running = false;
    IsPhase4Running = true;
}
