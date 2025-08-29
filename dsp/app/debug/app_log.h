#ifndef __LOG_H__
#define __LOG_H__


#include "elog.h"


#define APP_LOG_ASSERT  log_a
#define APP_LOG_INFO    log_i
#define APP_LOG_WARN    log_w
#define APP_LOG_ERROR   log_e
#define APP_LOG_DEBUG   log_d
#define APP_LOG_VERBOSE log_v


void app_log_init(void);


#endif
