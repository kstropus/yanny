#include <common/stdlib.h>
#include <common/stddef.h>
#include <kernel/uart.h>

#define MEM_START &_end
#define MEM_END   MMIO_BASE
unsigned long freeptr = MEM_START;

void* malloc(unsigned int size)
{
    if (size == 0 || freeptr + size > MEM_END)
        return (void*)0;

    freeptr += size;

    return (void*)(freeptr - size);
}

void memcpy(void * dest, void * src, int bytes) {
    char * d = dest, * s = src;
    while (bytes--) {
        *d++ = *s++;
    }
}

void bzero(void * dest, int bytes) {
    char * d = dest;
    while (bytes--) {
        *d++ = 0;
    }
}

int itoa(int num, int base, char * str, int maxLen)
{
    //uart_puts("1");
    if(base <= 1 || base > 36 || maxLen <= 0)
    {
		if(str != NULL)
			str[0] = '\0';

        return 0;
    }
    //uart_puts("2");
    int charsWritten = 0;
    bool negative = false;

    if(num < 0 && base == 10)
    {
        negative = true;
        num = -num;
    }
    //uart_puts("3");
	unsigned int unum = (unsigned int)num;

    do
    {
        //uart_puts("4");
        int digit = unum % base;

		if(str != NULL)
			str[charsWritten] = (digit <= 9) ? '0' + digit : 'a' + (digit - 10);

		charsWritten++;
        unum /= base;
    } while(unum != 0 && charsWritten < maxLen);
    //uart_puts("5");
    if(negative && charsWritten < maxLen)
	{
        //uart_puts("6");
		if(str != NULL)
			str[charsWritten] = '-';

		charsWritten++;
	}
    //uart_puts("7");
	if(str != NULL)
	{
		for(int i = 0, j = charsWritten - 1; i < j; i++, j--)
		{
            //uart_puts("8");
			num = str[i];
			str[i] = str[j];
			str[j] = (char)num;
		}

		str[charsWritten] = '\0';
	}
    //uart_puts("9");
    return charsWritten;
}
