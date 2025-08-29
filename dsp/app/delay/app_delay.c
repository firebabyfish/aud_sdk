#include "ch32v30x.h"


static uint8_t p_us  = 0;
static uint16_t p_ms = 0;


void app_delay_init(void)
{
    p_us = SystemCoreClock / 8000000;
    p_ms = (uint16_t)p_us * 1000;
}

void app_delay_us(uint32_t us)
{
    uint32_t i;

    SysTick->SR &= ~(1 << 0);

    i = (uint32_t)us * p_us;

    SysTick->CMP   = i;
    SysTick->CTLR |= (1 << 4);
    SysTick->CTLR |= (1 << 5) | (1 << 0);

    while ((SysTick->SR & (1 << 0)) != (1 << 0));
    SysTick->CTLR &= ~(1 << 0);
}

void app_delay_ms(uint32_t ms)
{
    uint32_t i;

    SysTick->SR &= ~(1 << 0);

    i = (uint32_t)ms * p_ms;

    SysTick->CMP   = i;
    SysTick->CTLR |= (1 << 4);
    SysTick->CTLR |= (1 << 5) | (1 << 0);

    while ((SysTick->SR & (1 << 0)) != (1 << 0));
    SysTick->CTLR &= ~(1 << 0);
}