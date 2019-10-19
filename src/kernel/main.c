#include <common/stdlib.h>
#include <common/stdio.h>
#include <kernel/uart.h>
#include <kernel/delays.h>

void main()
{
    // set up serial console
    uart_init();

    uart_puts("Waiting 1000000 CPU cycles (ARM CPU): ");
    wait_cycles(1000000);
    uart_puts("OK\n");

    char* name = "Keith";
    char* fish = "tuna";
    int numFish = 10;
    printf("Hey %s, good luck eating %d %s!\n", name, numFish, fish);

	char buffer[256];

    // echo everything back
    while (true) {
        gets(buffer, 256);
        puts(buffer);
        putc('\n');
    }
}
