#include "ev3api.h"
#include "app.h"
#include <unistd.h>
#include <ctype.h>
#include <string.h>

void task_cyc1(intptr_t unused) {
	char m[32];
	static int count = 0;

	sprintf(m , "task_cyc1:%3d" ,count++);
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
    ev3_lcd_draw_string(m, 20 ,20);
    ext_tsk();
}

void task_cyc2(intptr_t unused) {
	char m[32];
	static int count = 0;

	sprintf(m , "task_cyc2:%3d" ,count++);
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
    ev3_lcd_draw_string(m, 20 ,40);
    ext_tsk();
}
