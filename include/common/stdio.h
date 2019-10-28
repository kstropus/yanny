#ifndef STDIO_H
#define STDIO_H

#include <common/stddef.h>
#include <common/stdint.h>

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

typedef int (*stream_write_ptr)(stream* sr, int8_t* buffer, int offset, int length);

stream_write_ptr stream_register_type(int16_t type_id, stream_write_ptr write);

int stream_write(stream* sr, int8_t* buffer, int offset, int length);

int stream_flush(stream* sr);

int stream_close(stream* sr);

#endif
