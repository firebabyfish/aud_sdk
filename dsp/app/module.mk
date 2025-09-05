APP_DIR := $(ROOT_DIR)/app

# system
C_SOURCES += \
	$(APP_DIR)/system/app_system.c
C_INCLUDES += \
	-I${APP_DIR}/system
	
# delay
C_SOURCES += \
	$(APP_DIR)/delay/app_delay.c
C_INCLUDES += \
	-I${APP_DIR}/delay

# debug
C_SOURCES += \
	$(APP_DIR)/debug/app_debug.c \
	$(APP_DIR)/debug/app_log.c
C_INCLUDES += \
	-I${APP_DIR}/debug

# usb
ifeq ($(USB_AUDIO), v1)
C_SOURCES += \
	$(APP_DIR)/usb/audio_v1/app_usb_audio.c
C_INCLUDES += \
	-I${APP_DIR}/usb \
	-I${APP_DIR}/usb/audio_v1
else ifeq ($(USB_AUDIO), v2)
C_SOURCES += \
	$(APP_DIR)/usb/audio_v2/app_usb_audio.c
C_INCLUDES += \
	-I${APP_DIR}/usb \
	-I${APP_DIR}/usb/audio_v2
endif
	
# main
C_SOURCES += \
	$(APP_DIR)/main/app_test.c \
	$(APP_DIR)/main/app_main.c
