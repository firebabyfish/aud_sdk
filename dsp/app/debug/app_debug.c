#include "bsp_uart.h"
#include "bsp_dma.h"
#include "ch32v30x.h"

#include <stddef.h>

#define APP_DEBUG_UART_NUM BSP_UART_NUM_1


void app_debug_init(uint32_t baudrate)
{
    bsp_uart_tx_init(BSP_UART_NUM_1, baudrate);
    // bsp_dma_init(BSP_DMA_CH_USART1_TX, (uint32_t)&USART1->DATAR, 0, 0, BSP_DMA_DIR_DST, BSP_DMA_BYTE_WIDTH_BYTE);
}

__attribute__((used)) int _write(int fd, char *buf, int size)
{
    int i = 0;
    for (i = 0; i < size; i++) {
#if (APP_DEBUG_UART_NUM == BSP_UART_NUM_1)
        // bsp_dma_restart(BSP_DMA_CH_USART1_TX, (uint32_t)&USART1->DATAR, (uint32_t)buf, size);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        USART_SendData(USART1, *buf++);
#elif (APP_DEBUG_UART_NUM == BSP_UART_NUM_2)
        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
        USART_SendData(USART2, *buf++);
#elif (APP_DEBUG_UART_NUM == BSP_UART_NUM_3)
        while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
        USART_SendData(USART3, *buf++);
#endif
    }
    return size;
}
