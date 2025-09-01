#include "app_system.h"
#include "app_delay.h"
#include "app_debug.h"
#include "app_log.h"

#include <stdio.h>

#include "ch32v30x.h"
#include "bsp_dma.h"
#include "bsp_uart.h"
#include "bsp_i2s.h"


void app_test(void);
void app_usb_init(void);
void app_usb_runloop(void);


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
    // Initialize usb device: UAC1.0
    app_usb_init();

    while (1) {
        // USB device tx and rx handler
        app_usb_runloop();
    }
}
