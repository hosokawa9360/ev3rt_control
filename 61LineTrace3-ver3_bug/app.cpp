#include "ev3api.h"
#include "app.h"
#include <unistd.h>
#include <ctype.h>
#include <string.h>

const motor_port_t motor_port[TNUM_MOTOR_PORT] = {
    EV3_PORT_A,
    EV3_PORT_B,
    EV3_PORT_C,
    EV3_PORT_D };

const sensor_port_t sensor_port[TNUM_SENSOR_PORT] = {
    EV3_PORT_1,
    EV3_PORT_2,
    EV3_PORT_3,
    EV3_PORT_4 };

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/

void main_task(intptr_t unused) {}
