#pragma once

#include "ev3api.h"

extern void init_buff(int size, char *buff, char val);
extern int limit_int(int value, int min, int max);

/**
 *  @macro
 *  �o�b�t�@�[�̏��������s���B
 *  �o�b�t�@�[�̃C���f�b�N�X�������ϐ����A��1�����Ɏw�肷��B
 *  val�ŁA�����l(����������l)���w�肷��B
 */
#define INIT_BUF_VAL(size, buff, val)    init_buff(size, buff, val)

/**
 *  @macro
 *  �o�b�t�@�[�̏��������s���B
 *  �o�b�t�@�[�̃C���f�b�N�X�������ϐ����A��1�����Ɏw�肷��B
 *  �o�b�t�@�[�́A�S�āu0�v�ŏ���������B
 */
#define INIT_BUF(size, buff) INIT_BUF_VAL(size, buff, 0)
