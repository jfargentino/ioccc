/*		 
 * Copyright (C) 2014 Sebastiano Vigna 
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 3 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "reverse.h"

#ifdef TESTU01
#include <unif01.h>
#include <bbattery.h>
#endif

static union {
	__int128 x;
	uint64_t s[2];
} state = { .s = { 1, 1 } };

uint64_t y;

void next(void) {
	state.x *= ((__int128)0x12e15e35b500f16e << 64 | 0x2e714eb2b37916a5);
	y = REV(state.s[1]);
}

/* True if the lower part of y has already been returned. */
static int lower;

/* Note that this function returns a 32-bit number. */
unsigned long lehmer128(void *unused0, void *unused1) {
	if (lower ^= 1) return (uint32_t)y;
	const uint32_t result = y >> 32;
	next();
	return result;
}

#define NORM_64 ((1./4) / (1LL << 62))

double lehmer12801(void *unused0, void *unused1) {
	if (lower) next(); // Refresh y (lower part has already been used).
	const double result = y * NORM_64;
	next();
	lower = 0;
	return result;
}

void write_state(void *unused) {
	printf (" s1 = %llx s0 = %llx\n", (unsigned long long)state.s[1], (unsigned long long)state.s[0]);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "%s SEED (two 64-bit integers, the second one odd)\n", argv[0]);
		exit(1);
	}

	state.s[1] = strtoull(argv[1], NULL, 0);
	state.s[0] = strtoull(argv[2], NULL, 0);

	if (state.s[0] % 2 == 0) {
		fprintf(stderr, "The second value of the seed must be odd\n");
		exit(1);
	}

#ifdef TESTU01
	unif01_Gen gen;
	gen.name = "lehmer128" REVERSE_INFIX;
	gen.Write = write_state;
	gen.GetBits = lehmer128;
	gen.GetU01 = lehmer12801;
	TESTU01(&gen);
#else
	assert(freopen(NULL, "wb", stdout));

	for(;;) {
		const uint32_t z = lehmer128(NULL, NULL);
		fwrite(&z, sizeof z, 1, stdout);
	}
#endif

	return 0;
}
