#include <common/stdlib.h>
#include <common/stddef.h>

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

int itoa2(int num, char * str, int base)
{
    if(base <= 1 || base > 36)
    {
		if(str != NULL)
			str[0] = '\0';

        return 0;
    }

    int charsWritten = 0;
    bool negative = false;

    if(num < 0 && base == 10)
    {
        negative = true;
        num = -num;
    }

	unsigned int unum = (unsigned int)num;

    do
    {
        int digit = unum % base;

		if(str != NULL)
			str[charsWritten] = (digit <= 9) ? '0' + digit : 'a' + (digit - 10);

		charsWritten++;
        unum /= base;
    } while(unum != 0);

    if(negative)
	{
		if(str != NULL)
			str[charsWritten] = '-';

		charsWritten++;
	}

	if(str != NULL)
	{
		for(int i = 0, j = charsWritten - 1; i < j; i++, j--)
		{
			num = str[i];
			str[i] = str[j];
			str[j] = (char)num;
		}

		str[charsWritten] = '\0';
	}

    return charsWritten;
}

char * itoa(int i)
{
    static char buffer[20];
    int charsWritten = 0;
    bool negative = false;

    if(i < 0)
    {
        negative = true;
        i = -i;
    }

    do
    {
        buffer[charsWritten++] = '0' + (i % 10);
        i /= 10;
    } while(i > 0);

    if(negative)
        buffer[charsWritten++] = '-';

    for(int j = 0, k = charsWritten - 1; j < k; j++, k--)
    {
        i = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = (char)i;
    }

    buffer[charsWritten++] = '\0';

    return buffer;
}
