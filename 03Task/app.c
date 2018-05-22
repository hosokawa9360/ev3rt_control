#include "ev3api.h"
#include "app.h"

void task_cyc1(intptr_t unused)
{
	act_tsk(TASK1); //TASK1の実行
}
void task1(intptr_t unused)
{
	char m[32];
	static int count = 0;
	sprintf(m, "Task1:%3d", count++);
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_lcd_draw_string(m, 20, 20);
	ext_tsk(); //タスクを待ち状態にする
}
void task_cyc2(intptr_t unused)
{
	act_tsk(TASK2); //TASK1の実行
}
void task2(intptr_t unused)
{
	char m[32];
	static int count = 0;
	sprintf(m, "Task2:%3d", count++);
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_lcd_draw_string(m, 20, 40);
	ext_tsk(); //タスクを待ち状態にする
}
