CH585_STD_DIR := $(ROOT_DIR)/platform/ch585

C_SOURCES += \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_adc.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_clk.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_flash.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_gpio.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_i2c.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_lcd.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_pwm.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_pwr.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_spi0.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_spi1.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_sys.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_timer0.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_timer1.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_timer2.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_timer3.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_uart0.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_uart1.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_uart2.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_uart3.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_usbdev.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_usbhostBase.c \
	$(CH585_STD_DIR)/StdPeriphDriver/CH58x_usbhostClass.c
	
C_INCLUDES += \
	-I$(CH585_STD_DIR)/RVMSIS \
	-I$(CH585_STD_DIR)/StdPeriphDriver/inc

ifeq ($(OS), none)
ASM_SOURCES += $(CH585_STD_DIR)/Startup/startup_CH585.S
LDSCRIPT += $(CH585_STD_DIR)/Ld/Link.ld
else ifeq ($(OS), rtthread)
ASM_SOURCES += $(CH585_STD_DIR)/Startup/Startup_CH585_RTThread.S
LDSCRIPT += $(CH585_STD_DIR)/Ld/Link_RTThread.ld
else ifeq ($(OS), freertos)
ASM_SOURCES += $(CH585_STD_DIR)/Startup/Startup_CH585_FreeRTOS.S
LDSCRIPT += $(CH585_STD_DIR)/Ld/Link_FreeRTOS.ld
endif