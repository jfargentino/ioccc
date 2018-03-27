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


// TODO ////////////////////////////////////////////////////////////////////////

/* This is the jump function for the xorshift1024star generator.
 * It is equivalent to 2^512 calls to next(); it can be used to generate 2^512
   non-overlapping subsequences for parallel computations. */

void jump(void) {
	static const uint64_t JUMP[] = { 0x84242f96eca9c41d,
		0xa3c65b8776f96855, 0x5b34a39f070b5837, 0x4489affce4f31a1e,
		0x2ffeeb0a48316f40, 0xdc2d9891fe68c022, 0x3659132bb12fea70,
		0xaac17d8efa43cab8, 0xc4cb815590989b13, 0x5ee975283d71c93b,
		0x691548c86c1bd540, 0x7910c41d10a1e6a5, 0x0b5fc64563b3e2a8,
		0x047f7684e9fc949d, 0xb99181f2d8f685ca, 0x284600e3f30e38c3
	};

	uint64_t t[16] = { 0 };
	for(int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
		for(int b = 0; b < 64; b++) {
			if (JUMP[i] & UINT64_C(1) << b)
				for(int j = 0; j < 16; j++)
					t[j] ^= s[(j + p) & 15];
			next();
		}

	for(int j = 0; j < 16; j++)
		s[(j + p) & 15] = t[j];
}

