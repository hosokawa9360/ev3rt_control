#pragma once

#include "ev3api.h"

extern void init_buff(int size, char *buff, char val);
extern int limit_int(int value, int min, int max);

/**
 *  @macro
 *  バッファーの初期化を行う。
 *  バッファーのインデックスを示す変数を、第1引数に指定する。
 *  valで、初期値(初期化する値)を指定する。
 */
#define INIT_BUF_VAL(size, buff, val)    init_buff(size, buff, val)

/**
 *  @macro
 *  バッファーの初期化を行う。
 *  バッファーのインデックスを示す変数を、第1引数に指定する。
 *  バッファーは、全て「0」で初期化する。
 */
#define INIT_BUF(size, buff) INIT_BUF_VAL(size, buff, 0)
