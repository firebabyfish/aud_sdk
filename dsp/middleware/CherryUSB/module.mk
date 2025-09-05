CHERRYUSB_DIR := $(ROOT_DIR)/middleware/CherryUSB

C_SOURCES += \
	$(CHERRYUSB_DIR)/core/usbd_core.c \
	$(CHERRYUSB_DIR)/port/ch32/ch32fs/usb_dc_usbfs.c \
	$(CHERRYUSB_DIR)/class/audio/usbd_audio.c
	
C_INCLUDES += \
	-I$(CHERRYUSB_DIR)/core \
	-I$(CHERRYUSB_DIR)/common \
	-I$(CHERRYUSB_DIR)/class/audio \
	-I$(CHERRYUSB_DIR)/port/ch32/ch32fs
