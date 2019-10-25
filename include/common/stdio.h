#ifndef STDIO_H
#define STDIO_H

#include <common/stddef.h>

typedef struct Stream_Struct
{
	int8_t* Buffer;
	int32_t BufferLength;
	int8_t StreamType;
} Stream;

#endif