#LineTrace2  PID制御
ライントレースの前に、ColorSensorを使って輝度を測ること
閾値は　黒と白の輝度の中間を設定する

ロギングプログラム実装

   motor_log = fopen(motor_log_file_name, "a");

    if (NULL != motor_log) {
        fprintf(motor_log, (const char *)motor_log_format);
    }

if (NULL != motor_log) {
        fprintf(motor_log,"%d,%d,%d,%d\n",speed,p,i,d);
    }

    	if (NULL != motor_log) { fclose(motor_log); }