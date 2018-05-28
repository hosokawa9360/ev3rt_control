//#include "ev3api.h"
#include<string.h>
#include "app.h"
#include "Port.h"
#include "TouchSensor.h"
#include "GyroSensor.h"
using namespace ev3api;

TouchSensor *touch;
GyroSensor *gyro;

void main_task(intptr_t unused)
{
	char msg1[32],msg2[32];
	int angle,angleveloocity;;
	
	touch = new TouchSensor(PORT_1);
	gyro = new GyroSensor(PORT_4);

	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_lcd_draw_string("Gyro PG!!", 20, 20);
	gyro->reset();
	gyro->setOffset(0);
	while (touch->isPressed() == false){
		angle = gyro->getAngle();
		angleveloocity = gyro->getAnglerVelocity();

		sprintf(msg1,"Angle:%3d",angle);
		sprintf(msg2,"A Velocity:%3d",angleveloocity);
		ev3_lcd_draw_string(msg1, 20, 20);
		ev3_lcd_draw_string(msg2, 20, 60);
	}	
	ev3_lcd_draw_string("Stop!!", 20, 100);
	delete(touch);
	delete(gyro);

	ext_tsk();
}
