#include "debug.h"
#include "string.h"

/* Global Variable */
#define Len 10

u16 I2S2_Tx[Len] = {0x0000, 0x2222, 0x3333, 0x0000, 0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0x0000};
u16 I2S3_Rx[Len];


/*********************************************************************
 * @fn      I2S2_Init
 *
 * @brief   Init I2S2
 *
 * @return  none
 */
void I2S2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    I2S_InitTypeDef I2S_InitStructure   = {0};

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

    I2S_InitStructure.I2S_Mode       = I2S_Mode_MasterTx;
    I2S_InitStructure.I2S_Standard   = I2S_Standard_Phillips;
    I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
    I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
    I2S_InitStructure.I2S_AudioFreq  = I2S_AudioFreq_48k;
    I2S_InitStructure.I2S_CPOL       = I2S_CPOL_Low;
    I2S_Init(SPI2, &I2S_InitStructure);

    SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
    I2S_Cmd(SPI2, ENABLE);
}

/*********************************************************************
 * @fn      I2S3_Init
 *
 * @brief   Init I2S2
 *
 * @return  none
 */
void I2S3_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    I2S_InitTypeDef I2S_InitStructure   = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);


    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2S_InitStructure.I2S_Mode       = I2S_Mode_SlaveRx;
    I2S_InitStructure.I2S_Standard   = I2S_Standard_Phillips;
    I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
    I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
    I2S_InitStructure.I2S_AudioFreq  = I2S_AudioFreq_48k;
    I2S_InitStructure.I2S_CPOL       = I2S_CPOL_High;
    I2S_Init(SPI3, &I2S_InitStructure);

    SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Rx, ENABLE);
    I2S_Cmd(SPI3, ENABLE);
}

/*********************************************************************
 * @fn      DMA_Tx_Init
 *
 * @brief   Initializes the DMAy Channelx configuration.
 *
 * @param   DMA_CHx - x can be 1 to 7.
 *          ppadr - Peripheral base address.
 *          memadr - Memory base address.
 *          bufsize - DMA channel buffer size.
 *
 * @return  none
 */
void DMA_Tx_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA_CHx);

    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr     = memadr;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize         = bufsize;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);
}

/*********************************************************************
 * @fn      DMA_Rx_Init
 *
 * @brief   Initializes the I2S3 DMA Channelx configuration.
 *
 * @param   DMA_CHx - x can be 1 to 7.
 *          ppadr - Peripheral base address.
 *          memadr - Memory base address.
 *          bufsize - DMA channel buffer size.
 *
 * @return  none
 */
void DMA_Rx_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    DMA_DeInit(DMA_CHx);

    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr     = memadr;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = bufsize;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
void app_test(void)
{
    u32 i;

    SPI_I2S_DeInit(SPI2);
    // SPI_I2S_DeInit(SPI3);

    I2S2_Init();
    // I2S3_Init();

    // DMA_Rx_Init(DMA2_Channel1, (u32)&SPI3->DATAR, (u32)I2S3_Rx, Len);
    DMA_Tx_Init(DMA1_Channel5, (u32)&SPI2->DATAR, (u32)I2S2_Tx, Len);

    // DMA_Cmd(DMA2_Channel1, ENABLE);
    DMA_Cmd(DMA1_Channel5, ENABLE);

    while ((!DMA_GetFlagStatus(DMA1_FLAG_TC5))) {};
    // while ((!DMA_GetFlagStatus(DMA2_FLAG_TC1))) {};

    // I2S_Cmd(SPI3, DISABLE);
    I2S_Cmd(SPI2, DISABLE);

    printf("Rx data:\r\n");
    for (i = 0; i < Len; i++) {
        printf("%08x %08x\r\n", I2S2_Tx[i], I2S3_Rx[i]);
    }

    while (1);
}
