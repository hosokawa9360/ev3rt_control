#pragma once

#define MESSAGE_BUF_SIZE (32)
#define BT_TASK_INTERVAL (10) //10msec
extern void BtTask(intptr_t unused);

class Bt
{
  private:
    static FLGPTN bt_wait_flg;
    bool_t bt_task_running;
    int bt_task_count;
    int cmd_hdl_count;
  
  public:
    Bt(); //Bluetoothのタスクの初期化
    void start_bt_task(void);
    void stop_bt_task(void) ;
    void wait_btconnect(void) ;

}