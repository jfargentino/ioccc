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

uint64_t x, y;

void next(void) {
	uint64_t z = (x += 0x9E3779B97F4A7C15ULL);
	z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
	z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
	y = REV(z ^ (z >> 31));
}

/* True if the lower part of y has already been returned. */
static int lower;

/* Note that this function returns a 32-bit number. */
unsigned long splittable(void *unused0, void *unused1) {
	if (lower ^= 1) return (uint32_t)y;
	const uint32_t result = y >> 32;
	next();
	return result;
}

#define NORM_64 ((1./4) / (1LL << 62))

double splittable01(void *unused0, void *unused1) {
	if (lower) next(); // Refresh y (lower part has already been used).
	const double result = y * NORM_64;
	next();
	lower = 0;
	return result;
}

void write_state(void *unused) {
	printf (" x = %llx\n", (unsigned long long)x);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "%s SEED (a 64-bit integer)\n", argv[0]);
		exit(1);
	}

	x = strtoull(argv[1], NULL, 0);

#ifdef TESTU01
	unif01_Gen gen;
	gen.name = "splittable" REVERSE_INFIX;
	gen.Write = write_state;
	gen.GetBits = splittable;
	gen.GetU01 = splittable01;
	TESTU01(&gen);
#else
	assert(freopen(NULL, "wb", stdout));

	for(;;) {
		const uint32_t z = splittable(NULL, NULL);
		fwrite(&z, sizeof z, 1, stdout);
	}
#endif

	return 0;
}
