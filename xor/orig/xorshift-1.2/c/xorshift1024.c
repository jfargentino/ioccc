/*		 
 * Copyright (C) 2014-2015 Sebastiano Vigna 
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

/* The current state of the generator. */
static uint64_t s[16];
static int p;

/* The current 64-bit value output by the generator (this is not x if STAR32/STAR8/STAR2 is defined.) */
static uint64_t y;

/* The three shifts. */
static int A, B, C;

#if defined(STAR32)
#define NAME "xorshift1024*32"
// Composed with M_32.
const int64_t M = 2685821657736338717LL;
#elif defined(STAR8)
#define NAME "xorshift1024*8"
// Composed with M_8.
const int64_t M = 1181783497276652981LL;
#elif defined(STAR2)
#define NAME "xorshift1024*2"
// Composed with M_2.
const int64_t M = 8372773778140471301LL;
#elif defined(STARPHI)
#define NAME "xorshift1024*phi"
// Composed with 2^64 * (phi - 1).
const int64_t M = 0x9e3779b97f4a7c13;
#elif defined(ADD)
#define NAME "xorshift1024+"
#else
#define NAME "xorshift1024"
const int64_t M = 1;
#endif

				
void next(void) {
#include "xorshift1024-next.c"
#if defined(ADD)
	y = REV(s[p] + s0);
#else
	y = REV(s[p] * M);
#endif
}

/* True if the lower part of y has already been returned. */
static int lower;

/* Note that this function returns a 32-bit number. */
unsigned long xorshift(void *unused0, void *unused1) {
	if (lower ^= 1) return (uint32_t)y;
	const uint32_t result = y >> 32;
	next();
	return result;
}

#define NORM_64 ((1./4) / (1LL << 62))

double xorshift01(void *unused0, void *unused1) {
	if (lower) next(); // Refresh y (lower part has already been used).
	const double result = y * NORM_64;
	next();
	lower = 0;
	return result;
}

void write_state(void *unused) {
	for(int i = 0; i < 16; i++) printf("%s%llu", i ? " " : "", (unsigned long long)s[i]);
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
	if (argc != 16 + 5) {
		fprintf(stderr, "%s 0 A B C SEED (16 64-bit integers)\n", argv[0]);
		exit(1);
	}

	if (atoi(argv[1]) != 0) abort();

	A = atoi(argv[2]);
	B = atoi(argv[3]);
	C = atoi(argv[4]);

	for(int i = 0; i < 16; i++) s[i] = strtoull_check(argv[5 + i]);

#ifdef TESTU01
	char s[100];
	sprintf(s, NAME REVERSE_INFIX "-%d-%d-%d (algorithm %s)", A, B, C, argv[1]);

	unif01_Gen gen;
	gen.name = s;
	gen.Write = write_state;
	gen.GetBits = xorshift;
	gen.GetU01 = xorshift01;
	TESTU01(&gen);
	return 0;
#else
	assert(freopen(NULL, "wb", stdout));

	for(;;) {
		const uint32_t z = xorshift(NULL, NULL);
		fwrite(&z, sizeof z, 1, stdout);
	}
#endif
}
