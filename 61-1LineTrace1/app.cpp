#include <string.h>
#include "app.h"
#include "Port.h"
#include "ColorSensor.h"
#include "Motor.h"
using namespace ev3api;
Motor *motorR, *motorL;
ColorSensor *color;

void main_task(intptr_t unused)
{
	int w;
	char m[32];

	color = new ColorSensor(PORT_2);
	motorL = new Motor(PORT_A);
	motorR = new Motor(PORT_B);

	motorR->reset();
	motorL->reset();
	while (1)
	{
		w = color->getBrightness();
		sprintf(m, "ColorSensor:%4d", w);
		ev3_lcd_draw_string(m, 20, 20);
		
		if (w < 12)
		{
			motorR->setPWM(40);
			motorL->setPWM(0);
		}
		else
		{
			motorR->setPWM(0);
			motorL->setPWM(40);
		}

	}
	delete (motorL);
	delete (motorR);
	delete (color);
	ext_tsk();
}
