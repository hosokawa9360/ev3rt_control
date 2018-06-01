/**
 *  Log_Sensor.c
 *
 *  Write parameter read from sensor.
 */
#include "ev3api.h"

/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
FILE *sensor_log = NULL;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/
static const char *sensor_log_file_name = "sensor_log.csv";
static const char *sensor_log_format = "DST,AVE\n";
//Now the time, only the distance read from ultrasonic sensor.

/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern int16_t distance_sensor_value;
extern int16_t distance_average_value;

/*****************************************************************************/
/*                                �O���萔��`                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �O���֐�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/
/**
 *  @brief  Open logging file of ultrasonic sensor.
 */
void init_sensor_log(void)
{
    sensor_log = fopen(sensor_log_file_name, "a");
    if (NULL != sensor_log) {
        fprintf(sensor_log, (const char *)sensor_log_format);
    }
}

/**
 *  @brief  Finalize logging file of ultrasonic sensor.
 */
void fin_sensor_log(void)
{
    if (NULL != sensor_log) { fclose(sensor_log); }
}

/**
 *  @brief  Logging sensor data, ultrasonic sensor, and the average value.
 */
void logging_sensor(void)
{
    if (NULL != sensor_log) {
        fprintf(sensor_log,
            "%d,%d\n",
            distance_sensor_value, distance_average_value);
    }
}