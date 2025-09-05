#include "app_system.h"
#include "app_delay.h"
#include "app_debug.h"
#include "app_log.h"
#include "app_usb_audio.h"

#include <stdio.h>


int main(void)
{
    // Initialize NVIC, system clock and timer
    app_system_init();
    // Initialize debug uart, use baudrate 3M for output in interrupt
    app_debug_init(3000000);
    // Initialize easylogger
    app_log_init();
    // Initialize delay function
    app_delay_init();
    // Initialize usb device: UAC2.0
    app_usb_audio_init(0, 0x50000000);

    while (1) {
        // USB device tx and rx handler
        app_usb_audio_runloop(0);
    }
}
