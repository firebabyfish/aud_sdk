#include "ch32v30x.h"
#include "bsp_uart.h"


void bsp_uart_tx_init(bsp_uart_num_t uart_num, uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure   = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    uint16_t tx_pin          = 0;
    GPIO_TypeDef *gpio_port  = NULL;
    USART_TypeDef *uart_port = NULL;

    switch (uart_num) {
        case BSP_UART_NUM_1:
            tx_pin    = GPIO_Pin_9;
            gpio_port = GPIOA;
            uart_port = USART1;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
            break;
        case BSP_UART_NUM_2:
            tx_pin    = GPIO_Pin_2;
            gpio_port = GPIOA;
            uart_port = USART2;
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
            break;
        case BSP_UART_NUM_3:
            tx_pin    = GPIO_Pin_10;
            gpio_port = GPIOB;
            uart_port = USART3;
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
            break;
        default:
            break;
    }

    GPIO_InitStructure.GPIO_Pin   = tx_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(gpio_port, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = baudrate;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Tx;
    USART_Cmd(uart_port, DISABLE);
    USART_Init(uart_port, &USART_InitStructure);
    // USART_ClearFlag(uart_port, USART_FLAG_TC);
    USART_Cmd(uart_port, ENABLE);
}
