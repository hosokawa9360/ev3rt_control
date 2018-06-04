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
ColorSensor *color= new ColorSensor(PORT_2);
TouchSensor *touch= new TouchSensor(PORT_1);

#define MAX_LIGHT 20 	//白の光の強さ（設定値は仮の値）
#define MIN_LIGHT 2 	//黒の光の強さ（設定値は仮の値）
#define BASE_SPEED 0   //ベーススピード

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

	char m[32];
	if(diff[1] < middle_light){		//Power　BASE_SPEED　をベースに+α
		sprintf( m , "motorR Go L:%2d" , (int) color->getBrightness());
		motorR->setPWM(BASE_SPEED + speed);
		motorL->setPWM(BASE_SPEED);
	}else {
		sprintf( m , "motorL Go L:%2d " , (int) color->getBrightness());
		motorR->setPWM(BASE_SPEED);
		motorL->setPWM(BASE_SPEED + speed);
	}
	{
		ev3_lcd_set_font(EV3_FONT_MEDIUM);
		ev3_lcd_draw_string( m, 10 , 40);
	}
}

void main_task(intptr_t unused)
{
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	char m[32];
	sprintf( m , "middle Light :%d" , (MAX_LIGHT + MIN_LIGHT) / 2);
	
	ev3_lcd_draw_string( m , 20, 20);

	motorR->reset();
	motorL->reset();
	while (touch->isPressed() == false)
	{
		Pid(0.7 ,0.3 , 0.03);
		tslp_tsk(1);	//制御を一度OSに戻す
	}
	delete (motorR);
	delete (motorL);
	delete (color);
	ext_tsk();
}
