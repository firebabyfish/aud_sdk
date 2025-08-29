#ifndef BSP_I2S_H
#define BSP_I2S_H


#include <stdint.h>
#include <stdbool.h>


typedef enum {
    BSP_I2S_NUM_1,
    BSP_I2S_NUM_2,
    BSP_I2S_NUM_3,
    BSP_I2S_NUM_END,
} bsp_i2s_num_t;

typedef enum {
    BSP_I2S_DIR_TX,
    BSP_I2S_DIR_RX,
} bsp_i2s_dir_t;

typedef enum {
    BSP_I2S_FREQ_192k,
    BSP_I2S_FREQ_96k,
    BSP_I2S_FREQ_48k,
    BSP_I2S_FREQ_44k,
    BSP_I2S_FREQ_32k,
    BSP_I2S_FREQ_22k,
    BSP_I2S_FREQ_16k,
    BSP_I2S_FREQ_11k,
    BSP_I2S_FREQ_8k,
    BSP_I2S_FREQ_DEFAULT,
} bsp_i2s_freq_t;

typedef enum {
    BSP_I2S_FORMAT_16BIT,
    BSP_I2S_FORMAT_16BIT_EXT,
    BSP_I2S_FORMAT_24BIT,
    BSP_I2S_FORMAT_32BIT,
} bsp_i2s_format_t;


void bsp_i2s_init(bsp_i2s_num_t i2s_num, bsp_i2s_dir_t dir, bsp_i2s_freq_t aud_freq, bsp_i2s_format_t format);


#endif  // BSP_I2S_H
