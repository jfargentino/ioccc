/*  Written in 2015 by Sebastiano Vigna (vigna@acm.org)
To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.
See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include "splitmix64.h"

uint64_t splitmix64 (uint64_t seed) {
	seed += UINT64_C(0x9E3779B97F4A7C15); // next seed
	seed  = (seed ^ (seed >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
	seed  = (seed ^ (seed >> 27)) * UINT64_C(0x94D049BB133111EB);
	return seed ^ (seed >> 31);
}

