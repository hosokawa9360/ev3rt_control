#pragma once
#define task_phase3_INTERVAL (20)    //50msec
#ifdef __cplusplus
extern "C" {
#endif
#include "ev3api.h"
#ifndef TOPPERS_MACRO_ONLY
//extern void	main_task(intptr_t exinf);
extern void task_phase1(intptr_t unused);
extern void task_phase2(intptr_t unused);
extern void task_phase3(intptr_t unused);
extern void task_phase4(intptr_t unused);
#endif /* TOPPERS_MACRO_ONLY */
#ifdef __cplusplus
}
#endif	