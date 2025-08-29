#include "ch32v30x.h"


void bsp_nvic_init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}
