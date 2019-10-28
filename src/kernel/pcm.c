#include <kernel/pcm.h>
#include <kernel/gpio.h>
#include <kernel/uart.h>
#include <kernel/delays.h>
#include <common/stdio2.h>
#include <kernel/clocks.h>
#include <common/stdio2.h>
#include <common/stdlib.h>
#include <common/trig.h>

#define PCM_CS_A        ((volatile unsigned int*)(MMIO_BASE+0x00203000))
#define PCM_FIFO_A      ((volatile unsigned int*)(MMIO_BASE+0x00203004))
#define PCM_MODE_A      ((volatile unsigned int*)(MMIO_BASE+0x00203008))
#define PCM_RXC_A       ((volatile unsigned int*)(MMIO_BASE+0x0020300C))
#define PCM_TXC_A       ((volatile unsigned int*)(MMIO_BASE+0x00203010))
#define PCM_DREQ_A      ((volatile unsigned int*)(MMIO_BASE+0x00203014))
#define PCM_INTEN_A     ((volatile unsigned int*)(MMIO_BASE+0x00203018))
#define PCM_INTSTC_A    ((volatile unsigned int*)(MMIO_BASE+0x0020301C))
#define PCM_GRAY        ((volatile unsigned int*)(MMIO_BASE+0x00203020))

void pcm_init()
{
    register unsigned int r;
    pcm_control_t control;
    char tempStr[21];

    /* map PCM to GPIO pins */
    r=*GPFSEL1;
    r&=~((7<<24)|(7<<27)); // gpio18, gpio19
    r|=(4<<24)|(4<<27);    // alt0
    *GPFSEL1 = r;

    r=*GPFSEL2;
    r&=~(7 << 3); // gpio21
    r|=(4 << 3);    // alt0
    *GPFSEL2 = r;

    *GPPUD = 0;            // prep to remove pull ups and downs
    wait_cycles(150);
    *GPPUDCLK0 = (1<<18)|(1<<19)|(1<<21); // gpio18, 19, 21
    wait_cycles(150);
    *GPPUDCLK0 = 0;        // remove update clock

    *CM_PCM_CTRL = 0x5A000021;
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

    printf2("PCM_MODE_A: %s\n", tempStr);

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

    printf2("PCM_TXC_A: %s\n", tempStr);
    *PCM_TXC_A = tx_config.as_int;
    //*PCM_TXC_A = 0xC018C218;



    control.as_int = 0;
    control.pcm_clock_sync = 1;
    control.tx_fifo_sync = 1;
    control.tx_threshold = 3;
    control.tx_clear = 1;
    control.enable_pcm = 1;
    itoa(control.as_int, 16, tempStr, 20);

    printf2("PCM_CS_A: %s\n", tempStr);
    *PCM_CS_A = control.as_int;
    //*PCM_CS_A = 0x206D;

    //control.as_int = *PCM_CS_A;

    while(control.pcm_clock_sync == 0)
        control.as_int = *PCM_CS_A;






    //control.as_int = *PCM_CS_A;

    //while(control.tx_fifo_ready == 0)
        //control.as_int = *PCM_CS_A;

    //control.tx_threshold = 3;

    long countdown = 15;
    int pcm_data = 65000000;

    //while(1)
    //{
        //*PCM_FIFO_A = (uint32_t)pcm_data;

        //pcm_data -= 10000;

        //if(pcm_data <= 0)
        //    pcm_data = 10000000;

        //wait_cycles(10000);
    //}

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
    }




    /*uart_control_t control;

    // Disable UART0.
    bzero(&control, 4);
    mmio_write(UART0_CR, control.as_int);

    // Setup the GPIO pin 14 && 15.
    // Disable pull up/down for all GPIO pins & delay for 150 cycles.
    mmio_write(GPPUD, 0x00000000);
    delay(150);

    // Disable pull up/down for pin 14,15 & delay for 150 cycles.
    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);

    // Write 0 to GPPUDCLK0 to make it take effect.
    mmio_write(GPPUDCLK0, 0x00000000);

    // Clear pending interrupts.
    mmio_write(UART0_ICR, 0x7FF);

    // Set integer & fractional part of baud rate.
    // Divider = UART_CLOCK/(16 * Baud)
    // Fraction part register = (Fractional part * 64) + 0.5
    // UART_CLOCK = 3000000; Baud = 115200.

    // Divider = 3000000 / (16 * 115200) = 1.627 = ~1.
    mmio_write(UART0_IBRD, 1);
    // Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40.
    mmio_write(UART0_FBRD, 40);

    // Enable FIFO & 8 bit data transmissio (1 stop bit, no parity).
    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    // Mask all interrupts.
    mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
            (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    // Enable UART0, receive & transfer part of UART.
    control.uart_enabled = 1;
    control.transmit_enabled = 1;
    control.receive_enabled = 1;
    mmio_write(UART0_CR, control.as_int);*/
}
