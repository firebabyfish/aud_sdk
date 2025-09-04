#ifndef __BSP_USB_H__
#define __BSP_USB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


typedef void (*bsp_usb_delay_cb_t)(uint32_t);


void bsp_usb_init(void);

#ifdef __cplusplus
}
#endif

#endif
