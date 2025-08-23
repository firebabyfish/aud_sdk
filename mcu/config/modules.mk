ifeq ($(PLATFORM), ch585)
include $(ROOT_DIR)/platform/ch585/module.mk
endif

ifeq ($(OS), none)
else ifeq ($(OS), rtthread)
include $(ROOT_DIR)/middleware/rtthread/module.mk
else ifeq ($(OS), freertos)
include $(ROOT_DIR)/middleware/FreeRTOS/module.mk
endif

ifeq ($(CHERRYUSB_ENABLE), y)
include $(ROOT_DIR)/middleware/CherryUSB/module.mk
endif
