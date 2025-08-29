#include "usbfs_device.h"
#include "app_delay.h"


const uint8_t *p_usbfs_descr;

volatile uint8_t usbfs_setup_req_code;
volatile uint8_t usbfs_setup_req_type;
volatile uint16_t usbfs_setup_req_value;
volatile uint16_t usbfs_setup_req_index;
volatile uint16_t usbfs_setup_req_len;

volatile uint8_t usbfs_dev_config;
volatile uint8_t usbfs_dev_addr;
volatile uint8_t usbfs_dev_sleep_status;
volatile uint8_t usbfs_dev_enum_status;
volatile uint8_t usbfs_interface;

__attribute__((aligned(4))) uint8_t usbfs_ep0_buf[DEF_USBD_UEP0_SIZE];
__attribute__((aligned(4))) uint8_t usbfs_ep3_buf[DEF_USBD_EP3_FS_SIZE];
volatile uint8_t usbfs_endp_busy[DEF_UEP_NUM];

RING_BUFF_COMM ring_buffer_comm;
__attribute__((aligned(4))) uint8_t data_buffer[DEF_RING_BUFFER_SIZE];

void USBFS_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void usbfs_rcc_init(void)
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

void usbfs_device_endp_init(void)
{
    USBFSD->UEP2_3_MOD = USBFS_UEP3_RX_EN;

    USBFSD->UEP0_DMA = (uint32_t)usbfs_ep0_buf;
    USBFSD->UEP3_DMA = (uint32_t)usbfs_ep3_buf;

    USBFSD->UEP0_RX_CTRL = USBFS_UEP_R_RES_ACK;
    USBFSD->UEP3_RX_CTRL = USBFS_UEP_R_RES_ACK;

    for (uint8_t i = 0; i < DEF_UEP_NUM; i++) {
        usbfs_endp_busy[i] = 0;
    }
}

void usbfs_device_init(FunctionalState sta)
{
    if (sta) {
        USBFSH->BASE_CTRL = USBFS_UC_RESET_SIE | USBFS_UC_CLR_ALL;
        app_delay_us(10);
        USBFSH->BASE_CTRL = 0x00;
        USBFSD->INT_EN    = USBFS_UIE_SUSPEND | USBFS_UIE_BUS_RST | USBFS_UIE_TRANSFER;
        USBFSD->BASE_CTRL = USBFS_UC_DEV_PU_EN | USBFS_UC_INT_BUSY | USBFS_UC_DMA_EN;
        USBFS_Device_Endp_Init();
        USBFSD->UDEV_CTRL = USBFS_UD_PD_DIS | USBFS_UD_PORT_EN;
        NVIC_EnableIRQ(USBFS_IRQn);
    } else {
        USBFSH->BASE_CTRL = USBFS_UC_RESET_SIE | USBFS_UC_CLR_ALL;
        app_delay_us(10);
        USBFSH->BASE_CTRL = 0x00;
        NVIC_DisableIRQ(USBFS_IRQn);
    }
}

uint8_t usbfs_endp_dataup(uint8_t endp, uint8_t *pbuf, uint16_t len, uint8_t mod)
{
    
}
