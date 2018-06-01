/**
 *  judge_dist_safe_state
 *
 *  Judge whether MyCar has safe distance between distance and obstacle in 
 *  front.
 */
#include "ev3api.h"

/*****************************************************************************/
/*                                  •Ï”’è‹`                                 */
/*****************************************************************************/
int8_t distance_safe_state;
int8_t distance_safe_state_prev;
bool_t distance_safe_state_change;

/*****************************************************************************/
/*                               Ã“I•Ï”’è‹`                                */
/*****************************************************************************/


/*****************************************************************************/
/*                                ŠO•”•Ï”éŒ¾                               */
/*****************************************************************************/
extern int16_t distance_average_value;

/*****************************************************************************/
/*                                  ’è”’è‹`                                 */
/*****************************************************************************/
const int8_t CAR_SAFE_STATE_SAFE = 0;
const int8_t CAR_SAFE_STATE_ATTN = 1;
const int8_t CAR_SAFE_STATE_DANG = 2;
const int8_t CAR_SAFE_STATE_STOP = 3;

/*****************************************************************************/
/*                               Ã“I’è”’è‹`                                */
/*****************************************************************************/
static const int16_t CAR_SAFE_STATE_SAFE_ATTN_BORDER = 45;  //ˆÀ‘S¨Œx
static const int16_t CAR_SAFE_STATE_ATTN_DANG_BORDER = 35;  //Œx¨ŠëŒ¯
static const int16_t CAR_SAFE_STATE_DANG_STOP_BORDER = 25;  //ŠëŒ¯¨’âŽ~
static const int16_t CAR_SAFE_STATE_ATTN_SAFE_BORDER = 40;  //Œx¨ˆÀ‘S
static const int16_t CAR_SAFE_STATE_DANG_ATTN_BORDER = 30;  //ŠëŒ¯¨Œx
static const int16_t CAR_SAFE_STATE_STOP_DANG_BORDER = 20;  //’âŽ~¨ŠëŒ¯

/*****************************************************************************/
/*                                  ŠÖ”ŽÀ‘•                                 */
/*****************************************************************************/
/**
 *  @brief  Judge the safe state from distance read from ultrasonic sensor.
 */
void judge_dist_safe(void) {
    int16_t distance_average_value_tmp;
    
    //Latch latest value.
    distance_average_value_tmp = distance_average_value;

    if (CAR_SAFE_STATE_SAFE == distance_safe_state) {
        if (CAR_SAFE_STATE_SAFE_ATTN_BORDER > distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_ATTN;
        }
    } else if (CAR_SAFE_STATE_ATTN == distance_safe_state) {
        if (CAR_SAFE_STATE_ATTN_DANG_BORDER > distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_DANG;
        }
        if (CAR_SAFE_STATE_ATTN_SAFE_BORDER < distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_SAFE;
        }
    } else if (CAR_SAFE_STATE_DANG == distance_safe_state) {
        if (CAR_SAFE_STATE_DANG_STOP_BORDER > distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_STOP;
        }
        if (CAR_SAFE_STATE_DANG_ATTN_BORDER < distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_ATTN;
        }
    } else if (CAR_SAFE_STATE_STOP == distance_safe_state) {
        if (CAR_SAFE_STATE_STOP_DANG_BORDER < distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_DANG;
        }
    }
}

/**
 *  @brief  Check the change and udate safe state.
 */
void judge_distance_safe_change(void) {
    int16_t distance_average_value_tmp;
    
    //Latch latest value.
    distance_average_value_tmp = distance_average_value;

    if (distance_average_value_tmp == distance_safe_state_prev) {
        distance_safe_state_change = true;
    } else {
        distance_safe_state_change = false;
    }

    distance_safe_state_prev = distance_average_value_tmp;
}

/**
 *  @brief  Initialize the safe state.
 */
void init_dist_safe(void) {
    distance_safe_state = CAR_SAFE_STATE_SAFE;
    distance_safe_state_prev = CAR_SAFE_STATE_SAFE;
    distance_safe_state_change = false;

}
