#include "ev3api.h"
#include "app.h"
#include <unistd.h>
#include <ctype.h>
#include <string.h>

void task1(intptr_t unused) {
	char m[32];
	static int count = 0;
	while(1) {
	sprintf(m , "Task1:%3d" ,count++);
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
    ev3_lcd_draw_string(m, 20 ,20);
	tslp_tsk(100);
	}
   ext_tsk();
}

void task2(intptr_t unused) {
	char m[32];
	static int count = 0;
	while(1) {
	sprintf(m , "Task2:%3d" ,count++);
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
   ev3_lcd_draw_string(m, 20 ,40);
	tslp_tsk(100);
	}
   //ext_tsk();
}


