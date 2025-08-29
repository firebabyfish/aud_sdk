#include "ch32v30x.h"
#include "bsp_i2s.h"


void bsp_i2s_init(bsp_i2s_num_t i2s_num, bsp_i2s_dir_t dir, bsp_i2s_freq_t aud_freq, bsp_i2s_format_t format)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    I2S_InitTypeDef I2S_InitStructure   = {0};

    if (i2s_num == BSP_I2S_NUM_1) {
        return;
    }

    if (dir == BSP_I2S_DIR_TX) {
        I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;
    } else {
        I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveRx;
    }

    switch (aud_freq) {
        case BSP_I2S_FREQ_DEFAULT:
            I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_Default;
            break;
        case BSP_I2S_FREQ_8k:
            I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_8k;
            break;
        case BSP_I2S_FREQ_11k:
            I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_11k;
            break;
        case BSP_I2S_FREQ_16k:
            I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_16k;
            break;
        case BSP_I2S_FREQ_22k:
            I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_22k;
            break;
        case BSP_I2S_FREQ_32k:
            I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_32k;
            break;
        case BSP_I2S_FREQ_44k:
            I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_44k;
            break;
        case BSP_I2S_FREQ_48k:
            I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_48k;
            break;
        case BSP_I2S_FREQ_96k:
            I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_96k;
            break;
        case BSP_I2S_FREQ_192k:
            I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_192k;
            break;
    }

    switch (format) {
        case BSP_I2S_FORMAT_16BIT:
            I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
            break;
        case BSP_I2S_FORMAT_16BIT_EXT:
            I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16bextended;
            break;
        case BSP_I2S_FORMAT_24BIT:
            I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_24b;
            break;
        case BSP_I2S_FORMAT_32BIT:
            I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_32b;
            break;
    }

    I2S_InitStructure.I2S_Standard   = I2S_Standard_Phillips;
    I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
    I2S_InitStructure.I2S_CPOL       = I2S_CPOL_Low;

    switch (i2s_num) {
        case BSP_I2S_NUM_1:
            break;
        case BSP_I2S_NUM_2: {
            SPI_I2S_DeInit(SPI2);

            RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

            GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOC, &GPIO_InitStructure);

            I2S_Init(SPI2, &I2S_InitStructure);
            SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
            I2S_Cmd(SPI2, ENABLE);
        } break;
        case BSP_I2S_NUM_3: {
            SPI_I2S_DeInit(SPI3);
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

            GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3 | GPIO_Pin_5;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOB, &GPIO_InitStructure);

            I2S_Init(SPI3, &I2S_InitStructure);
            I2S_Cmd(SPI3, ENABLE);
        } break;
        default:
            break;
    }
}
