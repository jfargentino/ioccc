#include <stdint.h>
#include "_xorshift.h"

/**************************************************************************/
uint32_t _xor (void) {
    static uint32_t seed[1] = { 2463534242u };
    return _xorshift32_lrl (seed, 13, 17, 15);
}

/**************************************************************************/
uint64_t _xor64bis (void) {
    static uint64_t seed[1] = { 88172645463325252u };
    return _xorshift64_lrl (seed, 13, 7, 17);
}

/**************************************************************************/
static unsigned int a64[] = { 10,  8,  2, 23 };
static unsigned int b64[] = { 13,  9,  7,  3 };
static unsigned int c64[] = { 10, 22,  3, 24 };

uint32_t _xor64 (unsigned int a, unsigned int b, unsigned int c) {
    static uint32_t seed[2] = { 123456789u, 362436069u };
    return _xorshift_lrr(seed, 2, a, b, c);
}

/**************************************************************************/
static unsigned int a96[] = { 10, 13,  1, 10 };
static unsigned int b96[] = {  5, 19, 17,  1 };
static unsigned int c96[] = { 26,  3,  2, 26 };

uint32_t _xor96(unsigned int a, unsigned int b, unsigned int c){
    static uint32_t seed[3] = { 123456789u, 362436069u, 521288629u };
    return _xorshift_lrr(seed, 3, a, b, c);
}

/**************************************************************************/
static unsigned int a128[] = {  5, 15, 23,  5 };
static unsigned int b128[] = { 14,  4, 24, 12 };
static unsigned int c128[] = {  1, 21,  3, 29 };

uint32_t _xor128(unsigned int a, unsigned int b, unsigned int c){
    static uint32_t seed[4] = { 123456789u, 362436069u,
                                521288629u, 88675123u };
    return _xorshift_lrr(seed, 4, a, b, c);
}

/**************************************************************************/
static unsigned int a160[] = { 2,  7,  1 };
static unsigned int b160[] = { 1, 13,  1 };
static unsigned int c160[] = { 4,  6, 20 };

uint32_t _xor160(unsigned int a, unsigned int b, unsigned int c){
    static uint32_t seed[5] = { 123456789u, 362436069u,
                                521288629u, 88675123u, 5783321u };
    return _xorshift_lrr(seed, 5, a, b, c);
}

/**************************************************************************/
uint32_t xor96bis(uint32_t * seed,
                  unsigned int seed_len,
                  unsigned int a,
                  unsigned int b,
                  unsigned int c) {
    uint32_t seed0 = seed[0];
    unsigned int k = 0;
    while (k < seed_len - 1) {
        seed[k] = seed[k+1];
        k ++;
    }
    seed[k] = seed0;
    seed[k] = seed[k]^(seed[k] << a) 
            ^ seed[0]^(seed[0] >> b)
            ^ seed[1]^(seed[1] << c);
    return seed[k];
}

uint32_t _xor96bis(void) {
    static uint32_t seed[3] = { 123456789u, 362436069u, 521288629u };
    return xor96bis(seed, 3, 3, 19, 6);
}

/**************************************************************************/
uint32_t xor128bis(uint32_t * seed, 
                   unsigned int const * const abc,
                   unsigned int len) {
    uint32_t s = (seed[0]^(seed[0] << 20))
               ^ (seed[1]^(seed[1] >> 11))
               ^ (seed[2]^(seed[2] << 27))
               ^ (seed[3]^(seed[3] >>  6));
    seed[0]    = seed[1];
    seed[1]    = seed[2];
    seed[2]    = seed[3];
    seed[3]    = s;
    return seed[3];
}

uint32_t _xor128bis(void) {
    static uint32_t seed[4] = { 123456789u, 362436069u,
                                521288629u, 88675123u };
    unsigned int const abc[4] = { 20, 11, 27, 6 };
    return ___ (seed, abc, 4);
}

/**************************************************************************/
uint32_t xorwow (uint32_t seed[static 5], uint32_t d[static 1]){
    seed[0] ^= seed[0] >> 2; 
    uint32_t seed0 = seed[0];;
    seed[0] = seed[1];
    seed[1] = seed[2];
    seed[2] = seed[3];
    seed[3] = seed[4];
    seed[4] = (seed[4]^(seed[4] << 4)) ^ (seed0^(seed0 << 1));
    d[0] += 362437u;
    return d[0] + seed[4]; 
}

uint32_t _xorwow (void){
    static uint32_t seed[5] = { 123456789u, 362436069u,
                                521288629u, 88675123u, 5783321u };
    static uint32_t d[1] = { 6615241u };
    return xorwow(seed, d);
}

/**************************************************************************/
uint32_t xor128ter (uint32_t seed[static 4]) {
    seed[0] ^= seed[0] << 11;
    uint32_t seed0 = seed[0];
    seed[0] = seed[1];
    seed[1] = seed[2];
    seed[2] = seed[3];
    seed[3] = (seed[3]^(seed[3] >> 19)) ^ (seed0^(seed0 >> 8));
    return seed[3];
}

uint32_t _xor128ter (void) {
    static uint32_t seed[4] = { 123456789u, 362436069u,
                                521288629u, 88675123u  };
    return _xorshift_lrr(seed, 4, 11, 8, 19);
}

/**************************************************************************/
uint32_t mwc (uint32_t seed[3], uint32_t carry[static 1]) {
    uint64_t s = 916905990ll * seed[0] + carry[0];
    seed[0]    = seed[1];
    seed[1]    = seed[2];
    carry[0]   = s >> 32;
    seed[2]    = s & 0xffffffff;
    return seed[2];
}

uint32_t _mwc (void) {
    static uint32_t seed[3] = { 123456789u, 362436069u, 77465321u };
    static uint32_t carry[1] = { 13579u };
    return mwc(seed, carry);
}

// CHECK ///////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char ** argv) {
    unsigned long long k = 0;
    if (argc > 1) {
        k = strtoull (argv[1], NULL, 0);
    }
    if (k < 1) {
        k = 1;
    }
    while (k > 0) {
        printf("%08x %016lx ", _xor(), _xor64bis());
        printf("%08x %08x ",
               _xor64(a64[0],b64[0],c64[0]),
               _xor96(a96[0],b96[0],c96[0]));
        printf("%08x %08x ",
               _xor128(a128[0],b128[0],c128[0]),
               _xor160(a160[0],b160[0],c160[0]));
        printf("%08x %08x ", _xor96bis(), _xor128bis());
        printf("%08x %08x %08x\n", _xorwow(), _xor128ter(), _mwc());
        k --;
    }
}

