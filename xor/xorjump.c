#include "xorjump.h"
#include "xorshift.h"

static uint64_t const xorshift128plus_JUMP[] = { 0x8a5cd789635d2dff,
                                                 0x121fd2155c472f96 };

static uint64_t const xoroshiro128plus_JUMP[] = { 0xbeac0467eba5facb,
                                                  0xd86b048b86aa9922 };

static uint64_t _xs128_jump (uint64_t (*next)(uint64_t s[2]),
                             uint64_t const JUMP[2],
                             uint64_t seed[2]) {
	uint64_t s0 = 0;
	uint64_t s1 = 0;
	/* sizeof JUMP / sizeof *JUMP */
	for(int i = 0; i < 2; i++) {
		for(int b = 0; b < 64; b++) {
			if (JUMP[i] & UINT64_C(1) << b) {
				s0 ^= seed[0];
				s1 ^= seed[1];
			}
			next(seed);
		}
    }
	seed[0] = s0;
	seed[1] = s1;
    return s0 + s1;
}

uint64_t xorshift128_jump (uint64_t seed[2], bool xoro) {
    return xoro ? _xs128_jump (xoroshiro128plus,
                               xoroshiro128plus_JUMP, seed)
                : _xs128_jump (xorshift128plus,
                               xorshift128plus_JUMP, seed);
}

