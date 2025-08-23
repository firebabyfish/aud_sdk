/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.1
 * Date               : 2019/11/05
 * Description        : �����ӻ�Ӧ��������������ϵͳ��ʼ��
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/******************************************************************************/
/* ͷ�ļ����� */
#include "CONFIG.h"
#include "HAL.h"
#include "Peripheral.h"
#include "OTA.h"
#include "OTAprofile.h"

/* ��¼��ǰ��Image */
unsigned char CurrImageFlag = 0xff;

/*********************************************************************
 * GLOBAL TYPEDEFS
 */
__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

/* ע�⣺���ڳ���������flash�Ĳ���������ִ�У��������κ��жϣ���ֹ�����жϺ�ʧ�� */
/*********************************************************************
 * @fn      ReadImageFlag
 *
 * @brief   ��ȡ��ǰ�ĳ����Image��־��DataFlash���Ϊ�գ���Ĭ����ImageA�����ΪImageA������תImageA
 *
 * @return  none
 */
void ReadImageFlag(void)
{
    OTADataFlashInfo_t p_image_flash;

    EEPROM_READ(OTA_DATAFLASH_ADD, &p_image_flash, 4);
    CurrImageFlag = p_image_flash.ImageFlag;

    /* �����һ��ִ�У�����û�и��¹����Ժ���º��ڲ���DataFlash */
    if((CurrImageFlag != IMAGE_B_FLAG) && (CurrImageFlag != IMAGE_A_FLAG) && (CurrImageFlag != IMAGE_OTA_FLAG))
    {
        CurrImageFlag = IMAGE_A_FLAG;
    }

    PRINT("Image Flag %02x\n", CurrImageFlag);

    if(CurrImageFlag == IMAGE_A_FLAG)
    {
        PRINT("jump App \n");
        mDelaymS(5);
        jumpApp();
    }
}

/*********************************************************************
 * @fn      Main_Circulation
 *
 * @brief   ��ѭ��
 *
 * @return  none
 */
__HIGH_CODE
__attribute__((noinline))
void Main_Circulation()
{
    while(1)
    {
        TMOS_SystemProcess();
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   ������
 *
 * @return  none
 */
int main(void)
{
#if(defined(DCDC_ENABLE)) && (DCDC_ENABLE == TRUE)
    PWR_DCDCCfg(ENABLE);
#endif
    HSECFG_Capacitance(HSECap_18p);
    SetSysClock(CLK_SOURCE_HSE_PLL_62_4MHz);
#if(defined(HAL_SLEEP)) && (HAL_SLEEP == TRUE)
    GPIOA_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
#endif
#ifdef DEBUG
    GPIOA_SetBits(GPIO_Pin_14);
    GPIOPinRemap(ENABLE, RB_PIN_UART0);
    GPIOA_ModeCfg(GPIO_Pin_15, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeOut_PP_5mA);
    UART0_DefInit();
#endif
    PRINT("%s\n", VER_LIB);
    ReadImageFlag();
    if((R8_RESET_STATUS & RB_RESET_FLAG) == RST_FLAG_SW)
    {
        // ��λ����APP
    }
    else
    {
        if(CurrImageFlag == IMAGE_OTA_FLAG)
        {
            PRINT("jump App \n");
            mDelaymS(5);
            jumpApp();
        }
    }
    CH58x_BLEInit();
    HAL_Init();
    GAPRole_PeripheralInit();
    Peripheral_Init();
    Main_Circulation();
}

/******************************** endfile @ main ******************************/
