/*		 
 * Copyright (C) 2015 Sebastiano Vigna 
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

#include <immintrin.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "reverse.h"

#ifdef TESTU01
#include <unif01.h>
#include <bbattery.h>
#endif

#define NAME "sfmt"

#include "SFMT/SFMT.h"
#include "SFMT/SFMT.c"

sfmt_t sfmt;

/* True if the lower part of y has already been returned. */
static int lower;

static uint64_t y;

#define NORM_64 ((1./4) / (1LL << 62))

double sfmt01(void *unused0, void *unused1) {
	if (lower) y = REV(sfmt_genrand_uint64(&sfmt)); // Refresh y (lower part has already been used).
	const double result = y * NORM_64;
	y = REV(sfmt_genrand_uint64(&sfmt));
	lower = 0;
	return result;
}

/* Note that this function returns a 32-bit number. */
unsigned long sfmt32(void *unused0, void *unused1) {
	if (lower ^= 1) return (uint32_t)y;
	const uint32_t result = y >> 32;
	y = REV(sfmt_genrand_uint64(&sfmt));
	return result;
}

void write_state(void *unused) {
	for(int i = 0; i < SFMT_N*2; i++) printf("%s%" PRIx64, i ? " " : "", ((uint64_t *)sfmt.state)[i]);
	printf("\n");
}

uint64_t strtoull_check(char *p) {
	const uint64_t result = strtoull(p, NULL, 0);
	if (errno != 0) {
		fprintf(stderr, "Error while parsing seed: %s\n", strerror(errno));
		exit(1);
	}
	if (1 << 10 < result && result < 1ULL << 32) fprintf(stderr, "Suspiciosly 32-bit value while parsing seed: %llu\n", (unsigned long long)result);
	return result;
}


int main(int argc, char *argv[]) {
	if (argc != SFMT_N64 + 1) {
		fprintf(stderr, "%s SEED (%d 64-bit integers)\n", argv[0], SFMT_N64);
		exit(1);
	}

	for(int i = 0; i < SFMT_N64; i++) ((uint64_t *)sfmt.state)[i] = strtoull_check(argv[1 + i]);
	period_certification(&sfmt);
	sfmt.idx = SFMT_N32;

#ifdef TESTU01
	char s[100];
	sprintf(s, NAME "%d" REVERSE_INFIX, SFMT_MEXP);
	unif01_Gen gen;
	gen.name = s;
	gen.Write = write_state;
	gen.GetBits = sfmt32;
	gen.GetU01 = sfmt01;
	TESTU01(&gen);
	return 0;
#else
	assert(freopen(NULL, "wb", stdout));

	for(;;) {
		const uint32_t z = sfmt(NULL, NULL);
		fwrite(&z, sizeof z, 1, stdout);
	}
#endif
}
