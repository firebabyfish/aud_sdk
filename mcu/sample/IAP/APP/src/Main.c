/********************************** (C) COPYRIGHT *******************************
 * File Name          : Main.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2022/03/15
 * Description        : USB IAP APP����
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "CH58x_common.h"
#include "app_flag.h"

/*********************************************************************
 * @fn      DebugInit
 *
 * @brief   ���Գ�ʼ��
 *
 * @return  none
 */
void DebugInit(void)
{
    GPIOA_SetBits(GPIO_Pin_14);
    GPIOPinRemap(ENABLE, RB_PIN_UART0);
    GPIOA_ModeCfg(GPIO_Pin_15, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeOut_PP_5mA);
    UART0_DefInit();
}

/*********************************************************************
 * @fn      main
 *
 * @brief   ������
 *
 * @return  none
 */
int main()
{
    uint16_t i = 0;
    uint8_t  s = 0;

    HSECFG_Capacitance(HSECap_18p);
    SetSysClock(CLK_SOURCE_HSE_PLL_62_4MHz);

    /* ���ô��ڵ��� */
    DebugInit();
    PRINT("Start @ChipID=%02x\n", R8_CHIP_ID);
    /* app�������ִ�и���䣬��֤app����ʧ��ʱ���´���Ȼ����IAP */
    SwitchImageFlag(FLAG_USER_CALL_APP);

    GPIOB_ModeCfg(GPIO_Pin_4, GPIO_ModeIN_PU);
    while (1)
    {
		PRINT("i:%d\n",i);
		i++;
		DelayMs(10);
		if (GPIOB_ReadPortPin(GPIO_Pin_4) == 0)
		{
			s++;
			//�������μ�⵽�������£���ת��IAP
			if(s >= 2)
			{
				jumpToIap();
			}
		}
		else
		{
			s = 0;
		}
		DelayMs(100);
    }
}
