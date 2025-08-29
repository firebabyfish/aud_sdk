######################################
# target
######################################
TARGET = mcu
ROOT_DIR := .

C_SOURCES ?=
C_INCLUDES ?=
ASM_SOURCES ?=
LDSCRIPT ?=

include $(ROOT_DIR)/config/config.mk

######################################
# build options
######################################
DEBUG = -DDEBUG=0
LEVEL = -Os

######################################
# build directory
######################################
BUILD_DIR = out

######################################
# sources
######################################
USER_C_SRC = 
	
C_SOURCES += $(USER_C_SRC)

C_INCLUDES += 
######################################
# toolchain
######################################
PREFIX = riscv-wch-elf-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

######################################
# compiler flags
######################################
MCU = -march=rv32imc_zba_zbb_zbc_zbs_xw -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 ${LEVEL} \
	-fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g  
# --param=highcode-gen-section-name=1

CFLAGS = $(MCU) $(DEBUG) $(C_INCLUDES) -std=gnu99 

ASFLAGS = $(MCU) $(DEBUG) $(C_INCLUDES) -x assembler-with-cpp -DENABLE_INTERRUPT_NEST=0

######################################
# linker
######################################
LIBS = -lc -lm -lnosys $(ROOT_DIR)/platform/ch585/StdPeriphDriver/libISP585.a
LDFLAGS = $(MCU) -T $(LDSCRIPT) -nostartfiles -Xlinker --gc-sections ${LIBS} \
	 -Xlinker --print-memory-usage -Xlinker --print-memory-usage -Wl,-Map,$(BUILD_DIR)/$(TARGET).map \
	 --specs=nano.specs --specs=nosys.specs

######################################
# build objects
######################################
OBJ_C   = $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
OBJ_ASM = $(patsubst %.S,$(BUILD_DIR)/%.o,$(ASM_SOURCES))
OBJS = $(OBJ_C) $(OBJ_ASM)
DEPS = $(OBJS:.o=.d)

######################################
# default target
######################################
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

######################################
# build rules
######################################
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "CC      " "$<"
	@$(CC) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<" 

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "AS      " "$<"
	@$(AS) $(ASFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

$(BUILD_DIR)/$(TARGET).elf: $(OBJS) Makefile
	@echo "LD      " "$@"
	@$(CC) $(OBJS) $(LDFLAGS) -o $@
	@echo "SIZE    " "$@"
	@$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo "OBJCOPY " "$@"
	@$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo "OBJCOPY " "$@"
	@$(BIN) $< $@

######################################
# create build directory
######################################
$(BUILD_DIR):
	@mkdir -p $@

######################################
# clean
######################################
clean:
	rm -rf $(BUILD_DIR)

######################################
# dependencies
######################################
-include $(DEPS)
