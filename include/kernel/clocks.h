#ifndef CLOCKS_H
#define CLOCKS_H

#include <common/stdint.h>
#include <kernel/gpio.h>

#define CM_PCM_CTRL     ((volatile unsigned int*)(MMIO_BASE+0x00101098))
#define CM_PCM_DIV      ((volatile unsigned int*)(MMIO_BASE+0x0010109C))

#endif
