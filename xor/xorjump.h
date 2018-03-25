#ifndef XORJUMP_H
#define XORJUMP_H

#include <stdbool.h>
#include <stdint.h>

/*
 * This is the jump function for the generator. It is equivalent
 * to 2^64 calls to xoroshiro128plus(); it can be used to generate 2^64
 * non-overlapping subsequences for parallel computations.
 *
 * To the extent possible under law, the author has dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * See <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
uint64_t xorshift128_jump (uint64_t seed[static 2], bool xoro);

#endif

