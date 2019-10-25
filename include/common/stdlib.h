#ifndef STDLIB_H
#define STDLIB_H

typedef int bool;

#define true 1
#define false 0

void* malloc(unsigned int size);

void memcpy(void * dest, void * src, int bytes);

void bzero(void * dest, int bytes);

int itoa(int num, int base, char * str, int maxLen);

#endif
