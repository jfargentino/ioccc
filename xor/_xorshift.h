#ifndef _XORSHIFT_H
#define _XORSHIFT_H

#include "xorshift.h"

// Low-level ///////////////////////////////////////////////////////////////////

static inline uint32_t _xor32 (uint32_t * x, int k) {
    return (*x) ^= (*x) >> k;
}

static inline uint32_t _xol32 (uint32_t * x, int k) {
    return (*x) ^= (*x) << k;
}

static inline uint64_t _xor64 (uint64_t * x, int k) {
    return (*x) ^= (*x) >> k;
}

static inline uint64_t _xol64 (uint64_t * x, int k) {
    return (*x) ^= (*x) << k;
}

// General functions ///////////////////////////////////////////////////////////

// xorshift32 is _xor_shift32_abc(seed, 13, 17, 15)
// see the list of the (a,b,c) triplets in Marsaglia
// a, b & c < 32
static inline uint32_t _xorshift32_abc (uint32_t * seed,
                                        int a, int b, int c) {
    _xor32 (seed, a);
    _xol32 (seed, b);
    return _xor32 (seed, c);
}

static inline uint32_t _xorshift32plus_abc (uint32_t * seed,
                                            int a, int b, int c,
                                            uint32_t k) {
    return k + _xorshift32_abc (seed, a, b, c);
}

static inline uint32_t _xorshift32star_abc (uint32_t * seed,
                                            int a, int b, int c,
                                            uint32_t k) {
    return k * _xorshift32_abc (seed, a, b, c);
}

// xorshift64star is _xorshift64_abc(seed, 12, 25, 27) * 0x2545F4914F6CDD1D
// see the list of the (a,b,c) triplets in Marsaglia
// a, b & c < 64
static inline uint64_t _xorshift64_abc (uint64_t * seed,
                                        int a, int b, int c) {
    _xor64 (seed, a);
    _xol64 (seed, b);
    return _xor64 (seed, c);
}

static inline uint64_t _xorshift64plus_abc (uint64_t * seed,
                                            int a, int b, int c,
                                            uint64_t k) {
    return k + _xorshift64_abc (seed, a, b, c);
}

static inline uint64_t _xorshift64star_abc (uint64_t * seed,
                                            int a, int b, int c,
                                            uint64_t k) {
    return k * _xorshift64_abc (seed, a, b, c);
}

#endif

/*
uint32_t xorshift128(uint32_t seed[static 4]) {
    uint32_t s, t = seed[3];
    t ^= t << 11;
    t ^= t >> 8;
    seed[3] = seed[2];
    seed[2] = seed[1]; 
    seed[1] = s = seed[0];
    t ^= s;
    t ^= s >> 19;    
    seed[0] = t;
    return t;
}

uint64_t xorshift128plus(uint64_t seed[static 2]) {
    uint64_t s1 = seed[0];
    const uint64_t s0 = seed[1];
    seed[0] = s0;
    s1 ^= s1 << 23; // a
#if 1
    seed[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5); // b, c
    return seed[1] + s0;
#else
    seed[1] = s1 ^ s0 ^ ( s1 >> 17 ) ^ ( s0 >> 26 ); // b, c
    return seed[1] + s0;
#endif
}
*/
