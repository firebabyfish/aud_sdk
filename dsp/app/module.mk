APP_DIR := $(ROOT_DIR)/app

C_SOURCES += \
	$(APP_DIR)/system/app_system.c \
	$(APP_DIR)/delay/app_delay.c \
	$(APP_DIR)/debug/app_debug.c \
	$(APP_DIR)/debug/app_log.c \
	$(APP_DIR)/app_test.c \
	$(APP_DIR)/main.c

# usb
C_SOURCES += \
	$(APP_DIR)/usb/device/uac/app_usb_uac_desc.c \
	$(APP_DIR)/usb/device/uac/usbfs_device.c \
	$(APP_DIR)/usb/device/uac/app_usb_uac_tx.c \
	$(APP_DIR)/usb/app_usb_main.c

C_INCLUDES += \
	-I${APP_DIR}/system \
    -I${APP_DIR}/delay \
	-I${APP_DIR}/debug \
	-I${APP_DIR}/usb/device/uac
