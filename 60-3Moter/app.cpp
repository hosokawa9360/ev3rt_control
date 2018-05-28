#include<string.h>
#include "app.h"
#include "Port.h"
#include "TouchSensor.h"
#include "Motor.h"
using namespace ev3api;

TouchSensor *touch;
Motor *motorR,*motorL;

void main_task(intptr_t unused)
{
	motorL = new Motor(PORT_A);//右モーター
	motorR = new Motor(PORT_B);//左モーター

	motorR->reset();
	motorL->reset();
	motorR->setPWM(20);
	motorL->setPWM(20);
	while (motorR->getCount() < 360*2);
	
	motorR->reset();
	motorL->reset();
	
	motorR->setPWM(0);
	motorL->setPWM(20);
	while (motorL->getCount() < 270);
	motorR->setPWM(0);
	motorL->setPWM(0);
	delete(motorL);
	delete(motorR);
	ext_tsk();
}
