#include "bsp_nvic.h"
#include "bsp_clock.h"
#include "bsp_timer.h"

#define LOG_TAG "app_system"
#include "app_log.h"


void app_system_init(void)
{
    bsp_nvic_init();
    bsp_clock_init();
    bsp_timer_init(1000, 144);
}
