#include <string.h>
#include <stdio.h>
#include "app.h"
#include "Port.h"
#include "Motor.h"
#include "ColorSensor.h"
#include "TouchSensor.h"
#include "Pid.h"

using namespace ev3api;

#define BASE_SPEED 10 //ベーススピード

int white_Brightness;
int black_Brightness;
float middle_light;

Motor *motorR = new Motor(PORT_A);
Motor *motorL = new Motor(PORT_B);
ColorSensor *color = new ColorSensor(PORT_2);
TouchSensor *touch = new TouchSensor(PORT_1);
//Pid *pid = new Pid();
Pid pid;
void main_task(intptr_t unused)
{
	//pid->setPid(0.5, 0.3, 0.03);
	pid.setPid(0.5, 0.3, 0.03);
	//pid->InitPid();

	motorR->reset();
	motorL->reset();
	while (touch->isPressed() == false)
	{
		ev3_lcd_draw_string("Ready!", 10, 55);
	};
	tslp_tsk(1000);
	ev3_lcd_draw_string("Go!       ", 10, 55);
	int speed;
	while (touch->isPressed() == false)
	{
		speed = pid.CalcPid();
		if (pid.getDirection() == 1)
		{ //1:左回転 2:右回転
			motorR->setPWM(BASE_SPEED + speed);
			motorL->setPWM(BASE_SPEED);
		}
		else if (pid.getDirection() == 2)
		{
			motorR->setPWM(BASE_SPEED);
			motorL->setPWM(BASE_SPEED + speed);
		}
		tslp_tsk(1); //制御を一度OSに戻す
	}
	ev3_lcd_draw_string("Stop!       ", 10, 55);
	delete (motorR);
	delete (motorL);
	delete (color);
	ext_tsk();
}
