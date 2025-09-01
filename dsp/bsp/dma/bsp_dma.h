#ifndef __BSP_DMA_H__
#define __BSP_DMA_H__


#include "ch32v30x.h"
#include <stdint.h>
#include <stdbool.h>


#define BSP_DMA_CH_USART1_TX DMA1_Channel4
#define BSP_DMA_CH_USART2_TX DMA1_Channel7
#define BSP_DMA_CH_I2S2_TX   DMA1_Channel5
#define BSP_DMA_CH_I2S3_RX   DMA2_Channel1

typedef enum {
    BSP_DMA_BYTE_WIDTH_BYTE,
    BSP_DMA_BYTE_WIDTH_HALF_WORD,
    BSP_DMA_BYTE_WIDTH_WORD,
} bsp_dma_byte_width_t;

typedef enum {
    BSP_DMA_DIR_SRC,
    BSP_DMA_DIR_DST,
} bsp_dma_dir_t;


void bsp_dma_cmd(DMA_Channel_TypeDef *dma_ch, uint8_t en);
void bsp_dma_init(DMA_Channel_TypeDef *dma_ch, uint32_t peri_addr, uint32_t mem_addr, uint16_t buf_size, bsp_dma_dir_t dir, bsp_dma_byte_width_t byte_width);
void bsp_dma_ctrl(DMA_Channel_TypeDef *dma_ch, uint8_t en);
void bsp_dma_restart(DMA_Channel_TypeDef *dma_ch, uint32_t peri_addr, uint32_t mem_addr, uint16_t buf_size);


#endif  // __BSP_DMA_H__
