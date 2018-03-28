#include "_xorshift.h"

/****************************************************************************/

uint32_t xorshift32(uint32_t * seed) {
#if 0
    return _xorshift32_abc(seed, 13, 27, 25);
#else
    uint32_t x = *seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 15; // looks like 5 was a typo
    *seed = x;
    return x;
#endif
}

/****************************************************************************/

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

/****************************************************************************/

uint32_t xorwow(uint32_t seed[static 5]) {
    uint32_t s, t = seed[3];
    t ^= t >> 2;
    t ^= t << 1;
    seed[3] = seed[2];
    seed[2] = seed[1];
    seed[1] = s = seed[0];
    t ^= s;
    t ^= s << 4;    
    seed[0] = t;
    seed[4] += 362437;
    return t + seed[4];
}

/****************************************************************************/

uint64_t splitmix64 (uint64_t * seed) {
    (*seed) += UINT64_C(0x9E3779B97F4A7C15);
    uint64_t s = (*seed);
    s = (s ^ (s >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
    s = (s ^ (s >> 27)) * UINT64_C(0x94D049BB133111EB);
    return s ^ (s >> 31);
}

/****************************************************************************/
uint64_t xorshift64star(uint64_t * seed) {
#if 0
    return _xorshift64_abc(seed, 12, 25, 27) * 0x2545F4914F6CDD1D;
#else
    uint64_t x = *seed;
    x ^= x >> 12; // a
    x ^= x << 25; // b
    x ^= x >> 27; // c
    *seed = x;
    return x * UINT64_C(0x2545F4914F6CDD1D);
#endif
}

/****************************************************************************/

static uint64_t const UINT58MASK = ( ((uint64_t )1 << 58) - 1 );

uint64_t xorshift116plus(int64_t seed[static 2]) { 
	uint64_t s1 = seed[0];
	const uint64_t s0 = seed[1];
	seed[0] = s0;
	s1 ^= (s1 << 24) & UINT58MASK ;
	seed[1] = ( s1 ^ s0 ^ ( s1 >> 11 ) ^ ( s0 >> 41 ) );
	return (seed[1] + s0) & UINT58MASK;
}

/****************************************************************************/

static const
__int128 LEHMER128_MUL = ( (__int128)0x12e15e35b500f16e << 64
                                   | 0x2e714eb2b37916a5       );

uint64_t lehmer128(uint64_t seed[static 2]) {
    union { __int128 x; uint64_t s[2]; } state;
    state.s[0] = seed[0]; 
    state.s[1] = seed[1]; 
	state.x *= LEHMER128_MUL;
	return state.s[1];
}

/****************************************************************************/

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

/****************************************************************************/

static inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

uint64_t xoroshiro128plus(uint64_t seed[static 2]) {
    const uint64_t s0 = seed[0];
    uint64_t s1 = seed[1];
    s1 ^= s0;
    seed[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
    seed[1] = rotl(s1, 36); // c
    return seed[1] + s0;
}

/****************************************************************************/

uint64_t xorshift1024star(uint64_t seed[static 16]) {
    static int p = 0;
    const uint64_t s0 = seed[p++];
    uint64_t s1 = seed[p &= 15];
    s1 ^= s1 << 31; // a
#if 1
    seed[p] = s1 ^ s0 ^ (s1 >> 11) ^ (s0 >> 30); // b,c
    return seed[p] * UINT64_C(0x9E3779b97f4a7c13);
#else
    // 1st version was using M_8, now replaced by the golden-ratio
    s1 ^= s1 >> 11; // b
    s1 ^= s0 ^ (s0 >> 30); // c
    seed[p] = s1;
    return s1 * UINT64_C(1181783497276652981);
#endif
}

/****************************************************************************/

uint64_t xorshift4096star(uint64_t seed[static 64]) { 
    static int p = 0;
	uint64_t s0 = seed[p];
	uint64_t s1 = seed[p = ( p + 1 ) & 63];
	s1 ^= s1 << 25; // a
	s1 ^= s1 >> 3;  // b
	s0 ^= s0 >> 49; // c
    seed[p] = s0 ^ s1;
	return seed[p] * 8372773778140471301LL; 
}

/****************************************************************************/
// TODO
// http://www.iro.umontreal.ca/~panneton/well/
