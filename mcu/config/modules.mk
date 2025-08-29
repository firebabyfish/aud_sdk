ifeq ($(OS), none)
else ifeq ($(OS), rtthread)
include $(ROOT_DIR)/middleware/rtthread/module.mk
else ifeq ($(OS), freertos)
include $(ROOT_DIR)/middleware/FreeRTOS/module.mk
endif

ifeq ($(EASYLOGGER_ENABLE), y)
CFLAGS += -DEASYLOGGER_ENABLE
include $(ROOT_DIR)/middleware/EasyLogger/module.mk
endif

ifeq ($(CHERRYUSB_ENABLE), y)
# full, high
USB_SPEED := full
CFLAGS += -DCHERRYUSB_ENABLE
include $(ROOT_DIR)/middleware/CherryUSB/module.mk
endif

include $(ROOT_DIR)/bsp/module.mk
include $(ROOT_DIR)/app/module.mk
