#ColorSensorのテスト
		lightPower = color->getBrightness();
		sprintf(msg1,"Power:%3d",lightPower);
		ev3_lcd_draw_string(msg1, 20, 20);
		
		color->getRawColor(rgb_val);
		sprintf(msg2,"r:%d g:%d b:%d",rgb_val.r,rgb_val.g,rgb_val.b);
		ev3_lcd_draw_string(msg2, 20, 40);