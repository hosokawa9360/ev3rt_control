#include "ev3api.h"
#include "app.h"
#include <string.h>
#include <syssvc/serial.h>

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
 
