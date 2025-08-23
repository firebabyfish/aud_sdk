RTTHREAD_DIR := $(ROOT_DIR)/middleware/rtthread

C_SOURCES += \
	$(RTTHREAD_DIR)/src/clock.c \
	$(RTTHREAD_DIR)/src/components.c \
	$(RTTHREAD_DIR)/src/cpu.c \
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
	$(RTTHREAD_DIR)/libcpu/WCH/Qingke_V3C/cpuport.c \
	$(RTTHREAD_DIR)/components/finsh/cmd.c \
	$(RTTHREAD_DIR)/components/finsh/finsh_port.c \
	$(RTTHREAD_DIR)/components/finsh/msh.c \
	$(RTTHREAD_DIR)/components/finsh/shell.c \
	$(RTTHREAD_DIR)/components/drivers/ipc/ringbuffer.c \
	$(RTTHREAD_DIR)/components/device/device.c \
	$(RTTHREAD_DIR)/bsp/usart/drv_usart.c \
	$(RTTHREAD_DIR)/bsp/board.c
	
ASM_SOURCES += \
	$(RTTHREAD_DIR)/libcpu/WCH/Qingke_V3C/context_gcc.S \
	$(RTTHREAD_DIR)/libcpu/WCH/Qingke_V3C/interrupt_gcc.S
	
C_INCLUDES += \
	-I$(RTTHREAD_DIR)/components/finsh \
	-I$(RTTHREAD_DIR)/libcpu/WCH/Qingke_V3C \
	-I$(RTTHREAD_DIR)/include \
	-I$(RTTHREAD_DIR)/bsp \
	-I$(RTTHREAD_DIR)/bsp/usart \
	-I$(RTTHREAD_DIR)/components/drivers/include
