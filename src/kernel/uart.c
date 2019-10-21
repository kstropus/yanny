#include <common/stddef.h>
#include <common/stdint.h>
#include <kernel/gpio.h>
#include <kernel/mbox.h>
#include <kernel/uart.h>
#include <common/stdlib.h>
#include <kernel/delays.h>

// Memory-Mapped I/O output
void mmio_write(uint64_t reg, uint32_t data)
{
    *(volatile uint32_t*)reg = data;
}

// Memory-Mapped I/O input
uint32_t mmio_read(uint64_t reg)
{
    return *(volatile uint32_t*)reg;
}

// Loop <delay> times in a way that the compiler won't optimize away
void delay(int32_t count)
{
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
            : "=r"(count): [count]"0"(count) : "cc");
}

/* PL011 UART registers */
#define UART0_DR        ((volatile unsigned int*)(MMIO_BASE+0x00201000))
#define UART0_FR        ((volatile unsigned int*)(MMIO_BASE+0x00201018))
#define UART0_IBRD      ((volatile unsigned int*)(MMIO_BASE+0x00201024))
#define UART0_FBRD      ((volatile unsigned int*)(MMIO_BASE+0x00201028))
#define UART0_LCRH      ((volatile unsigned int*)(MMIO_BASE+0x0020102C))
#define UART0_CR        ((volatile unsigned int*)(MMIO_BASE+0x00201030))
#define UART0_IMSC      ((volatile unsigned int*)(MMIO_BASE+0x00201038))
#define UART0_ICR       ((volatile unsigned int*)(MMIO_BASE+0x00201044))

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart_init()
{
    register unsigned int r;

    /* initialize UART */
    *UART0_CR = 0;         // turn off UART0

    /* set up clock for consistent divisor values */
    mbox[0] = 9*4;
    mbox[1] = MBOX_REQUEST;
    mbox[2] = MBOX_TAG_SETCLKRATE; // set clock rate
    mbox[3] = 12;
    mbox[4] = 8;
    mbox[5] = 2;           // UART clock
    mbox[6] = 4000000;     // 4Mhz
    mbox[7] = 0;           // clear turbo
    mbox[8] = MBOX_TAG_LAST;
    mbox_call(MBOX_CH_PROP);

    /* map UART0 to GPIO pins */
    r=*GPFSEL1;
    r&=~((7<<12)|(7<<15)); // gpio14, gpio15
    r|=(4<<12)|(4<<15);    // alt0
    *GPFSEL1 = r;
    *GPPUD = 0;            // enable pins 14 and 15
    wait_cycles(150);
    *GPPUDCLK0 = (1<<14)|(1<<15);
    wait_cycles(150);
    *GPPUDCLK0 = 0;        // flush GPIO setup

    *UART0_ICR = 0x7FF;    // clear interrupts
    *UART0_IBRD = 2;       // 115200 baud
    *UART0_FBRD = 0xB;
    *UART0_LCRH = 0b11<<5; // 8n1
    *UART0_CR = 0x301;     // enable Tx, Rx, FIFO
}


uart_flags_t read_flags()
{
    uart_flags_t flags;

    flags.as_int = *UART0_FR;

    return flags;
}

void uart_putc(unsigned char c)
{
    uart_flags_t flags;

    do
    {
        flags = read_flags();
    } while (flags.transmit_queue_full);

    *UART0_DR = c;
}

unsigned char uart_getc()
{
    uart_flags_t flags;

    do
    {
        flags = read_flags();
    } while (flags.receive_queue_empty);

    return *UART0_DR;
}

void uart_puts(const char* s)
{
    uart_flags_t flags;

    while(*s != '\0')
    {
        flags = read_flags();

        while(flags.transmit_queue_full)
            flags = read_flags();

        *UART0_DR = *s++;
    }
}

/*int uart_gets(char* s, int maxLen)
{
    uart_flags_t flags;
    int len = 0;
    bool done = false;

    while(!done)
    {
        flags = read_flags();

        while(flags.receive_queue_empty)
            flags = read_flags();

        *s = mmio_read(UART0_DR);

        if(*s == '\0' || *s == '\n')
            done = true;
        else
        {
            s++;
            len++;
        }

        if(len == maxLen)
            done = true;
    }

    if(*s == '\n')
    {
        s++;
        len++;
        *s = '\0';
    }

    return len;
}*/
