#include "ev3api.h"
#include "app.h"
#include <unistd.h>
#include <ctype.h>
#include <string.h>

void sub_task(intptr_t unused) {
   ev3_lcd_set_font(EV3_FONT_MEDIUM);
   ev3_lcd_draw_string("Hello Jyobi!!", 20 ,40);
   ext_tsk();
}
