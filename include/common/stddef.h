#ifndef STDDEF_H
#define STDDEF_H

#define NULL ((void*)0)

#define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)

typedef unsigned long int size_t;
typedef long int ssize_t;
typedef short int wchar_t;

typedef __PTRDIFF_TYPE__ ptrdiff_t;

#endif
