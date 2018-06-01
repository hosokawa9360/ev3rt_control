#pragma once

extern void calc_motor_power(void);

//PID����̂��߂̍\����
typedef struct _power_t {
    int target;
    int target_prev;
    int current;
    int diff;
    int integral;
    int reset_count;
} power_t;

