typedef char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int int64_t;

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef unsigned long int uint64_t;

typedef char byte;

#define INT8_MIN 0x80
#define INT16_MIN 0x8000
#define INT32_MIN 0x80000000
#define INT64_MIN 0x8000000000000000L

#define INT8_MAX 0x7F
#define INT16_MAX 0x7FFF
#define INT32_MAX 0x7FFFFFFF
#define INT64_MAX 0x7FFFFFFFFFFFFFFFL

#define UINT8_MIN 0
#define UINT16_MIN 0
#define UINT32_MIN 0
#define UINT64_MIN 0

#define UINT8_MAX 0xFF
#define UINT16_MAX 0xFFFF
#define UINT32_MAX 0xFFFFFFFF
#define UINT64_MAX 0xFFFFFFFFFFFFFFFFUL

typedef char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;
typedef long int int_least64_t;

typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long int uint_least64_t;

#define INT_LEAST8_MAX 0x7F
#define INT_LEAST16_MAX 0x7FFF
#define INT_LEAST32_MAX 0x7FFFFFFF
#define INT_LEAST64_MAX 0x7FFFFFFFFFFFFFFFL

#define UINT_LEAST8_MAX 0xFF
#define UINT_LEAST16_MAX 0xFFFF
#define UINT_LEAST32_MAX 0xFFFFFFFF
#define UINT_LEAST64_MAX 0xFFFFFFFFFFFFFFFFUL

#define INT8_C(c) c
#define INT16_C(c) c
#define INT32_C(c) c
#define INT64_C(c) c ## L

#define UINT8_C(c) c
#define UINT16_C(c) c
#define UINT32_C(c) c
#define UINT64_C(c) c ## UL

typedef long int intptr_t;
typedef unsigned long int uintptr_t;

#define INTPTR_MIN 0x8000000000000000L
#define INTPTR_MAX 0x7FFFFFFFFFFFFFFFL
#define UINTPTR_MAX 0xFFFFFFFFFFFFFFFFUL

typedef long int intmax_t;
typedef unsigned long int uintmax_t;

#define INTMAX_MAX 0x7FFFFFFFFFFFFFFFL
#define INTMAX_MIN 0x8000000000000000L
#define UINTMAX_MAX 0xFFFFFFFFFFFFFFFFUL

#define INTMAX_C(c) c ## L
#define UINTMAX_C(c) c ## UL