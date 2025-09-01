#include "app_debug.h"
#include "app_usb_uac_tx.h"
#include "usbfs_device.h"

#include "bsp_uart.h"
#include "bsp_dma.h"
#include "bsp_i2s.h"


// #define APP_USB_TX_USE_UART
#define APP_USB_TX_USE_I2S

typedef struct __PACKED {
    uint16_t header;
    uint16_t length;
} data_pack_t, *p_data_pack_t;

uac_headphone_unit_t uac_headphone_unit = {
    .feature_unit.mute     = 0,
    .feature_unit.volume_l = 0x0100,
    .feature_unit.volume_r = 0x0100,
};

volatile uint8_t tx_flag;


uint16_t i2s_tx_buf[192];
uint8_t UART2_Tx_Buffer[DEF_UART2_TX_BUF_SIZE];


void app_usb_uac_tx_init(void)
{
#ifdef APP_USB_TX_USE_UART
    bsp_uart_tx_init(BSP_UART_NUM_2, 4500000);
    bsp_dma_init(BSP_DMA_CH_USART2_TX, (uint32_t)&USART2->DATAR, (uint32_t)Data_Buffer, DEF_RING_BUFFER_PACK_SIZE, BSP_DMA_DIR_DST, BSP_DMA_BYTE_WIDTH_BYTE);
#endif
#ifdef APP_USB_TX_USE_I2S
    bsp_i2s_init(BSP_I2S_NUM_2, BSP_I2S_DIR_TX, BSP_I2S_FREQ_48k, BSP_I2S_FORMAT_16BIT);
    bsp_dma_init(BSP_DMA_CH_I2S2_TX, (uint32_t)&SPI2->DATAR, (uint32_t)i2s_tx_buf, 96, BSP_DMA_DIR_DST, BSP_DMA_BYTE_WIDTH_HALF_WORD);
    bsp_dma_ctrl(BSP_DMA_CH_I2S2_TX, ENABLE);
    while ((!DMA_GetFlagStatus(DMA1_FLAG_TC5))) {};
    // bsp_i2s_init(BSP_I2S_NUM_2);
    // bsp_dma_cmd(BSP_DMA_CH_USART2_TX, ENABLE);
    // bsp_dma_init(BSP_DMA_CH_USART2_TX, (uint32_t)&USART2->DATAR, (uint32_t)Data_Buffer, DEF_RING_BUFFER_PACK_SIZE, BSP_DMA_BYTE_WIDTH_BYTE);
#endif
    tx_flag = 0;
}

extern uint8_t app_usb_tx_buf[192];
void app_usb_uac_tx_handler(void)
{
#ifdef APP_USB_TX_USE_UART
    p_data_pack_t p_data;
    if (tx_flag) {
        if (USART2->STATR & USART_FLAG_TC) {
            USART2->STATR  = (uint16_t)(~USART_FLAG_TC);
            USART2->CTLR3 &= (~USART_DMAReq_Tx);
            tx_flag        = 0x00;
        }
    } else {
        if (RingBuffer_Comm.RemainPack) {
            p_data         = (p_data_pack_t)&Data_Buffer[(RingBuffer_Comm.DealPtr) * DEF_RING_BUFFER_PACK_SIZE];
            p_data->header = 0x785A;
            p_data->length = RingBuffer_Comm.PackLen[RingBuffer_Comm.DealPtr];

            bsp_dma_restart(BSP_DMA_CH_I2S2_TX, (uint32_t)&SPI2->DATAR, (uint32_t)p_data, p_data->length + 4);

            tx_flag = 1;

            NVIC_DisableIRQ(USBFS_IRQn);
            RingBuffer_Comm.RemainPack--;
            RingBuffer_Comm.DealPtr++;
            if (RingBuffer_Comm.DealPtr == DEF_RING_BUFFER_MAX_BLKS) {
                RingBuffer_Comm.DealPtr = 0;
            }
            NVIC_EnableIRQ(USBFS_IRQn);
        }
    }
#endif
#ifdef APP_USB_TX_USE_I2S
    p_data_pack_t p_data;
    if (tx_flag) {
        tx_flag = 0x00;
        bsp_dma_restart(BSP_DMA_CH_I2S2_TX, (uint32_t)&SPI2->DATAR, (uint32_t)app_usb_tx_buf, 96);
        // while ((!DMA_GetFlagStatus(DMA1_FLAG_TC5))) {};
    } else {
        if (RingBuffer_Comm.RemainPack) {
            p_data         = (p_data_pack_t)&Data_Buffer[(RingBuffer_Comm.DealPtr) * DEF_RING_BUFFER_PACK_SIZE];
            p_data->header = 0x785A;
            p_data->length = RingBuffer_Comm.PackLen[RingBuffer_Comm.DealPtr];

            tx_flag = 1;

            NVIC_DisableIRQ(USBFS_IRQn);
            RingBuffer_Comm.RemainPack--;
            RingBuffer_Comm.DealPtr++;
            if (RingBuffer_Comm.DealPtr == DEF_RING_BUFFER_MAX_BLKS) {
                RingBuffer_Comm.DealPtr = 0;
            }
            NVIC_EnableIRQ(USBFS_IRQn);
        }
    }
#endif
}
