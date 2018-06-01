#include <string.h>
#include <stdio.h>
#include "app.h"
#include "Port.h"
#include "ColorSensor.h"
#include "Motor.h"

using namespace ev3api;
Motor *motor = new Motor(PORT_A);
ColorSensor *color= new ColorSensor(PORT_2);

#define ANGLE_OF_AIM 90 //目的の角度

int Pid(float kp, float ki, float kd) { //PID制御関数
	static long diff[2] = { 0, 0};
	static float p = 0, i = 0 , d = 0 ;
	static float delta = 0.004; //周期
	static float speed = 0;
	static float integral = 0;

 //PID制御計算
	diff[0] = diff[1];
	diff[1] = ANGLE_OF_AIM - motor->getCount();  //偏差を取得
	
	p = ki * integral;  //P制御
	
	integral += ((diff[1]-diff[0]) / 2.0) * delta;//偏差の集計
	i = ki * integral;	//I制御
	d = kd * (diff[1] - diff[0]) / delta;	//D制御
	speed = (p + i + d);

	if(speed < -100) speed = -100;		//モータパワー (-100～100)
	else if (speed >100) speed = 100;

	//motor->setPWM(speed);
	return(speed);
}

void main_task(intptr_t unused)
{
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_lcd_draw_string("PID PG!!", 20, 20);

	motor->reset();
	float speed;

	while (1)
	{
		speed = Pid(0.7 ,0.3 , 0.03);
		motor->setPWM(speed);
		tslp_tsk(1);
	}
	delete (motor);
	delete (color);
	ext_tsk();
}
