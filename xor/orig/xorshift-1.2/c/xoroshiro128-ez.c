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

/* The internal state of the generator. */
static uint64_t x = 0x1LL;

/* The current state of the generator. */
static uint64_t s[2];

/* The current 64-bit value output by the generator (this is not x if STAR32/STAR8/STAR2 is defined.) */
static uint64_t y;

/* The three shifts. */
static int A, B, C;

#ifdef STAR32
// Composed with M_32.
const int64_t M = 2685821657736338717LL;
#endif

#ifdef STAR8
// Composed with M_8.
const int64_t M = 1181783497276652981LL;
#endif

#ifdef STAR2
// Composed with M_2.
const int64_t M = 8372773778140471301LL;
#endif

static int p;
				
static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

void next(void) {
#include "xoroshiro128-next.c"
#ifdef ADD
	y = s[0] + s[1];
#else
	y = s[1] * M;
#endif
}

int main(int argc, char *argv[]) {
	if (argc != 6) {
		fprintf(stderr, "%s A B C NUMBER WINDOW\n", argv[0]);
		exit(1);
	}

	A = atoi(argv[1]);
	B = atoi(argv[2]);
	C = atoi(argv[3]);

	const int n = atoi(argv[4]);
	const int k = atoi(argv[5]);
	unsigned long long c[n + k];
	memset(c, 0, sizeof c);
	
	for(int b = 0; b < 128; b++) {
		memset(s, 0, sizeof s);
		s[b / 64] = 1ULL << b % 64;
	
		for(int i = 0; i < n; i++) {	
			next();
			const int t = __builtin_popcountll(y);
			for(int j = 0; j < k; j++) c[i + j] += t;
		}
	}

	double norm = 1. / (128 * k * 64);
	for(int i = k; i < n; i++) printf("%f\n", c[i] * norm);
}
