APP_DIR := $(ROOT_DIR)/app

C_SOURCES += \
	$(APP_DIR)/src/app_delay.c \
	$(APP_DIR)/src/app_log.c \
	$(APP_DIR)/main.c

C_INCLUDES += \
    -I${APP_DIR}/inc
