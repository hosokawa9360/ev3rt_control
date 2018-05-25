#include "ev3api.h"
#include "app.h"
#include "Port.h"
#include "ColorSensor.h"
#include "TouchSensor.h"

using namespace ev3api;

TouchSensor *touch;
ColorSensor *color;

void main_task(intptr_t unused)
{
	char msg1[32],msg2[32],msg3[32];
	int lightPower;
	int colorId;
	rgb_raw_t rgb_val;

	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_lcd_draw_string("Color PG!!", 20, 20);
	
	touch = new TouchSensor(PORT_1);
	color = new ColorSensor(PORT_2);

	while (touch->isPressed() == false){
		lightPower = color->getBrightness();
		colorId = color->getColorNumber();
		color->getRawColor(rgb_val);

		sprintf(msg1,"Power:%3d",lightPower);
		sprintf(msg2,"ColorId:%3d", colorId);
		sprintf(msg3,"r:%d g:%d b:%d",rgb_val.r,rgb_val.g,rgb_val.b);
		ev3_lcd_draw_string(msg1, 20, 20);
		ev3_lcd_draw_string(msg2, 20, 40);
		ev3_lcd_draw_string(msg3, 20, 60);
	}	
	ev3_lcd_draw_string("Stop!!", 20, 60);
	//delete(color);
	//delete(touch);
	ext_tsk();
}
