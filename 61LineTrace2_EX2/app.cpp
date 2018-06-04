// 61LineTrace2_EX2
// ロギングプログラム実装

#include <string.h>
#include <stdio.h>
#include "app.h"
#include "Port.h"
#include "ColorSensor.h"
#include "Motor.h"

using namespace ev3api;
Motor *motor = new Motor(PORT_A);
ColorSensor *color = new ColorSensor(PORT_2);

#define ANGLE_OF_AIM 90 //目的の角度

FILE *motor_log = NULL;
FILE *bluetooth_log = NULL;
static const char *motor_log_file_name = "motor_log.csv";
char msg[32];

/* 状態を表示する。 */
void display(int x, int y)
{

	ev3_lcd_set_font(EV3_FONT_SMALL);
	ev3_lcd_draw_string(msg, x, y);
}

void bluetooth_write()
{
	FILE *logfile=NULL;
	int ret;

	logfile = fopen(motor_log_file_name, "r");
	
	// 接続状態を確認
	while (!ev3_bluetooth_is_connected())
	{
		tslp_tsk(100);
	}

	//sprintf(msg,"s:%3.2f p:%3.2f i:%3.2f d:%3.2f",speed,p,i,d);

	strcpy(msg, "ev3_bluetooth_is_connected");
	display(10, 80);

	//  シリアルポートを開く
	bluetooth_log = ev3_serial_open_file(EV3_SERIAL_BT);

	char m1[10], m2[10], m3[10], m4[10];
	float s = 0, p = 0, i = 0, d = 0;
	long count=0;

	if (NULL != bluetooth_log)
	{
		fscanf(logfile, "%s,%s,%s,%s", m1, m2, m3, m4);
		fprintf(bluetooth_log, "%s,%s,%s,%s\n", m1, m2, m3, m4);

		while ((ret = fscanf(logfile, "%f, %f, %f, %f\n", &s, &p, &i, &d)) != EOF)
		{
			fprintf(bluetooth_log, "%ld %3.2f, %3.2f, %3.2f, %3.2f\n",count, s, p, i, d);
			count++;
			if(count>1000) break;
		}
	}
	if (NULL != logfile)
	{
		fclose(logfile);
	}
	if (NULL != bluetooth_log)
	{
		fclose(bluetooth_log);
	}
}

int Pid(float kp, float ki, float kd)
{ //PID制御関数
	static long diff[2] = {0, 0};
	static float p = 0, i = 0, d = 0;
	static float delta = 0.004; //周期
	static float speed = 0;
	static float integral = 0;
	static long count = 0;
	//PID制御計算
	diff[0] = diff[1];
	diff[1] = ANGLE_OF_AIM - motor->getCount(); //偏差を取得
	sprintf(msg, "count:%ld", count++);
	display(10, 10);
	sprintf(msg, "d0:%ld d1:%ld", diff[0], diff[1]);
	display(10, 20);

	p = ki * diff[1]; //P制御

	integral += ((diff[1] - diff[0]) / 2.0) * delta; //偏差の集計
	i = ki * integral;								 //I制御
	d = kd * (diff[1] - diff[0]) / delta;			 //D制御
	speed = (p + i + d);

	sprintf(msg, "s:%3.2f p:%3.2f i:%3.2f d:%3.2f", speed, p, i, d);
	display(10, 40);

	if (NULL != motor_log)
	{
		fprintf(motor_log, "%3.2f, %3.2f, %3.2f, %3.2f\n", speed, p, i, d);
	}

	if (speed < -100)
		speed = -100; //モータパワー (-100～100)
	else if (speed > 100)
		speed = 100;

	motor->setPWM(speed);
	return (speed);
}

void main_task(intptr_t unused)
{
	ev3_lcd_set_font(EV3_FONT_MEDIUM);

	motor_log = fopen(motor_log_file_name, "a");

	if (NULL != motor_log)
	{
		fprintf(motor_log, "SPEED,P_VALUE,I_VALUE,D_VALUE\n");
	}

	motor->reset();
	float speed;
	long count = 0;
	while (count < 1000)
	{
		speed = Pid(0.7, 0.3, 0.03);
		motor->setPWM(speed);
		tslp_tsk(1);
		count++;
	}

	delete (motor);
	delete (color);
	if (NULL != motor_log)
	{
		fclose(motor_log);
	}

	bluetooth_write();

	ext_tsk();
}
