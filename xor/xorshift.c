#include "xorshift.h"

/****************************************************************************/

uint32_t xorshift32(uint32_t * state) {
	uint32_t x = *state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 15; // looks like 5 was a typo
	*state = x;
	return x;
}

/****************************************************************************/

uint32_t xorshift128(uint32_t state[static 4]) {
	uint32_t s, t = state[3];
	t ^= t << 11;
	t ^= t >> 8;
	state[3] = state[2];
    state[2] = state[1]; 
    state[1] = s = state[0];
	t ^= s;
	t ^= s >> 19;	
	state[0] = t;
	return t;
}

/****************************************************************************/

uint32_t xorwow(uint32_t state[static 5]) {
	uint32_t s, t = state[3];
	t ^= t >> 2;
	t ^= t << 1;
	state[3] = state[2]; state[2] = state[1]; state[1] = s = state[0];
	t ^= s;
	t ^= s << 4;	
	state[0] = t;
	return t + (state[4] += 362437);
}

/****************************************************************************/

uint64_t xorshift64star(uint64_t * state) {
	uint64_t x = *state;
	x ^= x >> 12; // a
	x ^= x << 25; // b
	x ^= x >> 27; // c
	*state = x;
	return x * 0x2545F4914F6CDD1D;
}

/****************************************************************************/

uint64_t xorshift1024star(uint64_t s[static 16]) {
    static int p = 0;
	const uint64_t s0 = s[p++];
	uint64_t s1 = s[p &= 15];
	s1 ^= s1 << 31; // a
	s1 ^= s1 >> 11; // b
	s1 ^= s0 ^ (s0 >> 30); // c
	s[p] = s1;
	return s1 * (uint64_t)1181783497276652981;
}

/****************************************************************************/

uint64_t xorshift128plus(uint64_t s[static 2]) {
	uint64_t s1 = s[0];
	const uint64_t s0 = s[1];
	s[0] = s0;
	s1 ^= s1 << 23; // a
	s[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5); // b, c
	return s[1] + s0;
}

/****************************************************************************/

static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

uint64_t xoroshiro128plus(uint64_t s[static 2]) {
	const uint64_t s0 = s[0];
	uint64_t s1 = s[1];
	s1 ^= s0;
	s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
	s[1] = rotl(s1, 36); // c
	return s[1] + s0;
}

/****************************************************************************/

static uint64_t const xorshift128plus_JUMP[] = { 0x8a5cd789635d2dff,
                                                 0x121fd2155c472f96 };

static uint64_t const xoroshiro128plus_JUMP[] = { 0xbeac0467eba5facb,
                                                  0xd86b048b86aa9922 };

static uint64_t _xs128_jump (uint64_t (*next)(uint64_t s[2]),
                             uint64_t const JUMP[2],
                             uint64_t s[2]) {
	uint64_t s0 = 0;
	uint64_t s1 = 0;
	/* sizeof JUMP / sizeof *JUMP */
	for(int i = 0; i < 2; i++) {
		for(int b = 0; b < 64; b++) {
			if (JUMP[i] & UINT64_C(1) << b) {
				s0 ^= s[0];
				s1 ^= s[1];
			}
			next(s);
		}
    }
	s[0] = s0;
	s[1] = s1;
    return s0 + s1;
}

uint64_t xorshift128_jump (uint64_t s[2], bool xoro) {
    return xoro ? _xs128_jump (xoroshiro128plus,
                               xoroshiro128plus_JUMP, s)
                : _xs128_jump (xorshift128plus,
                               xorshift128plus_JUMP, s);
}

