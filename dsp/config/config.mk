# ch32v30x, ch585
PLATFORM := ch32v30x

# none, rtthread, freertos
OS := none

# none, fixed, floating
CODEC := none

EASYLOGGER_ENABLE := y

CHERRYUSB_ENABLE := y
# v1, v2
USB_AUDIO := v1

include $(ROOT_DIR)/config/platform.mk
include $(ROOT_DIR)/config/modules.mk
