#LineTrace1

// Bluetooth仮想シリアルポートのファイルをオープンする
FILE *bt = ev3_serial_open_file(EV3_SERIAL_BT);

// 書式化した文字列をBluetooth仮想シリアルポートへ書き込む
fprintf(bt, "Bluetooth SPP ID: %d\n", EV3_SERIAL_BT);

// Bluetooth仮想シリアルポートから1文字を読み取る
int c = fgetc(bt);