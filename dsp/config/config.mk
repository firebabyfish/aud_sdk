# ch32v30x, ch585
PLATFORM := ch32v30x

# none, rtthread, freertos
OS := none

# none, fixed, floating
CODEC := none

EASYLOGGER_ENABLE := y

include $(ROOT_DIR)/config/platform.mk
include $(ROOT_DIR)/config/modules.mk
