#include <stdint.h>

// PCG64 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)

static uint64_t x;
static uint64_t inc = 1442695040888963407;

static uint64_t inline next(void) {
	const uint64_t old_x = x;
	x = old_x * UINT64_C(6364136223846793005) + inc;
	const uint64_t word = ((old_x >> ((old_x >> 59u) + 5u)) ^ old_x) * UINT64_C(12605985483714917081);
	return (word >> 43u) ^ word;
}

#define HARNESS_ADD
#include "harness.c"
