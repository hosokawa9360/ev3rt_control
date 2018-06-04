#include <string.h>
#include <stdio.h>
#include "app.h"
#include "Port.h"
#include "ColorSensor.h"
#include "Motor.h"
#include "TouchSensor.h"

using namespace ev3api;
Motor *motorR = new Motor(PORT_A);
Motor *motorL = new Motor(PORT_B);
ColorSensor *color = new ColorSensor(PORT_2);
TouchSensor *touch = new TouchSensor(PORT_1);

#define BASE_SPEED 20 //ベーススピード

int white_Brightness;
int black_Brightness;
float middle_light;

void init_Pid(void);
void Pid(float kp, float ki, float kd);
void main_task(intptr_t unused);

void init_Pid(void)
{
	char m[32];

	ev3_lcd_set_font(EV3_FONT_MEDIUM);

	ev3_lcd_draw_string("Push", 10, 10);
	while (touch->isPressed() == false){}
	tslp_tsk(1500);

	while (touch->isPressed() == false)
	{
		white_Brightness = color->getBrightness();
		sprintf(m, "white:%2d", white_Brightness);
		ev3_lcd_draw_string(m, 20, 10);
	}
	tslp_tsk(1500);

	while (touch->isPressed() == false)
	{
		black_Brightness = color->getBrightness();
		sprintf(m, "black:%2d", black_Brightness);
		ev3_lcd_draw_string(m, 10, 25);
	}
	tslp_tsk(1500);
	middle_light = (white_Brightness + black_Brightness) / 2.0;
	sprintf(m, "middle:%3.1lf", middle_light);
	ev3_lcd_draw_string(m, 10, 40);
}

void Pid(float kp, float ki, float kd)
{ //PID制御関数
	static long diff[2] = {0, 0};
	static float p = 0, i = 0, d = 0;
	static float delta = 0.004; //周期
	static float speed = 0;
	static float integral = 0;
	char m[32];

	diff[0] = diff[1];
	diff[1] = middle_light - color->getBrightness();
	p = kp * diff[1];								 //P制御
	integral += ((diff[1] - diff[0]) / 2.0) * delta; //偏差の集計
	i = ki * integral;								 //I制御
	d = kd * (diff[1] - diff[0]) / delta;			 //D制御
	speed = (p + i + d);

	ev3_lcd_set_font(EV3_FONT_MEDIUM);

	if (diff[1] < middle_light)
	{ //Power　BASE_SPEED　をベースに+α
		sprintf(m, "B:%d RS:%2d     ", (int)color->getBrightness(), (int)speed);
		ev3_lcd_draw_string(m, 10, 55);
		motorR->setPWM(BASE_SPEED + speed);
		motorL->setPWM(BASE_SPEED);
	}
	else
	{
		sprintf(m, "B:%d LS:%2d     ", (int)color->getBrightness(), (int)speed);
		ev3_lcd_draw_string(m, 10, 55);
		motorR->setPWM(BASE_SPEED);
		motorL->setPWM(BASE_SPEED + speed);
	}
}

void main_task(intptr_t unused)
{
	init_Pid();

	motorR->reset();
	motorL->reset();
	while (touch->isPressed() == false)
	{
		ev3_lcd_draw_string("Ready!", 10, 55);
	};
	tslp_tsk(1000);
	ev3_lcd_draw_string("Go!       ", 10, 55);
	while (touch->isPressed() == false)
	{
		Pid(0.7, 0.3, 0.03);
		tslp_tsk(1); //制御を一度OSに戻す
	}
	ev3_lcd_draw_string("Stop!       ", 10, 55);
	delete (motorR);
	delete (motorL);
	delete (color);
	ext_tsk();
}
