#include "bsp_usb.h"
#include "usbfs_device.h"
#include "app_usb_uac_tx.h"

#include "app_debug.h"
#include "app_delay.h"


uint8_t app_usb_tx_buf[192] __attribute__((aligned(4)));


void app_usb_init(void)
{
    app_usb_uac_tx_init();

    /* USBFSD device init */
    bsp_usb_init();
    USBFS_Device_Init(ENABLE);
}

void app_usb_runloop(void)
{
    app_usb_uac_tx_handler();
}
