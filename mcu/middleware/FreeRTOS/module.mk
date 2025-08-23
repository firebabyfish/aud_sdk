FREERTOS_DIR := $(ROOT_DIR)/middleware/FreeRTOS

C_SOURCES += \
	$(FREERTOS_DIR)/portable/MemMang/heap_4.c \
	$(FREERTOS_DIR)/portable/GCC/RISC-V/port.c \
	$(FREERTOS_DIR)/src/croutine.c \
	$(FREERTOS_DIR)/src/event_groups.c \
	$(FREERTOS_DIR)/src/list.c \
	$(FREERTOS_DIR)/src/queue.c \
	$(FREERTOS_DIR)/src/stream_buffer.c \
	$(FREERTOS_DIR)/src/tasks.c \
	$(FREERTOS_DIR)/src/timers.c
	
ASM_SOURCES += $(FREERTOS_DIR)/portable/GCC/RISC-V/portASM.S
	
C_INCLUDES += \
	-I$(FREERTOS_DIR)/portable/GCC/RISC-V \
	-I$(FREERTOS_DIR)/include
