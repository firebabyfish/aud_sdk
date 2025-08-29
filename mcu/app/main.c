#include "CH58x_common.h"
#include "bsp_clock.h"
#include "bsp_timer.h"
#include "bsp_uart.h"
#include "bsp_usb.h"

#include "app_delay.h"
#define LOG_TAG "main"
#include "app_log.h"


int main(void)
{
    bsp_clock_init();
    bsp_uart_init();
    bsp_timer_init();
    bsp_usb_audio_init();

    app_log_init();

    while (1) {
        audio_v2_test(0);
    }
}
