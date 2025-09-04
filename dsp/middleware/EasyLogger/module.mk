EASYLOGGER_DIR := $(ROOT_DIR)/middleware/EasyLogger/easylogger

C_SOURCES += \
	$(EASYLOGGER_DIR)/port/elog_port.c \
	$(EASYLOGGER_DIR)/src/elog.c \
	$(EASYLOGGER_DIR)/src/elog_async.c \
	$(EASYLOGGER_DIR)/src/elog_utils.c \
	$(EASYLOGGER_DIR)/src/elog_buf.c \
	
C_INCLUDES += -I$(EASYLOGGER_DIR)/inc
