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
#include <inttypes.h>

#define HAVE_SSE2

#include "SFMT/SFMT.h"
#include "SFMT/SFMT.c"

sfmt_t sfmt;

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "%s NUMBER WINDOW\n", argv[0]);
		exit(1);
	}
	const int n = atoi(argv[1]);
	const int k = atoi(argv[2]);
	unsigned long long c[n + k];
	memset(c, 0, sizeof c);
	
	for(int b = 0; b < SFMT_N64 * 64; b++) {
		memset(&sfmt, 0, sizeof sfmt);
		((uint64_t *)sfmt.state)[b / 64] |= 1ULL << (63 - b % 64);
		sfmt.idx = SFMT_N32;

		for(int i = 0; i < n; i++) {	
			const int t = __builtin_popcountll(sfmt_genrand_uint64(&sfmt));
			for(int j = 0; j < k; j++) c[i + j] += t;
		}
	}

	double norm = 1. / (SFMT_N64 * 64 * k * 64);
	for(int i = k; i < n; i++) printf("%f\n", c[i] * norm);
}
