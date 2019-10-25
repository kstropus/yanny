#include <kernel/pcm.h>
#include <kernel/gpio.h>
#include <kernel/uart.h>
#include <kernel/delays.h>
#include <common/stdio2.h>
#include <common/stdlib.h>

void pcm_init()
{
    register unsigned int r;
    pcm_control_t control;

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
    *GPPUD = 0;            // remove control signal
    *GPPUDCLK0 = 0;        // remove update clock

    control.as_int = *PCM_CS_A;

    control.enable_pcm = 1;

    *PCM_CS_A = control.as_int;

    control.as_int = *PCM_CS_A;

    char tempStr[21];
    itoa(control.as_int, 16, tempStr, 20);

    printf2("PCM_CS_A: %s\n", tempStr);





    pcm_mode_t mode;

    mode.as_int = *PCM_MODE_A;

    itoa(mode.as_int, 16, tempStr, 20);

    printf2("PCM_MODE_A: %s\n", tempStr);

    pcm_tx_config_t tx_config;

    tx_config.as_int = *PCM_TXC_A;

    itoa(tx_config.as_int, 16, tempStr, 20);

    printf2("PCM_TXC_A: %s\n", tempStr);



    mode.pdm_input_enable = 0;
    mode.clock_invert = 1;
    mode.frame_sync_invert = 1;
    mode.frame_len = 63;
    mode.frame_sync_len = 32;

    *PCM_MODE_A = mode.as_int;

    tx_config.ch1_width = 8;
    tx_config.ch1_width_ex = 1;
    tx_config.ch1_enable = 1;
    tx_config.ch2_width = 8;
    tx_config.ch2_width_ex = 1;
    tx_config.ch2_position = 32;
    tx_config.ch2_enable = 1;

    *PCM_TXC_A = tx_config.as_int;



    mode.as_int = *PCM_MODE_A;

    itoa(mode.as_int, 16, tempStr, 20);

    printf2("PCM_MODE_A: %s\n", tempStr);

    tx_config.as_int = *PCM_TXC_A;

    itoa(tx_config.as_int, 16, tempStr, 20);

    printf2("PCM_TXC_A: %s\n", tempStr);






    control.as_int = *PCM_CS_A;

    control.tx_clear = 1;

    *PCM_CS_A = control.as_int;

    delay(1000);



    //control.as_int = *PCM_CS_A;

    //control.tx_threshold = 3;

    long countdown = 100;
    int pcm_data = 65000000;

    while(control.tx_fifo_ready == 1)
    {
        *PCM_FIFO_A = (uint32_t)pcm_data;
        printf2("Write to FIFO\n");

        countdown--;

        if(countdown == 0)
        {
            pcm_data = -pcm_data;
            countdown = 100;
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

    while(1)
    {
        printf2("Q\n");
        control.as_int = *PCM_CS_A;

        while(control.tx_fifo_ready != 1)
            control.as_int = *PCM_CS_A;
        printf2("R\n");
        *PCM_FIFO_A = (uint32_t)pcm_data;
        printf2("S\n");
        countdown--;

        if(countdown == 0)
        {
            pcm_data = -pcm_data;
            countdown = 100;
            printf2("T\n");
        }
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
