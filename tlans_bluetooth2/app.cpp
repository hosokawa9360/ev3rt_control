#include "ev3api.h"
#include "app.h"
#include <string.h>
#include <syssvc/serial.h>

#include <kernel.h>
#include <itron.h>
#include <t_syslog.h>
#include <stdio.h>
#include "zmodem/src/gen_defs.h"
//#include "fatfs_dri.h"

#include "syssvc/serial.h"
#include "target_serial.h"


#define MESSAGE_LEN  8
 
static char message[MESSAGE_LEN + 1] = {0};
 
 /* 状態を表示する。 */
void display()
{
  ev3_lcd_set_font(EV3_FONT_MEDIUM);
  ev3_lcd_draw_string(message, 10, 40);
}

/* タスク */
void task1(intptr_t exinf)
{
  FILE *bt;
  bool_t result;
  int connected_attempt=0;
  // 接続状態を確認
  while((result = ev3_bluetooth_is_connected())!=true){
    connected_attempt++;
    sprintf(message,"retval %d %d",result,connected_attempt);
    display();
    tslp_tsk(100);
  }
   // シリアルポートを開く
  bt = ev3_serial_open_file(EV3_SERIAL_BT);
 
        fprintf(bt, "Bluetooth SPP ID: %d\n", EV3_SERIAL_BT);

       

     strcpy(message,"end");
     display();
 }
}
 
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


void main_task(intptr_t unused)
{
	ev3_lcd_set_font(EV3_FONT_MEDIUM);

	bluetooth_write();

	ext_tsk();
}
