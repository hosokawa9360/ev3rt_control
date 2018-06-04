mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))
APPL_COBJS += IO_Port.o
APPL_COBJS += SYS_Phase.o
APPL_COBJS += TSK_Phase.o

APPL_CXXOBJS += 

SRCLANG := c++
ifdef CONFIG_EV3RT_APPLICATION
# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile
endif
APPL_DIR += $(mkfile_path)app $(mkfile_path)unit
INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit
#COPTS += -fno-use-cxa-atexit
