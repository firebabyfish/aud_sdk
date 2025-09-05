#include "ch32v30x.h"
#include "ch32v30x_usb.h"

#include "bsp_usb.h"


void bsp_usb_init(void)
{
#ifdef CH32V30x_D8C
    RCC_USBCLK48MConfig(RCC_USBCLK48MCLKSource_USBPHY);
    RCC_USBHSPLLCLKConfig(RCC_HSBHSPLLCLKSource_HSE);
    RCC_USBHSConfig(RCC_USBPLL_Div2);
    RCC_USBHSPLLCKREFCLKConfig(RCC_USBHSPLLCKREFCLK_4M);
    RCC_USBHSPHYPLLALIVEcmd(ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_USBHS, ENABLE);
#else
    if (SystemCoreClock == 144000000) {
        RCC_USBFSCLKConfig(RCC_USBFSCLKSource_PLLCLK_Div3);
    } else if (SystemCoreClock == 96000000) {
        RCC_USBFSCLKConfig(RCC_USBFSCLKSource_PLLCLK_Div2);
    } else if (SystemCoreClock == 48000000) {
        RCC_USBFSCLKConfig(RCC_USBFSCLKSource_PLLCLK_Div1);
    }
#endif
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_USBFS, ENABLE);
}

void bsp_usb_irq_enable(void)
{
    NVIC_EnableIRQ(USBFS_IRQn);
}
