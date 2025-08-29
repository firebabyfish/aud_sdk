#include "CH58x_common.h"


volatile uint32_t tmr0_count;
volatile uint32_t tick_count;
volatile uint32_t __sys_tick;


void bsp_timer_init(void)
{
    TMR0_TimerInit(FREQ_SYS / 100000);      // 设置定时时间 10us
    TMR0_ITCfg(ENABLE, TMR0_3_IT_CYC_END);  // 开启中断
    PFIC_EnableIRQ(TMR0_IRQn);
}

void bsp_timer_delay(uint32_t ticks)
{
    tmr0_count = ticks;
    while (tmr0_count);
}

__INTERRUPT
__HIGH_CODE
void TMR0_IRQHandler(void)
{
    if (TMR0_GetITFlag(TMR0_3_IT_CYC_END)) {
        TMR0_ClearITFlag(TMR0_3_IT_CYC_END);
        if (++tick_count >= 100) {
            tick_count = 0;
            __sys_tick++;
        }
        if (tmr0_count) {
            tmr0_count--;
        }
    }
}
