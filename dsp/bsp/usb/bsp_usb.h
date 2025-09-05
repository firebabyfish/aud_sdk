#ifndef __BSP_USB_H__
#define __BSP_USB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


void bsp_usb_init(void);
void bsp_usb_irq_enable(void);


#ifdef __cplusplus
}
#endif

#endif
