ifeq ($(PLATFORM), ch32v30x)
include $(ROOT_DIR)/platform/ch32v30x/module.mk
endif

ifeq ($(OS), none)
else ifeq ($(OS), rtthread)
include $(ROOT_DIR)/middleware/rtthread/module.mk
else ifeq ($(OS), freertos)
include $(ROOT_DIR)/middleware/FreeRTOS/module.mk
endif

ifneq ($(CODEC), none)
include $(ROOT_DIR)/middleware/lc3plus/module.mk
endif
