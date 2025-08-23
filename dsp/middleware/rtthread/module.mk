RTTHREAD_DIR := $(ROOT_DIR)/middleware/rtthread

C_SOURCES += \
	$(RTTHREAD_DIR)/src/clock.c \
	$(RTTHREAD_DIR)/src/components.c \
	$(RTTHREAD_DIR)/src/cpu.c \
	$(RTTHREAD_DIR)/src/device.c \
	$(RTTHREAD_DIR)/src/idle.c \
	$(RTTHREAD_DIR)/src/ipc.c \
	$(RTTHREAD_DIR)/src/irq.c \
	$(RTTHREAD_DIR)/src/kservice.c \
	$(RTTHREAD_DIR)/src/mem.c \
	$(RTTHREAD_DIR)/src/memheap.c \
	$(RTTHREAD_DIR)/src/mempool.c \
	$(RTTHREAD_DIR)/src/object.c \
	$(RTTHREAD_DIR)/src/scheduler.c \
	$(RTTHREAD_DIR)/src/slab.c \
	$(RTTHREAD_DIR)/src/thread.c \
	$(RTTHREAD_DIR)/src/timer.c \
	$(RTTHREAD_DIR)/libcpu/risc-v/common/cpuport.c \
	$(RTTHREAD_DIR)/components/finsh/cmd.c \
	$(RTTHREAD_DIR)/components/finsh/msh.c \
	$(RTTHREAD_DIR)/components/finsh/msh_cmd.c \
	$(RTTHREAD_DIR)/components/finsh/msh_file.c \
	$(RTTHREAD_DIR)/components/finsh/shell.c \
	$(RTTHREAD_DIR)/components/finsh/symbol.c \
	$(RTTHREAD_DIR)/components/drivers/serial/serial.c \
	$(RTTHREAD_DIR)/components/drivers/misc/pin.c \
	$(RTTHREAD_DIR)/board.c
	
ASM_SOURCES += \
	$(RTTHREAD_DIR)/libcpu/risc-v/common/context_gcc.S \
	$(RTTHREAD_DIR)/libcpu/risc-v/common/interrupt_gcc.S
	
C_INCLUDES += \
	-I$(RTTHREAD_DIR) \
	-I$(RTTHREAD_DIR)/include \
	-I$(RTTHREAD_DIR)/include/libc \
	-I$(RTTHREAD_DIR)/libcpu/risc-v/common \
	-I$(RTTHREAD_DIR)/components/drivers/include \
	-I$(RTTHREAD_DIR)/components/drivers/include/drivers \
	-I$(RTTHREAD_DIR)/components/drivers/include/ipc \
	-I$(RTTHREAD_DIR)/components/finsh
