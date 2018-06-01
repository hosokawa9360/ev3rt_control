#pragma once

#include "ev3api.h"

/*
 *  デバイスとポートの設定
 */
/**
 *  入力ポートチャンネルの設定(2～4)
 *  ※ポート1は、UARTポートになっており、PCなどのデバイスとシリアル通信を
 *    するために使用する可能性があるため。
 */
#define SONIC_SENSOR_PORT   (EV3_PORT_3)
#define TOUCH_SENSOR_PORT   (EV3_PORT_2)
#define COLOR_SENSOR_PORT   (EV3_PORT_4)
#define GYRO_SENSOR_PORT    (EV3_PORT_1)

/**
 *  出力ポートチャンネルの設定(A～D)
 */
#define RIGHT_MOTOR_PORT    (EV3_PORT_D)
#define LTYPE_MOTOR_PORT    (EV3_PORT_B)
#define LEFT_MOTOR_PORT     (EV3_PORT_A)
