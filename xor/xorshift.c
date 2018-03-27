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
	(*seed)  = ((*seed) ^ ((*seed) >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
	(*seed)  = ((*seed) ^ ((*seed) >> 27)) * UINT64_C(0x94D049BB133111EB);
	return (*seed) ^ ((*seed) >> 31);
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
	s1 ^= s1 >> 11; // b
	s1 ^= s0 ^ (s0 >> 30); // c
	seed[p] = s1;
	return s1 * UINT64_C(1181783497276652981);
}

/****************************************************************************/

uint64_t xorshift128plus(uint64_t seed[static 2]) {
	uint64_t s1 = seed[0];
	const uint64_t s0 = seed[1];
	seed[0] = s0;
	s1 ^= s1 << 23; // a
	seed[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5); // b, c
	return seed[1] + s0;
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

