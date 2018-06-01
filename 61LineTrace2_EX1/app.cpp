/* 61LineTrace2_EX1 
プリント２７～２８ページ改訂 
5回転チキンレース 
*/

#include <string.h>
#include <stdio.h>
#include "app.h"
#include "Port.h"
//#include "ColorSensor.h"
#include "Motor.h"

using namespace ev3api;
Motor *motorR = new Motor(PORT_A);//右モーター
Motor *motorL = new Motor(PORT_B);//左モーター

//ColorSensor *color= new ColorSensor(PORT_2);

#define ANGLE_OF_AIM 360*5 //目的の角度
#define PW_MAX1 20 //ローギヤ
#define PW_MAX2 50  //ハイギア

int Pid(float kp, float ki, float kd) { //PID制御関数
	static long diff[2] = { 0, 0};
	static float p = 0, i = 0 , d = 0 ;
	static float delta = 0.004; //周期
	static float speed = 0;
	static float integral = 0;

 //PID制御計算
	diff[0] = diff[1];
	diff[1] = ANGLE_OF_AIM - motorR->getCount();  //偏差を取得
	p = ki * diff[1];  //P制御
	integral += ((diff[1]-diff[0]) / 2.0) * delta;//偏差の集計
	i = ki * integral;	//I制御
	d = kd * (diff[1] - diff[0]) / delta;	//D制御
	speed = (p + i + d);

	char m1[32],m2[32];
	// Clear menu area
	//ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
	sprintf(m1 , "p:%3.1f    " ,p);
	ev3_lcd_draw_string(m1, 0 ,10);
	sprintf(m1 , "i:%3.1f    " ,i);
	ev3_lcd_draw_string(m1, 0 ,25);
	sprintf(m1 , "d:%3.1f    " ,d);
	ev3_lcd_draw_string(m1, 0 ,40);
	sprintf(m2 , "speed:%3.1f   " ,speed);
	ev3_lcd_draw_string(m2, 0 ,55);
	
	
	if( motorR->getCount() <45) { //ローギア
		if(speed < -PW_MAX1) speed = -PW_MAX1;		//モータパワー (-PW_MAX1～PW_MAX1)
		else if (speed >PW_MAX1) speed = PW_MAX1;
	} else { //ハイギア
		if(speed < -PW_MAX2) speed = -PW_MAX2;		//モータパワー (-PW_MAX2～PW_MAX2)
		else if (speed >PW_MAX2) speed = PW_MAX2;
	}
	//motor->setPWM(speed);
	return(speed);
}

void main_task(intptr_t unused)
{
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	//ev3_lcd_draw_string("PID PG!!", 0, 20);

	motorR->reset();
	motorL->reset();

	float speed;
	while (1)
	{
		speed = Pid(0.7 ,0.3 , 0.03);
		motorR->setPWM(speed);
		motorL->setPWM(speed);
		tslp_tsk(1);
	}
	delete (motorR);
	delete (motorL);
	//delete (color);
	ext_tsk();
}
