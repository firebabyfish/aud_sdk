BSP_DIR := $(ROOT_DIR)/bsp

C_SOURCES += \
	$(BSP_DIR)/src/bsp_clock.c \
	$(BSP_DIR)/src/bsp_timer.c \
	$(BSP_DIR)/src/bsp_uart.c \
	$(BSP_DIR)/src/bsp_usb.c

C_INCLUDES += \
    -I${BSP_DIR}/inc/config \
    -I${BSP_DIR}/inc
