#include "ch32v30x.h"


// uint32_t counter = 0;
// void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));


// void GPIO_Toggle_INIT(void)
// {
//     GPIO_InitTypeDef GPIO_InitStructure = {0};

//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOA, &GPIO_InitStructure);
// }

// void bsp_systick_irq_init(uint64_t ticks)
// {
//     // SysTick->SR &= ~(1 << 0);//clear State flag
//     // SysTick->CMP = SystemCoreClock / 1000;
//     // SysTick->CNT = 0;
//     // SysTick->CTLR = 0xF;

//     // NVIC_SetPriority(SysTicK_IRQn, 15);
//     // NVIC_EnableIRQ(SysTicK_IRQn);
// }

void bsp_clock_init(void)
{
    SystemCoreClockUpdate();
    // bsp_systick_irq_init(SystemCoreClock-1);
    // GPIO_Toggle_INIT();
}

// void SysTick_Handler(void)
// {
//     // u8 i = 0;
//     // if(SysTick->SR == 1)
//     // {
//     //     SysTick->SR = 0;//clear State flag
//     //     GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
//     // }
// }
