#ifndef __APP_DELAY_H__
#define __APP_DELAY_H__


#include <stdint.h>


void app_delay_init(void);
void app_delay_us(uint32_t us);
void app_delay_ms(uint32_t ms);


#endif  // __APP_DELAY_H__