#include "debug.h"
#include "FreeRTOS.h"
#include "task.h"
#include "aud_i2s.h"


void aud_task(void *pvParameters)
{
    while (1) {
        printf("aud_task is running\r\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void aud_lowlevel_init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(921600);
}

int main(void)
{
    aud_lowlevel_init();
    
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
    printf("FreeRTOS Kernel Version:%s\r\n", tskKERNEL_VERSION_NUMBER);
    
    // aud_i2s_init();

    xTaskCreate(aud_task, "aud_task", 256, NULL, 2, NULL);

    vTaskStartScheduler();
    while (1) {
        printf("shouldn't run at here!!\n");
    }
}
