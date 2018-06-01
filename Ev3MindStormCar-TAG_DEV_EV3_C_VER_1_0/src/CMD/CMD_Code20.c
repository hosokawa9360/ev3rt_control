/**
 *  CMD_Code20.c
 *
 *  GetSonicSensor command source code file.
 */
#include "ev3api.h"
#include "CMD.h"

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern uint8_t rcv_msg_buf[];
extern uint8_t snd_msg_buf[];
extern uint8_t rcv_msg_len;
extern uint8_t snd_msg_len;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/
extern const sensor_port_t sensor_port[];

/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数宣言                                 */
/*****************************************************************************/
DECLARE_SUB_CMD_CODE_FUNC(cmd_code20_00);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code20_01);

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Main funtion of GetSonicSensor command.
 *          This function, command, returns ultrasonic sensor data of earch
 *          mode, distance or listen.
 */
void cmd_code20(void) {
    uint8_t res_code = CMD_ERROR_OK;
    uint8_t cmd_data_len = 0;
    uint8_t sub_cmd_code = 0;
    uint8_t sub_res_code = 0;
    uint8_t (*cmd_code20_Sub)(
        uint8_t *cmd, uint8_t cmd_len,
        uint8_t *res, uint8_t *res_len);
    
    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    cmd_data_len = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN];
    
    //Check command format.
    //Sub command code.
    if ((0x00 != sub_cmd_code) && (0x01 != sub_cmd_code)) {
        res_code = CMD_ERROR_INVALID_SUB_CODE;
        cmd_data_len = 0;
    }

    //Check command data lenght.
    if ((CMD_ERROR_OK != res_code) && (0x00 != cmd_data_len)) {//Avoid overwriting error information.
        res_code = CMD_ERROR_CMD_DATA_LEN;
        cmd_data_len = 0;
    }

    if (CMD_ERROR_OK == res_code) {
        /*
         *  If the command data is valud, run operation corresponding to
         *  the sub command code.
         */
        switch (sub_cmd_code) {
        case 0x00: cmd_code20_Sub = cmd_code20_00; break;
        case 0x01: cmd_code20_Sub = cmd_code20_01; break;
        default:
            cmd_code20_Sub = NULL;
            break;
        }
        
        if (NULL != cmd_code20_Sub) {
            res_code = cmd_code20_Sub(
                (uint8_t *)(&(rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_TOP])),
                (uint8_t)rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN],
                (uint8_t *)(&(snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP])),
                (uint8_t *)(&cmd_data_len));
            sub_res_code = sub_cmd_code;
        } else {
            res_code = CMD_ERROR_INVALID_SUB_CODE;
            sub_res_code = 0xFF;
            cmd_data_len = 0;
        }
    }

    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x21;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = cmd_data_len;
    snd_msg_len = 4 + cmd_data_len;
}

/**
 *  @brief  Main function of command:0x20/sub command:0x00
 *
 *  @param[in] cmd Pointer to data part in received data.
 *  @param  cmd_len Length of data part in received data.
 *  @param[in, out] res Pointer to data part in received data.
 *  @param[in, out] res_len Pointer to length of response data.
 *
 *  @return Result of setting up response data.
 */
static uint8_t cmd_code20_00(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    uint8_t sensor_num;
    uint8_t data_len;
    int16_t sensor_value = 0;
    int sensor_index = 0;
    uint8_t *sensor_num_ptr;
    sensor_port_t port = TNUM_SENSOR_PORT;
    sensor_type_t type = TNUM_SENSOR_TYPE;

    sensor_num_ptr = res;
    res++;
    
    sensor_num = 0;
    data_len = 1;//Set the data size for the number of port device connected in advance.
    for (sensor_index = 0; sensor_index < (int)TNUM_SENSOR_PORT; sensor_index++) {
        port = sensor_port[sensor_index];
        type = ev3_sensor_get_type(port);
        if (ULTRASONIC_SENSOR == type) {
            sensor_value = ev3_ultrasonic_sensor_get_distance(port);
            *res = (uint8_t)port;
            res++;
            *res = (uint8_t)(sensor_value & 0x00FF);//Lower byte.
            res++;
            *res = (uint8_t)((((uint16_t)sensor_value) & 0xFF00) >> 8);//Upper byte.
            res++;
            sensor_num++;
            data_len += 3;
        }
    }
    *res_len = data_len;
    *sensor_num_ptr = sensor_num;
    
    return 0;
}

/**
 *  @brief  Main function of command:0x20/sub command:0x01
 *
 *  @param[in] cmd Pointer to data part in received data.
 *  @param  cmd_len Length of data part in received data.
 *  @param[in, out] res Pointer to data part in received data.
 *  @param[in, out] res_len Pointer to length of response data.
 *
 *  @return Result of setting up response data.
 */
static uint8_t cmd_code20_01(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    uint8_t res_code = CMD_ERROR_OK;
    uint8_t sensor_num = 0;
    uint8_t data_len = 0;
    bool_t is_listen = false;
    int sensor_index = 0;
    uint8_t *sensor_num_ptr;
    
    sensor_port_t port = TNUM_SENSOR_PORT;
    sensor_type_t type = TNUM_SENSOR_TYPE;
    
    sensor_num_ptr = res;
    res++;
    
    sensor_num = 0;
    data_len = 1;//Set the data size for the number of port device connected in advance.
    for (sensor_index = 0; sensor_index < (int)TNUM_SENSOR_PORT; sensor_index++) {
        port = sensor_port[sensor_index];
        type = ev3_sensor_get_type(port);
        if (ULTRASONIC_SENSOR == type) {
            is_listen = ev3_ultrasonic_sensor_listen(port);
            
            *res = (uint8_t)port;
            res++;
            
            if (true == is_listen) {
                *res = 0x01;
            } else {
                *res = 0x00;
            }
            res++;

            sensor_num++;
            data_len += 2;
        }
    }
    *res_len = data_len;
    *sensor_num_ptr = sensor_num;
    res_code = CMD_ERROR_OK;

    return res_code;
}
