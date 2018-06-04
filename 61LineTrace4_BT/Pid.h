#include "ColorSensor.h"
#include "TouchSensor.h"

using namespace ev3api;

#define MAX_LIGHT 20
#define MIN_LIGHT 2

class Pid
{
  private:
    long diff[2] = {0, 0};
    float kp , ki , kd;
    float p = 0, i = 0, d = 0;
    float delta = 0.004; //周期
    float speed = 0;
    float integral = 0;
    short motorFlg = 0; //0:直進 1:左回転 2:右回転
    ColorSensor color;
    public:
    Pid();
    void setPid(float , float , float); //Pid計数設定
    short getDirection();   //方向取得  
    int CalcPid();  //Pid計算
    void initPid(); //タッチを利用した白黒輝度取得
}