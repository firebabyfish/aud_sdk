#ifndef __BSP_TIMER_H__
#define __BSP_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


typedef enum {
    BSP_TIMER_NUM_1,
    BSP_TIMER_NUM_2,
    BSP_TIMER_NUM_3,
    BSP_TIMER_NUM_4,
    BSP_TIMER_NUM_5,
    BSP_TIMER_NUM_6,
    BSP_TIMER_NUM_7,
    BSP_TIMER_NUM_8,
    BSP_TIMER_NUM_9,
    BSP_TIMER_NUM_10,
    BSP_TIMER_NUM_END,
} bsp_timer_num_t;


void bsp_timer_init(uint16_t arr, uint16_t psc);

#ifdef __cplusplus
}
#endif

#endif
