#include "CH58x_common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdarg.h"


void aud_task(void *pvParameters)
{
    while (1) {
        extern void audio_v2_test(uint8_t busid);
        audio_v2_test(0);
    }
}

int main(void)
{
    GPIOA_SetBits(GPIO_Pin_14);
    GPIOPinRemap(ENABLE, RB_PIN_UART0);
    GPIOA_ModeCfg(GPIO_Pin_15, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeOut_PP_5mA);
    UART0_DefInit();

    PRINT("start.\n");
    
    extern void audio_v2_init(uint8_t busid, uintptr_t reg_base);
    audio_v2_init(0, 0x40009000);

    xTaskCreate(aud_task, "aud_task", 256, NULL, 2, NULL);

    vTaskStartScheduler();
    while (1) {
        PRINT("shouldn't run at here!!\n");
    }
}

void GPIOA_IRQHandler(void)
{
    uint16_t flag;
    portBASE_TYPE xHigherPriorityTaskWoken;
    flag = GPIOA_ReadITFlagPort();
    if ((flag & GPIO_Pin_12) != 0) {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
    GPIOA_ClearITFlagBit(flag);
}
