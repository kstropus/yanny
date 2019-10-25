#ifndef PCM_H
#define PCM_H

#include <common/stdint.h>
#include <kernel/gpio.h>

#define PCM_CS_A        ((volatile unsigned int*)(MMIO_BASE+0x00203000))
#define PCM_FIFO_A      ((volatile unsigned int*)(MMIO_BASE+0x00203004))
#define PCM_MODE_A      ((volatile unsigned int*)(MMIO_BASE+0x00203008))
#define PCM_RXC_A       ((volatile unsigned int*)(MMIO_BASE+0x0020300C))
#define PCM_TXC_A       ((volatile unsigned int*)(MMIO_BASE+0x00203010))
#define PCM_DREQ_A      ((volatile unsigned int*)(MMIO_BASE+0x00203014))
#define PCM_INTEN_A     ((volatile unsigned int*)(MMIO_BASE+0x00203018))
#define PCM_INTSTC_A    ((volatile unsigned int*)(MMIO_BASE+0x0020301C))
#define PCM_GRAY        ((volatile unsigned int*)(MMIO_BASE+0x00203020))

typedef union pcm_control {
    struct {
        uint32_t enable_pcm: 1;
        uint32_t rx_enable: 1;
        uint32_t tx_enable: 1;
        uint32_t tx_clear: 1;
        uint32_t rx_clear: 1;
        uint32_t tx_threshold: 2;
        uint32_t rx_threshold: 2;
        uint32_t dma_dreq_enable: 1;
        uint32_t _reserved1: 3;
        uint32_t tx_fifo_sync: 1;
        uint32_t rx_fifo_sync: 1;
        uint32_t tx_fifo_error: 1;
        uint32_t rx_fifo_error: 1;
        uint32_t tx_fifo_panic: 1;
        uint32_t rx_fifo_panic: 1;
        uint32_t tx_fifo_ready: 1;
        uint32_t rx_fifo_ready: 1;
        uint32_t tx_fifo_empty: 1;
        uint32_t rx_fifo_full: 1;
        uint32_t rx_sign_extend: 1;
        uint32_t pcm_clock_sync: 1;
        uint32_t ram_standby: 1;
        uint32_t padding: 6;
    };
    uint32_t as_int;
} pcm_control_t;

typedef union pcm_mode {
    struct {
        uint32_t frame_sync_len: 10;
        uint32_t frame_len: 10;
        uint32_t frame_sync_invert: 1;
        uint32_t frame_sync_mode: 1;
        uint32_t clock_invert: 1;
        uint32_t pcm_clock_mode: 1;
        uint32_t tx_frame_packed: 1;
        uint32_t rx_frame_packed: 1;
        uint32_t pdm_input_enable: 1;
        uint32_t pdm_decimation_factor: 1;
        uint32_t pcm_clock_disable: 1;
        uint32_t padding: 3;
    };
    uint32_t as_int;
} pcm_mode_t;

typedef union pcm_rx_config {
    struct {
        uint32_t ch2_width: 4;
        uint32_t ch2_position: 10;
        uint32_t ch2_enable: 1;
        uint32_t ch2_width_ex: 1;
        uint32_t ch1_width: 4;
        uint32_t ch1_position: 10;
        uint32_t ch1_enable: 1;
        uint32_t ch1_width_ex: 1;
    };
    uint32_t as_int;
} pcm_rx_config_t;

typedef union pcm_tx_config {
    struct {
        uint32_t ch2_width: 4;
        uint32_t ch2_position: 10;
        uint32_t ch2_enable: 1;
        uint32_t ch2_width_ex: 1;
        uint32_t ch1_width: 4;
        uint32_t ch1_position: 10;
        uint32_t ch1_enable: 1;
        uint32_t ch1_width_ex: 1;
    };
    uint32_t as_int;
} pcm_tx_config_t;

typedef union pcm_dma_request {
    struct {
        uint32_t rx_request_level: 7;
        uint32_t _reserved1: 1;
        uint32_t tx_request_level: 7;
        uint32_t _reserved2: 1;
        uint32_t rx_panic_level: 7;
        uint32_t _reserved3: 1;
        uint32_t tx_panic_level: 7;
        uint32_t _reserved4: 1;
    };
    uint32_t as_int;
} pcm_dma_request_t;

void pcm_init();

#endif
