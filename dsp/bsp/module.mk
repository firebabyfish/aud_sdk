BSP_DIR := $(ROOT_DIR)/bsp

# clock
C_SOURCES += ${BSP_DIR}/clock/bsp_clock.c
# nvic
C_SOURCES += ${BSP_DIR}/nvic/bsp_nvic.c
# timer
C_SOURCES += ${BSP_DIR}/timer/bsp_timer.c
# dma
C_SOURCES += ${BSP_DIR}/dma/bsp_dma.c
# uart
C_SOURCES += ${BSP_DIR}/uart/bsp_uart.c
# i2s
C_SOURCES += ${BSP_DIR}/i2s/bsp_i2s.c
# usb
C_SOURCES += ${BSP_DIR}/usb/bsp_usb.c

C_INCLUDES += \
    -I${BSP_DIR}/clock \
    -I${BSP_DIR}/nvic \
    -I${BSP_DIR}/timer \
    -I${BSP_DIR}/dma \
	-I${BSP_DIR}/uart \
	-I${BSP_DIR}/i2s \
	-I${BSP_DIR}/usb
