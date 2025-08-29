# ch585, ch32v30x
PLATFORM := ch585

# none, rtthread, freertos(Can't use os)
OS := none

EASYLOGGER_ENABLE := y
CHERRYUSB_ENABLE := y

include $(ROOT_DIR)/config/platform.mk
include $(ROOT_DIR)/config/modules.mk
