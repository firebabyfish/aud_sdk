ifeq ($(OS), none)
else ifeq ($(OS), rtthread)
include $(ROOT_DIR)/middleware/rtthread/module.mk
else ifeq ($(OS), freertos)
include $(ROOT_DIR)/middleware/FreeRTOS/module.mk
endif

ifneq ($(CODEC), none)
include $(ROOT_DIR)/middleware/lc3plus/module.mk
endif

ifeq ($(EASYLOGGER_ENABLE), y)
include $(ROOT_DIR)/middleware/EasyLogger/module.mk
endif

include $(ROOT_DIR)/bsp/module.mk
include $(ROOT_DIR)/app/module.mk
