#ifndef STDIO_H
#define STDIO_H

#include <common/stddef.h>

typedef struct stream
{
	int64_t position;
	//int8_t* buffer;
	//int32_t buffer_length;
    //int8_t* head;
    //int8_t* tail;
	int16_t type_id;
	void* type_data;
} stream;

/*typedef struct array_segment
{
	int8_t* buffer;
	int64_t offset;
	int64_t length;
} array_segment;*/

int stream_register_type(
	int16_t type_id, int (*write)(void*, int8_t*, int, int));

int stream_write(stream* sm, int8_t* buffer, int offset, int length);

int stream_flush(stream* sm);

int stream_close(stream* sm);

#endif
