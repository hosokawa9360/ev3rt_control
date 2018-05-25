APPL_COBJS += 

APPL_CXXOBJS += 

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
#include $(EV3RT_SDK_LIB_DIR)/libcpp-test/Makefile
#include $(EV3RT_SDK_LIB_DIR)/lib2/Makefile
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

#APPL_DIR += \
#    $(mkfile_path)../../common/libray/libcpp-ev3/src \
#    $(mkfile_path)app \
#    $(mkfile_path)unit

#INCLUDE += \
#    -I$(mkfile_path)../../common/libray/libcpp-ev3/include \
#    -I$(mkfile_path)app \
#    -I$(mkfile_path)unit

endif

