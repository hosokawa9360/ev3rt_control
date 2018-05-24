mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))
#C言語プログラムコンパイル時のファイルを指定
APPL_COBJS += \
#C++言語プログラムコンパイル時のファイルを指定
APPL_CXXOBJS += \
    TouchSensor.o
SRCLANG :=c++

APPL_DIR += \
    $(mkfile_path)../../common/libray/libcpp-ev3/src \
    $(mkfile_path)app \
    $(mkfile_path)unit

INCLUDE += \
    -I$(mkfile_path)../../common/libray/libcpp-ev3/include \
    -I$(mkfile_path)app \
    -I$(mkfile_path)unit

#COPTS += -fno-use-cxa-atexit