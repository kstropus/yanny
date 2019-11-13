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

void write_fifo(uint8_t data)
{
    spi_control_t control;

    control.as_int = *SPI_CS;

    while(control.tx_fifo_ready != 1)
        control.as_int = *SPI_CS;

    *SPI_FIFO = data;
}

void write_fifo_16(uint16_t data)
{
    spi_control_t control;

    control.as_int = *SPI_CS;

    while(control.tx_fifo_ready != 1)
        control.as_int = *SPI_CS;

    *SPI_FIFO = data;
}

bool read_fifo(uint8_t* data)
{
    spi_control_t control;

    control.as_int = *SPI_CS;

    if(control.rx_fifo_ready == 1)
    {
        *data = *SPI_FIFO;
        return true;
    }

    return false;
}

void begin_transfer()
{
    spi_control_t control;

    control.as_int = *SPI_CS;

    control.clear_fifo = 3;
    control.transfer_active = 1;

    *SPI_CS = control.as_int;
}

void end_transfer()
{
    spi_control_t control;

    control.as_int = *SPI_CS;

    while(control.transfer_done != 1)
        control.as_int = *SPI_CS;

    control.transfer_active = 0;

    *SPI_CS = control.as_int;
}

void execute_transfer(uint8_t* buffer, int offset, int length)
{
    begin_transfer();

    for(int i = 0; i < length; i++)
    {
        *SPI_FIFO = buffer[offset + i];

        if(i >= 16)
        {
            int junk = *SPI_FIFO;
        }
    }

    end_transfer();
}

void spi_init()
{
    register unsigned int r;
    spi_control_t control;
    char tempStr[21];

    printf2("Setting up SPI GPIO\n");

    r=*GPFSEL0;
    r&=~((7<<24)|(7<<27));
    r|=(4<<24)|(4<<27);
    *GPFSEL0 = r;

    r=*GPFSEL1;
    r&=~((7)|(7<<3));
    r|=(4)|(4<<3);
    *GPFSEL1 = r;

    r=*GPFSEL2;
    r&=~(7<<15);
    r|=(1<<15);
    *GPFSEL2 = r;

    /*printf2("Waiting 2 secs...\n");

    wait_msec_st(2000000);*/

    *GPPUD = 1;
    wait_cycles(150);
    //*GPPUDCLK0 = (1<<8)|/*(1<<9)|*/(1<<10)|(1<<11);
    *GPPUDCLK0 = (1<<25);
    wait_cycles(150);
    *GPPUDCLK0 = 0;

    *SPI_CLK = 18;

    *SPI_CS = 0;

    r = *GPLEV0;
    r |= 1 << 25;
    *GPLEV0 = r;

    /*printf2("Waiting 2 secs...\n");

    wait_msec_st(2000000);*/

    uint8_t buffer[16];
    uint8_t buffer2[8];

    bzero(buffer2, 8);

    /*printf2("Writing 0x0000 (nop) to all\n");

    wait_msec_st(1000000);

    execute_transfer(buffer2, 0, 2);

    wait_msec_st(1000000);*/

    buffer[0] = 0x0C;
    buffer[1] = 0x01;
    buffer[2] = 0x0C;
    buffer[3] = 0x01;
    buffer[4] = 0x0C;
    buffer[5] = 0x01;
    buffer[6] = 0x0C;
    buffer[7] = 0x01;

    printf2("Writing 0x0C01 (Shutdown off) to all\n");

    execute_transfer(buffer, 0, 8);

    wait_msec_st(1000000);

    /*buffer[0] = 0x0F;
    buffer[1] = 0x01;
    buffer[2] = 0x0F;
    buffer[3] = 0x01;
    buffer[4] = 0x0F;
    buffer[5] = 0x01;
    buffer[6] = 0x0F;
    buffer[7] = 0x01;

    printf2("Writing 0x0F01 (Display Test on) to all\n");

    execute_transfer(buffer, 0, 8);*/

    //wait_msec_st(1000000);

    buffer[0] = 0x0F;
    buffer[1] = 0x00;
    buffer[2] = 0x0F;
    buffer[3] = 0x00;
    buffer[4] = 0x0F;
    buffer[5] = 0x00;
    buffer[6] = 0x0F;
    buffer[7] = 0x00;

    printf2("Writing 0x0F00 (Display Test off) to all\n");

    execute_transfer(buffer, 0, 8);

    //wait_msec_st(1000000);

    buffer[0] = 0x0B;
    buffer[1] = 0x07;
    buffer[2] = 0x0B;
    buffer[3] = 0x07;
    buffer[4] = 0x0B;
    buffer[5] = 0x07;
    buffer[6] = 0x0B;
    buffer[7] = 0x07;

    printf2("Writing 0x0B07 (Scan all) to all\n");

    execute_transfer(buffer, 0, 8);

    //wait_msec_st(1000000);

    buffer[0] = 0x0A;
    buffer[1] = 0x01;
    buffer[2] = 0x0A;
    buffer[3] = 0x01;
    buffer[4] = 0x0A;
    buffer[5] = 0x01;
    buffer[6] = 0x0A;
    buffer[7] = 0x01;

    printf2("Writing 0x0A01 (Intens) to all\n");

    execute_transfer(buffer, 0, 8);

    //wait_msec_st(1000000);

    bzero(buffer, 8);

    printf2("Blanking all\n");

    bzero(buffer, 8);

    for(int i = 1 ; i <= 8 ; i++)
    {
        buffer[0] = i;
        buffer[2] = i;
        buffer[4] = i;
        buffer[6] = i;

        execute_transfer(buffer, 0, 8);
    }

    while(1)
    {
        /*printf2("Writing 0x0000 (nop) to all\n");

        wait_msec_st(1000000);

        execute_transfer(buffer2, 0, 2);

        wait_msec_st(1000000);*/

        buffer[0] = 0x04;
        buffer[1] = 0x55;
        buffer[2] = 0x04;
        buffer[3] = 0x55;
        buffer[4] = 0x04;
        buffer[5] = 0x55;
        buffer[6] = 0x04;
        buffer[7] = 0x55;

        printf2("Writing 0x0F01 (Display Test on) to first\n");

        execute_transfer(buffer, 0, 8);

        wait_msec_st(100000);

        /*printf2("Writing 0x0000 (nop) to all\n");

        wait_msec_st(1000000);

        execute_transfer(buffer2, 0, 2);

        wait_msec_st(1000000);*/

        buffer[0] = 0x04;
        buffer[1] = 0xAA;
        buffer[2] = 0x04;
        buffer[3] = 0xAA;
        buffer[4] = 0x04;
        buffer[5] = 0xAA;
        buffer[6] = 0x04;
        buffer[7] = 0xAA;

        printf2("Writing 0x0F01 (Display Test on) to first\n");

        execute_transfer(buffer, 0, 8);

        wait_msec_st(1000000);
    }

    /*wait_msec_st(2000000);

    buffer[0] = 0x0B;
    buffer[1] = 0x07;
    buffer[2] = 0x0B;
    buffer[3] = 0x07;
    buffer[4] = 0x0B;
    buffer[5] = 0x07;
    buffer[6] = 0x0B;;
    buffer[7] = 0x07;

    execute_transfer(buffer, 0, 8);

    wait_msec_st(2000000);

    buffer[0] = 0x0A;
    buffer[1] = 0x01;
    buffer[2] = 0x0A;
    buffer[3] = 0x01;
    buffer[4] = 0x0A;
    buffer[5] = 0x01;
    buffer[6] = 0x0A;
    buffer[7] = 0x0F;
    buffer[8] = 0x0A;
    buffer[9] = 0x01;
    buffer[10] = 0x0A;
    buffer[11] = 0x01;
    buffer[12] = 0x0A;
    buffer[13] = 0x01;
    buffer[14] = 0x0A;
    buffer[15] = 0x0F;

    int i = 0;

    while(1)
    {
        execute_transfer(buffer, i, 8);

        i += 2;
        if(i == 8)
            i = 0;

        wait_msec_st(1000000);
    }*/
}

