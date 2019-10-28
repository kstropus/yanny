#ifndef SPI_H
#define SPI_H

#include <common/stdint.h>
#include <kernel/gpio.h>

typedef union spi_control {
    struct {
        uint32_t chip_select: 2;
        uint32_t clock_phase: 1;
        uint32_t clock_polarity: 1;
        uint32_t clear_fifo: 2;
        uint32_t chip_select_polatiry: 1;
        uint32_t transfer_active: 1;
        uint32_t dma_enable: 1;
        uint32_t interrupt_on_done: 1;
        uint32_t interrupt_on_rxr: 1;
        uint32_t auto_deassert_cs: 1;
        uint32_t read_enable: 1;
        uint32_t lossi_enable: 1;
        uint32_t _unused: 2;
        uint32_t transfer_done: 1;
        uint32_t rx_fifo_ready: 1;
        uint32_t tx_fifo_ready: 1;
        uint32_t rx_fifo_should_read: 1;
        uint32_t rx_fifo_full: 1;
        uint32_t chip_select_0_polarity: 1;
        uint32_t chip_select_1_polarity: 1;
        uint32_t chip_select_2_polarity: 1;
        uint32_t dma_lossi_enable: 1;
        uint32_t lossi_enable_long: 1;
        uint32_t _padding: 6;
    };
    uint32_t as_int;
} spi_control_t;

typedef union spi_clock {
    struct {
        uint32_t clock_divider: 16;
        uint32_t _padding: 16;
    };
    uint32_t as_int;
} spi_clock_t;

void spi_init();

#endif
