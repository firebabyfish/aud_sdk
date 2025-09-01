#include "bsp_dma.h"


void bsp_dma_cmd(DMA_Channel_TypeDef *dma_ch, uint8_t en)
{
    switch ((uint32_t)dma_ch) {
        case (uint32_t)BSP_DMA_CH_USART1_TX:
            USART_DMACmd(USART1, USART_DMAReq_Tx, en);
            break;
        case (uint32_t)BSP_DMA_CH_USART2_TX:
            USART_DMACmd(USART2, USART_DMAReq_Tx, en);
            break;
        case (uint32_t)BSP_DMA_CH_I2S2_TX:
            SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, en);
            break;
        case (uint32_t)BSP_DMA_CH_I2S3_RX:
            SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Rx, en);
            break;
        default:
            break;
    }
}

void bsp_dma_init(DMA_Channel_TypeDef *dma_ch, uint32_t peri_addr, uint32_t mem_addr, uint16_t buf_size, bsp_dma_dir_t dir, bsp_dma_byte_width_t byte_width)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    if (dma_ch < DMA2_Channel1) {
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    } else {
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
    }
    DMA_DeInit(dma_ch);

    switch (byte_width) {
        case BSP_DMA_BYTE_WIDTH_BYTE:
            DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
            DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
            break;
        case BSP_DMA_BYTE_WIDTH_HALF_WORD:
            DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
            DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
            break;
        case BSP_DMA_BYTE_WIDTH_WORD:
            DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
            DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Word;
            break;
        default:
            break;
    }

    if (dir == BSP_DMA_DIR_SRC) {
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    } else {
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    }

    DMA_InitStructure.DMA_PeripheralBaseAddr = peri_addr;
    DMA_InitStructure.DMA_MemoryBaseAddr     = mem_addr;
    DMA_InitStructure.DMA_BufferSize         = buf_size;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;

    DMA_Init(dma_ch, &DMA_InitStructure);
    bsp_dma_cmd(dma_ch, ENABLE);
}

void bsp_dma_ctrl(DMA_Channel_TypeDef *dma_ch, uint8_t en)
{
    DMA_Cmd(dma_ch, en);
}

void bsp_dma_restart(DMA_Channel_TypeDef *dma_ch, uint32_t peri_addr, uint32_t mem_addr, uint16_t buf_size)
{
    bsp_dma_ctrl(dma_ch, DISABLE);
    dma_ch->PADDR = peri_addr;
    dma_ch->MADDR = mem_addr;
    dma_ch->CNTR  = buf_size;
    bsp_dma_ctrl(dma_ch, ENABLE);
}
