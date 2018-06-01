/**
 *  Common data for command data and macros.
 */
#pragma once

#define DECLARE_SUB_CMD_CODE_FUNC(func_name)    \
    static uint8_t func_name(uint8_t*, uint8_t, uint8_t*, uint8_t*)

//Macros for error code, information.
#define CMD_ERROR_OK                (0x00)
#define CMD_ERROR_FATAL             (0xFF)
#define CMD_ERROR_CMD_DATA_LEN      (0xFE)
#define CMD_ERROR_INVALID_SUB_CODE  (0xFD)
#define CMD_ERROR_INVALID_CMD_DATA  (0xFC)
#define CMD_WARN_NO_DEVICE_CONN     (0xEF)//デバイス未接続エラー

//Enumlator of command data fomrat.
enum {
    CMD_DATA_FORMAT_INDEX_CMD_CODE = 0,
    CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE,
    CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN,
    CMD_DATA_FORMAT_INDEX_CMD_DATA_TOP,
};

//Enumlator of response data format.
enum {
    RES_DATA_FORMAT_INDEX_RES_CODE = 0,
    RES_DATA_FORMAT_INDEX_RES_SUB_CODE,
    RES_DATA_FORMAT_INDEX_RES_CMD_RSLT,
    RES_DATA_FORMAT_INDEX_RES_DATA_LEN,
    RES_DATA_FORMAT_INDEX_RES_DATA_TOP,
};
