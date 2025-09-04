#include "ch32v30x.h"
#include "ch32v30x_usb.h"

#include "bsp_usb.h"


bsp_usb_delay_cb_t bsp_usb_delay_us = NULL;
bsp_usb_delay_cb_t bsp_usb_delay_ms = NULL;


void bsp_usb_rcc_init(void)
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

void bsp_usb_delay_init(bsp_usb_delay_cb_t us_cb, bsp_usb_delay_cb_t ms_cb)
{
    bsp_usb_delay_us = us_cb;
    bsp_usb_delay_ms = ms_cb;
}

void bsp_usbfs_device_init(uint8_t en)
{
    // if (en) {
    //     USBFSH->BASE_CTRL = USBFS_UC_RESET_SIE | USBFS_UC_CLR_ALL;
    //     bsp_usb_delay_us(10);
    //     USBFSH->BASE_CTRL = 0x00;
    //     USBFSD->INT_EN    = USBFS_UIE_SUSPEND | USBFS_UIE_BUS_RST | USBFS_UIE_TRANSFER;
    //     USBFSD->BASE_CTRL = USBFS_UC_DEV_PU_EN | USBFS_UC_INT_BUSY | USBFS_UC_DMA_EN;
    //     USBFS_Device_Endp_Init();
    //     USBFSD->UDEV_CTRL = USBFS_UD_PD_DIS | USBFS_UD_PORT_EN;
    //     NVIC_EnableIRQ(USBFS_IRQn);
    // } else {
    //     USBFSH->BASE_CTRL = USBFS_UC_RESET_SIE | USBFS_UC_CLR_ALL;
    //     bsp_usb_delay_us(10);
    //     USBFSH->BASE_CTRL = 0x00;
    //     NVIC_DisableIRQ(USBFS_IRQn);
    // }
}

void bsp_usb_init(void)
{
    bsp_usb_rcc_init();
}
