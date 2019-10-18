/*
 * Copyright (C) 2018 bzt (bztsrc@github)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

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

    char mystr[256];

	itoa2(1234567, mystr, 10);
    puts(mystr);
	puts(": ");
	puts(itoa(itoa2(1234567, NULL, 10)));
    putc('\n');
	itoa2(1234567, mystr, 8);
    puts(mystr);
    putc('\n');
	itoa2(1234567, mystr, 2);
    puts(mystr);
	puts(": ");
	puts(itoa(itoa2(1234567, NULL, 2)));
    putc('\n');
	itoa2(1234567, mystr, 16);
    puts(mystr);
    putc('\n');
	itoa2(1234567, mystr, 3);
    puts(mystr);
    putc('\n');


	itoa2(-0x12345, mystr, 16);
    puts(mystr);
    putc('\n');

	itoa2(-0x01, mystr, 16);
    puts(mystr);
    putc('\n');

	itoa2(-0x55, mystr, 16);
    puts(mystr);
    putc('\n');

	char buf[256];

    // echo everything back
    while (1) {
        gets(buf,256);
        puts(buf);
        putc('\n');
    }
}
