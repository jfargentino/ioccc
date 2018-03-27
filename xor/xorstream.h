#ifndef XORSTREAM_H
#define XORSTREAM_H

#include <stdint.h>

enum xorshift_t {
    XORSHIFT32 = 0,
    XORSHIFT128,
    XORWOW,
    SPLITMIX64,
    XORSHIFT64STAR,
    XORSHIFT116PLUS,
    LEHMER128,
    XORSHIFT128PLUS,
    XOROSHIRO128PLUS,
    XORSHIFT1024STAR,
    XORSHIFT4096STAR,
    XORSHIFT_NB
};

int xorseed32_length (enum xorshift_t method);
int xorseed64_length (enum xorshift_t method);

uint32_t xorstream32(enum xorshift_t method, uint32_t * seed);
uint64_t xorstream64(enum xorshift_t method, uint64_t * seed);

#endif

