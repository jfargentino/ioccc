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

#include "SFMT/SFMT.h"
#include "SFMT/SFMT.c"
#include <stdint.h>

sfmt_t sfmt = { { { .u64 = { 1, 1 } } } };

#define INIT sfmt_init_gen_rand(&sfmt, -1);

#ifdef HARNESS_DOUBLE

static inline double to_double(uint64_t x) {
	const union { uint64_t i; double d; } u = { .i = UINT64_C(0x3FF) << 52 | x >> 12 };
	return u.d - 1.0;
}

#define NEXT to_double(sfmt_genrand_uint64(&sfmt))

#else
#define NEXT sfmt_genrand_uint64(&sfmt)
#endif

#define HARNESS_ADD
#include "harness.c"
