#ifndef __TIMER_H__
#define __TIMER_H__


#include <stdint.h>


extern volatile uint32_t __sys_tick;


void bsp_timer_init(void);
void bsp_timer_delay(uint32_t ticks);


#endif
