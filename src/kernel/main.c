#include <common/stdlib.h>
#include <common/stdio.h>
#include <kernel/uart.h>
#include <kernel/delays.h>
#include <kernel/pcm.h>

void main()
{
    uart_init();

    uart_puts("Waiting 1000000 CPU cycles (ARM CPU): ");
    wait_cycles(1000000);
    uart_puts("OK\n");

    char* name = "Keith";
    char* fish = "tuna";
    int numFish = 10;
    printf("Hey %s, good luck eating %d %s!\n", name, numFish, fish);

    pcm_init();

	//char buffer[256];

    // echo everything back
    while (1) {
        //uart_gets(buffer, 256);
        //uart_puts(buffer);
        //putc('\n');
        char c = uart_getc();
        uart_putc(c);
    }
}
