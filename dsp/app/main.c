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


uint16_t i2s_temp_buf[10] = {0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0x0000};


int main(void)
{
    app_system_init();
    app_debug_init(921600);
    app_log_init();
    app_delay_init();

    app_usb_init();

    while (1) {
        app_usb_runloop();
    }
}
