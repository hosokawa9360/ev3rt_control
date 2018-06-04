#include "Pid.h"
#include "TouchSensor.h"

using namespace ev3api;
extern TouchSensor *touch; 

Pid :: Pid()
{
    color = new ColorSensor(PORT_1);
    kp = 0.7;
    ki = 0.3;
    kd = 0.03;
    middle_light = (MAX_LIGHT + MIN_LIGHT) / 2.0;
    motorFlg = 0;
}

void Pid::setPid(float _kp, float _ki, float _kd)
{ //PID計数をセット
    kp = _kp;
    ki = _ki;
    kd = _kd;
}

short Pid::getDirection()
{ //左右回転情報を返す
    return motorFlg;
}

int Pid::CalcPid()
{ //PID計算と速さのリターン
    diff[0] = diff[1];
    diff[1] = middle_light - color->getBrightness();
    p = kp * diff[1];                                //P制御
    integral += ((diff[1] - diff[0]) / 2.0) * delta; //偏差の集計
    i = ki * integral;                               //I制御
    d = kd * (diff[1] - diff[0]) / delta;            //D制御
    speed = (p + i + d);

    motorFlg = 0;
    if (diff[1] < middle_light)
        motorFlg = 1; //左回転フラグ設定
    else if (diff[1] > middle_light)
        motorFlg = 2; //右回転フラグ設定
    {
        char m[32];
        sprintf(m, "Bright:%d Speed:%2d     ", (int)color->getBrightness(), (int)speed);
        ev3_lcd_draw_string(m, 10, 40);
    }

    return(speed);
}

void Pid::InitPid(void)
{
	char m[32];

	ev3_lcd_set_font(EV3_FONT_MEDIUM);

	int black_Brightness=0;
    int white_Brightness=0;
	
    while (touch->isPressed() == false)
	{
		white_Brightness = color->getBrightness();
		sprintf(m, "white:%2d", white_Brightness);
		ev3_lcd_draw_string(m, 20, 10);
	}
	tslp_tsk(1000);

   while (touch->isPressed() == false)
	{
		black_Brightness = color->getBrightness();
		sprintf(m, "black:%2d", black_Brightness);
		ev3_lcd_draw_string(m, 20, 25);
	}
	tslp_tsk(1000);
	middle_light = (white_Brightness + black_Brightness) / 2;
	sprintf(m, "middle:%3.1lf", middle_light);
	ev3_lcd_draw_string(m, 20, 40);
}