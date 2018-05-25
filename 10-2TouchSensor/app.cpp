#include "ev3api.h"
#include "app.h"
#include "Port.h"
#include "TouchSensor.h"

using namespace ev3api;

TouchSensor *touch;

void main_task(intptr_t unused)
{
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_lcd_draw_string("Touch PG!!", 20, 20);
	touch = new TouchSensor(PORT_1);

	while (touch->isPressed() == false);
	ev3_lcd_draw_string("Stop!!", 20, 60);
	delete (touch);
	ext_tsk();
}
