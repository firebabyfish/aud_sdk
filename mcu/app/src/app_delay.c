#include "bsp_timer.h"


void app_delay_10us(uint32_t us)
{
    bsp_timer_delay(us);
}

void app_delay_ms(uint32_t ms)
{
    while (ms--) {
        app_delay_10us(100);
    }
}
