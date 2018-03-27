#include "xorshift.h"

/****************************************************************************/
uint32_t xorshift32_abck(uint32_t * seed, int a, int b, int c, uint32_t k) {
    uint32_t x = *seed;
    x ^= x >> a;
    x ^= x << b;
    x ^= x >> c;
    *seed = x;
    return x * k;
}

/****************************************************************************/
// xorshift32_abck(seed, 13, 17, 15, 1)
uint32_t xorshift32(uint32_t * seed) {
    uint32_t x = *seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 15; // looks like 5 was a typo
    *seed = x;
    return x;
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
    return t + (seed[4] += 362437);
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

uint64_t xorshift64_abck(uint64_t * seed, int a, int b, int c, uint64_t k) {
    uint64_t x = *seed;
    x ^= x >> a;
    x ^= x << b;
    x ^= x >> c;
    *seed = x;
    return x * k;
}

/****************************************************************************/
// xorshift64_abck(seed, 12, 25, 27, 0x2545F4914F6CDD1D)
uint64_t xorshift64star(uint64_t * seed) {
    uint64_t x = *seed;
    x ^= x >> 12; // a
    x ^= x << 25; // b
    x ^= x >> 27; // c
    *seed = x;
    return x * UINT64_C(0x2545F4914F6CDD1D);
}

/****************************************************************************/

uint64_t xorshift1024star(uint64_t seed[static 16]) {
    static int p = 0;
    const uint64_t s0 = seed[p++];
    uint64_t s1 = seed[p &= 15];
    s1 ^= s1 << 31; // a
#if 1
    s[p] = s1 ^ s0 ^ (s1 >> 11) ^ (s0 >> 30); // b,c
    return s[p] * UINT64_C(0x9E3779b97f4a7c13);
#else
    // 1st version was using M_8, now replaced by the golden-ratio
    s1 ^= s1 >> 11; // b
    s1 ^= s0 ^ (s0 >> 30); // c
    seed[p] = s1;
    return s1 * UINT64_C(1181783497276652981);
#endif
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
    return ( s[ 1 ] = ( s1 ^ s0 ^ ( s1 >> 17 ) ^ ( s0 >> 26 ) ) ) + s0; // b, c
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

// TODO lehmer128 //////////////////////////////////////////////////////////////
/* This is probably the oldest known PRNG: a Lehmer generator (a.k.a.
   multiplicative LCG). It simply multiplies the current state by a
   constant. It is a very fast generator passing BigCrush, albeit slower
   than xoroshiro128+, and with a smaller period (2^126). It needs support
   for 128-bit integers from the compiler. The less significant bit,
   moreover, has shorter period 2^62, the next bit 2^63, etc.

   Note, however, that as 128-bit processor and compilers will become
   common this generator will likely become extremely fast. 

   The multiplier has been taken from

   Pierre L'Ecuyer. Tables of linear congruential generators of different
   sizes and good lattice structure. Math. Comput. 68, 225 (1999), 249-260.

   IMPORTANT: On big-endian architectures, the role of s[0] and s[1] must
   be exchanged.
*/
#define MULTIPLIER ((__int128)0x12e15e35b500f16e << 64 | 0x2e714eb2b37916a5)

/* The state must be seeded with two 64-bit values, among which s[0] MUST be odd. */
static union {
	__int128 x;
	uint64_t s[2];
} state;

uint64_t next(void) {
	state.x *= MULTIPLIER;
	return state.s[1];
}

// TODO xorshift4096star ///////////////////////////////////////////////////////
/*  Written in 2014 by Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <stdint.h>

/* While you can use this generator, we rather suggest to use a
   xorshift1024* generator. */

/* The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed,  we suggest to seed a xorshift64* generator and use its
   output to fill s. */

uint64_t s[ 64 ];
int p;

uint64_t next(void) { 
	uint64_t s0 = s[ p ];
	uint64_t s1 = s[ p = ( p + 1 ) & 63 ];
	s1 ^= s1 << 25; // a
	s1 ^= s1 >> 3;  // b
	s0 ^= s0 >> 49; // c
	return ( s[ p ] = s0 ^ s1 ) * 8372773778140471301LL; 
}

// TODO xorshift116plus ////////////////////////////////////////////////////////
/* Written in 2014 by Sebastiano Vigna (vigna@acm.org) and 
   Kenji Rikitake (kenji.rikitake@acm.org).

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <stdint.h>

#define UINT58MASK (uint64_t)((uint64_t )1 << 58) - 1)

/* This generator is a variant of xorshift128+ for dynamic languages, such
   as Erlang, that can use only 58 bits of a 64-bit integer. Only the lower
   58 bits of each state word are valid (the upper six are zeroes).
   
   This generator passes BigCrush without systematic failures, but due to
   the relatively short period it is acceptable only for applications with
   a mild amount of parallelism; otherwise, use a xorshift1024* generator.

   The state must be seeded so that the lower 58 bits of s[ 0 ] and s[ 1 ]
   are not all zeroes. If you have a nonzero 64-bit seed, we suggest to
   pass it twice through MurmurHash3's avalanching function and take the
   lower 58 bits, taking care that they are not all zeroes (you can apply
   the avalanching function again if this happens). */

uint64_t s[ 2 ];

uint64_t next(void) { 
	uint64_t s1 = s[ 0 ];
	const uint64_t s0 = s[ 1 ];
	s[ 0 ] = s0;
	s1 ^= (s1 << 24) & UINT58MASK ; // a
	return ((( s[ 1 ] = ( s1 ^ s0 ^ ( s1 >> 11 ) ^ ( s0 >> 41 ) ) ) + s0) & UINT58MASK) ; // b, c
}

// TODO
// http://www.iro.umontreal.ca/~panneton/well/
