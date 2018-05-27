//#include "ev3api.h"
#include<string.h>
#include "app.h"
#include "Port.h"
#include "TouchSensor.h"
#include "SonarSensor.h"
using namespace ev3api;

TouchSensor *touch;
SonarSensor *sonar;

void main_task(intptr_t unused)
{
	
	char msg1[32];
	int distance;
	
	touch = new TouchSensor(PORT_1);
	sonar = new SonarSensor(PORT_3);

	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_lcd_draw_string("sonar PG!!", 20, 20);

	while (touch->isPressed() == false){
		distance = sonar->getDistance();
		sprintf(msg1,"Distance:%3d",distance);
		ev3_lcd_draw_string(msg1, 20, 20);
	}	
	ev3_lcd_draw_string("Stop!!", 20, 100);
	delete(touch);
	delete(sonar);
	ext_tsk();
}
