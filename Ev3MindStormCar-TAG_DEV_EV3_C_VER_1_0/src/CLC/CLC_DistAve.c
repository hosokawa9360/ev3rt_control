/**
 *  dist_remove_noise
 *
 *  Remove noise from ultrasoni sensor valus. To do so, a distance used to
 *  judge SAFETY_STATE is calcurated from the moving averate of the past 3
 *  times period.
 */
#include "ev3api.h"

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int16_t distance_average_value;


/*****************************************************************************/
/*                               静的変数定義                                */
/*****************************************************************************/
#define DISTANCE_AVERAGE_BUF_SIZE   (3)
static int16_t distance_average_buf[DISTANCE_AVERAGE_BUF_SIZE];


/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern int16_t distance_sensor_value;

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
 *  @brief  Calcurate average value of distance.
 */
void calc_distance_average(void) {
    int index;
    int32_t distance_sum = 0;

    //Step forward buffer value and set latest valuet to buffer.
    for (index = 0; index < DISTANCE_AVERAGE_BUF_SIZE - 1; index++) {
        distance_average_buf[index] = distance_average_buf[index + 1];
    }
    distance_average_buf[DISTANCE_AVERAGE_BUF_SIZE - 1] =
        distance_sensor_value;

    for (index = 0; index < DISTANCE_AVERAGE_BUF_SIZE; index++) {
        distance_sum += (int32_t)distance_average_buf[index];
    }

    distance_average_value =
        (int16_t)(distance_sum / DISTANCE_AVERAGE_BUF_SIZE);
}

/**
 *  @brief  Initialize distance average buffer.
 */
void init_distance_averate(void) {
    int index;

    for (index = 0; index < DISTANCE_AVERAGE_BUF_SIZE; index++) {
        distance_average_buf[index] = 0;
    }
}