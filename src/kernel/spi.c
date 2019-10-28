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

    wait_msec_st(100);

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
    *GPPUDCLK0 = (1<<8)|(1<<9)|(1<<10)|(1<<11);
    wait_cycles(150);
    *GPPUDCLK0 = 0;

    *SPI_CLK = 0;

    wait_msec_st(100);

    control.as_int = *SPI_CS;
    itoa(control.as_int, 16, tempStr, 20);
    printf2("1.SPI_CS: %s\n", tempStr);

    control.as_int = 0;
    control.chip_select = 0;
    control.clock_polarity = 0;
    control.clock_phase = 0;
    control.clear_fifo = 3;
    control.transfer_active = 1;

    *SPI_CS = control.as_int;

    control.as_int = *SPI_CS;
    itoa(control.as_int, 16, tempStr, 20);
    printf2("2.SPI_CS: %s\n", tempStr);







    /*for(int i = 0 ; i < 4 ; i++)
    {
        control.as_int = *SPI_CS;
        printf2("2.1\n");
        while(control.tx_fifo_ready == 0)
        {
            printf2("2.1.1\n");
            control.as_int = *SPI_CS;
        }
        printf2("2.2\n");
        *SPI_FIFO = 0x0000;
    }*/

    control.as_int = *SPI_CS;
    printf2("3\n");
    while(control.tx_fifo_ready == 0)
    {
        printf2("3.1\n");
        control.as_int = *SPI_CS;
    }
    printf2("4\n");
    *SPI_FIFO = 0x0C01;

    control.as_int = *SPI_CS;
    printf2("3\n");
    while(control.tx_fifo_ready == 0)
    {
        printf2("3.1\n");
        control.as_int = *SPI_CS;
    }
    printf2("4\n");
    *SPI_FIFO = 0x0C01;

    control.as_int = *SPI_CS;
    printf2("3\n");
    while(control.tx_fifo_ready == 0)
    {
        printf2("3.1\n");
        control.as_int = *SPI_CS;
    }
    printf2("4\n");
    *SPI_FIFO = 0x0C01;

    control.as_int = *SPI_CS;
    printf2("3\n");
    while(control.tx_fifo_ready == 0)
    {
        printf2("3.1\n");
        control.as_int = *SPI_CS;
    }
    printf2("4\n");
    *SPI_FIFO = 0x0C01;



    control.as_int = *SPI_CS;
    printf2("11\n");
    while(control.transfer_done == 0)
    {
        printf2("11.1\n");
        control.as_int = *SPI_CS;
    }
    printf2("12\n");
    control.transfer_active = 0;
    *SPI_CS = control.as_int;
    printf2("13\n");


    control.as_int = *SPI_CS;
    control.transfer_active = 1;
    *SPI_CS = control.as_int;



    control.as_int = *SPI_CS;
    printf2("3\n");
    while(control.tx_fifo_ready == 0)
    {
        printf2("3.1\n");
        control.as_int = *SPI_CS;
    }
    printf2("4\n");
    *SPI_FIFO = 0x0F01;

    /*control.as_int = *SPI_CS;
    printf2("5\n");
    while(control.tx_fifo_ready == 0)
    {
        printf2("5.1\n");
        control.as_int = *SPI_CS;
    }
    printf2("6\n");
    *SPI_FIFO = 0x0000;

    control.as_int = *SPI_CS;
    printf2("7\n");
    while(control.tx_fifo_ready == 0)
    {
        printf2("7.1\n");
        control.as_int = *SPI_CS;
    }
    printf2("8\n");
    *SPI_FIFO = 0x0000;

    control.as_int = *SPI_CS;
    printf2("9\n");
    while(control.tx_fifo_ready == 0)
    {
        printf2("9.1\n");
        control.as_int = *SPI_CS;
    }
    printf2("10\n");
    *SPI_FIFO = 0x0000;*/











    control.as_int = *SPI_CS;
    printf2("11\n");
    while(control.transfer_done == 0)
    {
        printf2("11.1\n");
        control.as_int = *SPI_CS;
    }
    printf2("12\n");
    control.transfer_active = 0;
    *SPI_CS = control.as_int;
    printf2("13\n");
    /**CM_PCM_CTRL = 0x5A000021;
    *CM_PCM_DIV = 0x5A006400;
    *CM_PCM_CTRL = 0x5A000211;

    pcm_mode_t mode;
    pcm_tx_config_t tx_config;

    mode.as_int = 0;
    mode.clock_invert = 1;
    //mode.frame_sync_invert = 1;
    mode.frame_len = 63;
    mode.frame_sync_len = 32;

    itoa(mode.as_int, 16, tempStr, 20);

    printf("PCM_MODE_A: %s\n", tempStr);

    *PCM_MODE_A = mode.as_int;
    //*PCM_MODE_A = 0x040FC20;


    tx_config.as_int =0;

    tx_config.ch1_width = 8;
    tx_config.ch1_width_ex = 1;
    tx_config.ch1_position = 1;
    tx_config.ch1_enable = 1;
    tx_config.ch2_width = 8;
    tx_config.ch2_width_ex = 1;
    tx_config.ch2_position = 33;
    tx_config.ch2_enable = 1;
    itoa(tx_config.as_int, 16, tempStr, 20);

    printf("PCM_TXC_A: %s\n", tempStr);
    *PCM_TXC_A = tx_config.as_int;
    //*PCM_TXC_A = 0xC018C218;



    control.as_int = 0;
    control.pcm_clock_sync = 1;
    control.tx_fifo_sync = 1;
    control.tx_threshold = 3;
    control.tx_clear = 1;
    control.enable_pcm = 1;
    itoa(control.as_int, 16, tempStr, 20);

    printf("PCM_CS_A: %s\n", tempStr);
    *PCM_CS_A = control.as_int;

    while(control.pcm_clock_sync == 0)
        control.as_int = *PCM_CS_A;

    long countdown = 15;
    int pcm_data = 65000000;

    while(control.tx_fifo_ready == 1)
    {
        *PCM_FIFO_A = (uint32_t)pcm_data;
        printf2("Write to FIFO\n");

        countdown--;

        if(countdown == 0)
        {
            pcm_data = -pcm_data;
            countdown = 15;
        }
    }

    printf2("FIFO filled, setting tx_enable\n");

    control.as_int = *PCM_CS_A;

    control.tx_enable = 1;

    *PCM_CS_A = control.as_int;

    printf2("tx_enable set\n");

    control.as_int = *PCM_CS_A;

    itoa(control.as_int, 16, tempStr, 20);

    printf2("PCM_CS_A: %s\n", tempStr);

    long i = 0;

    while(1)
    {
        control.as_int = *PCM_CS_A;

        while(control.tx_fifo_ready != 1)
            control.as_int = *PCM_CS_A;

        *PCM_FIFO_A = (int32_t)(sin(i*((TWO_PI/48000)*440))*65000000);

        control.as_int = *PCM_CS_A;

        while(control.tx_fifo_ready != 1)
            control.as_int = *PCM_CS_A;

        *PCM_FIFO_A = (int32_t)(sin(i*((TWO_PI/48000)*440))*65000000);

        i++;
    }*/
}