void spi_init_oled()
{
    register unsigned int r;
    spi_control_t control;
    char tempStr[21];

    printf2("Setting up SPI GPIO\n");

    r=*GPFSEL0;
    r&=~((7<<24)|(7<<27));
    r|=(4<<24)|(4<<27);
    *GPFSEL0 = r;

    r=*GPFSEL1;
    r&=~((7)|(7<<3));
    r|=(4)|(4<<3);
    *GPFSEL1 = r;

    r=*GPFSEL2;
    r&=~(7<<15);
    r|=(1<<15);
    *GPFSEL2 = r;

    /*printf2("Waiting 2 secs...\n");

    wait_msec_st(2000000);*/

    *GPPUD = 1;
    wait_cycles(150);
    //*GPPUDCLK0 = (1<<8)|/*(1<<9)|*/(1<<10)|(1<<11);
    *GPPUDCLK0 = (1<<25);
    wait_cycles(150);
    *GPPUDCLK0 = 0;

    *SPI_CLK = 0;

    control.as_int = 0;
    control.lossi_enable = 1;
    control.clock_phase = 1;
    control.clock_polarity = 0;
    control.chip_select = 0;
    *SPI_CS = control.as_int;

    printf2("Waiting 1 sec...\n");

    wait_msec_st(1000000);

    uint8_t buffer[16];
    uint8_t buffer2[8];

    bzero(buffer2, 8);

    buffer[0] = 0x0C;
    buffer[1] = 0x01;
    buffer[2] = 0x0C;
    buffer[3] = 0x01;
    buffer[4] = 0x0C;
    buffer[5] = 0x01;
    buffer[6] = 0x0C;
    buffer[7] = 0x01;

    while(1)
    {
        printf2("Writing 0x00A5 (All on)\n");

        begin_transfer();

        write_fifo_16(0x00A5);

        end_transfer();

        wait_msec_st(1000000);

        printf2("Writing 0x00A4 (All off)\n");

        begin_transfer();

        write_fifo_16(0x00A4);

        end_transfer();

        wait_msec_st(1000000);
    }
}
