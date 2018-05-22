#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "ev3api.h"

#ifndef TOPPERS_MACRO_ONLY

extern void	task_cyc1(intptr_t exinf);
extern void	task_cyc2(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif	