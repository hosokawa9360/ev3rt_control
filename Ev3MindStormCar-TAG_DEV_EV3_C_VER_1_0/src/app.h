#pragma once

#include "ev3api.h"

/*
 *  �A�v���̃o�[�W����
 */
#define APP_MAJOR_VERSION       (1)
#define APP_MINOR_VERSION       (0)

/*
 *  �^�[�Q�b�g�ˑ��̒�`
 */
#include "target_test.h"

/*
 *  �e�^�X�N�̗D��x�̒�`
 */
#define MAIN_PRIORITY   5       /* ���C���^�X�N�̗D��x */
                                /* HIGH_PRIORITY��荂�����邱�� */

#define HIGH_PRIORITY   9       /* ���s���s�����^�X�N�̗D��x */
#define MID_PRIORITY    10
#define LOW_PRIORITY    11

/*
 *  �^�[�Q�b�g�Ɉˑ�����\���̂���萔�̒�`
 */
#ifndef STACK_SIZE
#define STACK_SIZE      4096        /* �^�X�N�̃X�^�b�N�T�C�Y */
#endif /* STACK_SIZE */

/*
 *  �֐��̃v���g�^�C�v�錾
 */
#ifndef TOPPERS_MACRO_ONLY

#include <stdio.h>
extern void main_task(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */
