#ifndef __APP_USB_AUDIO_H__
#define __APP_USB_AUDIO_H__


#include <stdint.h>


void app_usb_audio_init(uint8_t busid, uintptr_t reg_base);
void app_usb_audio_runloop(uint8_t busid);


#endif
