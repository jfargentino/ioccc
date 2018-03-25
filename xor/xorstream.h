#ifndef XORSTREAM_H
#define XORSTREAM_H

#include <stdint.h>

enum xorshift_t {
    XORSHIFT32 = 0,
    XORSHIFT128,
    XORWOW,
    SPLITMIX64,
    XORSHIFT64STAR,
    XORSHIFT1024STAR,
    XORSHIFT128PLUS,
    XOROSHIRO128PLUS,
    XORSHIFT_NB
};

uint32_t xorstream32(enum xorshift_t method, uint32_t * seed);
uint64_t xorstream64(enum xorshift_t method, uint64_t * seed);

#endif

