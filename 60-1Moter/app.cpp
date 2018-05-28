#include<string.h>
#include "app.h"
#include "Port.h"
#include "TouchSensor.h"
#include "Motor.h"
using namespace ev3api;

TouchSensor *touch;
Motor *motor;

void main_task(intptr_t unused)
{
	touch = new TouchSensor(PORT_1);
	motor = new Motor(PORT_A);
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_lcd_draw_string("Motor PG!!", 20, 20);

	motor->reset();
	motor->setPWM(10);
	
	while (!touch->isPressed());
	
	motor->stop();

	delete(touch);
	delete(motor);

	ext_tsk();
}
