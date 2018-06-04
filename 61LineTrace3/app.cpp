#include <string.h>
#include <stdio.h>
#include "app.h"
#include "Port.h"
#include "ColorSensor.h"
#include "Motor.h"

using namespace ev3api;
Motor *motorR = new Motor(PORT_A);
Motor *motorL = new Motor(PORT_B);
ColorSensor *color= new ColorSensor(PORT_2);

#define MAX_LIGHT 20 	//白の光の強さ（設定値は仮の値）
#define MIN_LIGHT 2 	//黒の光の強さ（設定値は仮の値）

void Pid(float kp, float ki, float kd) { //PID制御関数
	static long diff[2] = { 0, 0};
	static float p = 0, i = 0 , d = 0 ;
	static float delta = 0.004; //周期
	static float speed = 0;
	static float integral = 0;
	static float middle_light = (MAX_LIGHT + MIN_LIGHT) / 2 ;

	diff[0] = diff[1];
	diff[1] = middle_light - color->getBrightness();
	p = kp * diff[1];  //P制御
	integral += ((diff[1]-diff[0]) / 2.0) * delta;//偏差の集計
	i = ki * integral;	//I制御
	d = kd * (diff[1] - diff[0]) / delta;	//D制御
	speed = (p + i + d);

	if(diff[1] < middle_light){		//Power20をベースに+α
		motorR->setPWM(20 + speed);
		motorL->setPWM(20);
	}else {
		motorR->setPWM(20);
		motorL->setPWM(20 + speed);
	}
	{
		char m[32];
		sprintf( m , "Light:%d" , (int) color->getBrightness());
		ev3_lcd_set_font(EV3_FONT_MEDIUM);
		ev3_lcd_draw_string( m, 10 , 40);
	}
}

void main_task(intptr_t unused)
{
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_lcd_draw_string("PID PG!!", 20, 20);

	motorR->reset();
	motorL->reset();
	while (1)
	{
		Pid(0.7 ,0.3 , 0.03);
		tslp_tsk(1);	//制御を一度OSに戻す
	}
	delete (motorR);
	delete (motorL);
	delete (color);
	ext_tsk();
}
