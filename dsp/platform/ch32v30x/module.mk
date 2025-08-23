CH32V30X_STD_DIR := $(ROOT_DIR)/platform/ch32v30x

C_SOURCES += \
	$(CH32V30X_STD_DIR)/Core/core_riscv.c \
	$(CH32V30X_STD_DIR)/System/ch32v30x_it.c \
	$(CH32V30X_STD_DIR)/System/system_ch32v30x.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_adc.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_bkp.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_can.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_crc.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_dac.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_dbgmcu.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_dma.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_dvp.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_eth.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_exti.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_flash.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_fsmc.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_gpio.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_i2c.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_iwdg.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_misc.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_opa.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_pwr.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_rcc.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_rng.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_rtc.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_sdio.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_spi.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_tim.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_usart.c \
	$(CH32V30X_STD_DIR)/Peripheral/src/ch32v30x_wwdg.c \
	$(CH32V30X_STD_DIR)/Debug/debug.c

ifeq ($(OS), none)
ASM_SOURCES += $(CH32V30X_STD_DIR)/Startup/startup_ch32v30x_D8C.S
LDSCRIPT += $(CH32V30X_STD_DIR)/Ld/Link.ld
else ifeq ($(OS), rtthread)
ASM_SOURCES += $(CH32V30X_STD_DIR)/Startup/startup_ch32v30x_D8C.S
else ifeq ($(OS), freertos)
ASM_SOURCES += $(CH32V30X_STD_DIR)/Startup/startup_ch32v30x_D8C_FreeRTOS.S
LDSCRIPT += $(CH32V30X_STD_DIR)/Ld/Link_FreeRTOS.ld
endif
	
C_INCLUDES += \
	-I$(CH32V30X_STD_DIR)/Core \
	-I$(CH32V30X_STD_DIR)/Debug \
	-I$(CH32V30X_STD_DIR)/System \
	-I$(CH32V30X_STD_DIR)/Peripheral/inc
