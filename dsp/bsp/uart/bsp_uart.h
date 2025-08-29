#ifndef BSP_UART_H
#define BSP_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


typedef enum {
    BSP_UART_NUM_1,
    BSP_UART_NUM_2,
    BSP_UART_NUM_3,
    BSP_UART_NUM_4,
    BSP_UART_NUM_5,
    BSP_UART_NUM_6,
    BSP_UART_NUM_7,
    BSP_UART_NUM_8,
    BSP_UART_NUM_END,
} bsp_uart_num_t;


void bsp_uart_tx_init(bsp_uart_num_t uart_num, uint32_t baudrate);

#ifdef __cplusplus
}
#endif

#endif
