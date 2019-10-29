#include <kernel/spi.h>
#include <kernel/delays.h>
#include <common/stdio2.h>
#include <common/stdlib.h>

#define SPI_CS          ((volatile unsigned int*)(MMIO_BASE+0x00204000))
#define SPI_FIFO        ((volatile unsigned int*)(MMIO_BASE+0x00204004))
#define SPI_CLK         ((volatile unsigned int*)(MMIO_BASE+0x00204008))
#define SPI_DLEN        ((volatile unsigned int*)(MMIO_BASE+0x0020400C))
#define SPI_LTOH        ((volatile unsigned int*)(MMIO_BASE+0x00204010))
#define SPI_DC          ((volatile unsigned int*)(MMIO_BASE+0x00204014))

void spi_init()
{
    register unsigned int r;
    spi_control_t control;
    char tempStr[21];

    wait_msec_st(1000000);

    /* map SPI to GPIO pins */
    r=*GPFSEL0;
    r&=~((7<<24)|(7<<27));
    r|=(4<<24)|(4<<27);
    *GPFSEL0 = r;

    r=*GPFSEL1;
    r&=~((7)|(7<<3));
    r|=(4)|(4<<3);
    *GPFSEL1 = r;

    *GPPUD = 0;
    wait_cycles(150);
    *GPPUDCLK0 = (1<<8)|/*(1<<9)|*/(1<<10)|(1<<11);
    wait_cycles(150);
    *GPPUDCLK0 = 0;

    *SPI_CLK = 0;

    wait_msec_st(1000000);

    control.as_int = 0;
    control.chip_select = 0;
    control.clock_polarity = 0;
    control.clock_phase = 0;
    control.clear_fifo = 3;
    control.transfer_active = 0;

    *SPI_CS = control.as_int;

    int j = 1;
    while(1)
    {
        control.as_int = *SPI_CS;
        control.transfer_active = 1;
        *SPI_CS = control.as_int;

        for(int i = 0 ; i < j ; i++)
        {
            control.as_int = *SPI_CS;
            while(control.tx_fifo_ready == 0)
                {/*printf2("1\n", j);*/ control.as_int = *SPI_CS;}
            *SPI_FIFO = 0x0F00;
        }

        control.as_int = *SPI_CS;
        while(control.tx_fifo_ready == 0)
            {/*printf2("1\n", j);*/ control.as_int = *SPI_CS;}
        *SPI_FIFO = 0x0F01;

        control.as_int = *SPI_CS;
        while(control.transfer_done == 0)
            {/*printf2("2\n", j);*/ control.as_int = *SPI_CS;}
        control.transfer_active = 0;
        *SPI_CS = control.as_int;

        control.as_int = *SPI_CS;
        while(control.rx_fifo_ready == 1)
        {
            /*printf2("1\n", j);*/
            control.as_int = *SPI_FIFO;
            control.as_int = *SPI_CS;
        }

        printf2("Done, j = %d\n", j);

        wait_msec(1000000);

        j++;
        if(j > 6)
            j = 1;
    }
    /*wait_msec_st(100000);

    control.as_int = *SPI_CS;
    control.transfer_active = 1;
    *SPI_CS = control.as_int;

    control.as_int = *SPI_CS;

    while(control.tx_fifo_ready == 0)
        control.as_int = *SPI_CS;

    *SPI_FIFO = 0x0F01;

    control.as_int = *SPI_CS;

    while(control.transfer_done == 0)
        control.as_int = *SPI_CS;

    control.transfer_active = 0;
    *SPI_CS = control.as_int;*/
}
