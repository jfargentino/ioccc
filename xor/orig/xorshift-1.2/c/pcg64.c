#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>
#include "reverse.h"

#ifdef TESTU01
#include <unif01.h>
#include <bbattery.h>
#endif

#ifdef REVERSE
#define NAME "pcg64-rev"
#define REV(x) (reverse(x))
#else
#define NAME "pcg64"
#define REV(x) (x)
#endif

/* The internal state of the generator. */
static uint64_t x, inc;

/* The current 64-bit value output by the generator. */
static uint64_t y;

/* True if the lower part of y has already been returned. */
static int lower;

void next(void) {
	const uint64_t old_x = x;
	x = x * UINT64_C(6364136223846793005) + inc;
	const uint64_t word = ((old_x >> ((old_x >> 59u) + 5u)) ^ old_x) * UINT64_C(12605985483714917081);
	y = REV((word >> 43u) ^ word);
}

/* Note that this function returns a 32-bit number. */
unsigned long pcg64i(void *unused0, void *unused1) {
	if (lower ^= 1) return (uint32_t)y;
	const uint32_t result = y >> 32;
	next();
	return result;
}

#define NORM_64 ((1./4) / (1LL << 62))

double pcg6401(void *unused0, void *unused1) {
	if (lower) next(); // Refresh y (lower part has already been used).
	const double result = y * NORM_64;
	next();
	lower = 0;
	return result;
}

void write_state(void *unused) {
	printf(" ");
	printf("0x%" PRIx64 " ", x);
	printf("0x%" PRIx64, inc);
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
	if (argc != 2 + 1) {
		fprintf(stderr, "%s SEED (2 64-bit integers)\n", argv[0]);
		exit(1);
	}
	
	x = strtoull_check(argv[1]);
	inc = strtoull_check(argv[2]) | 1;

#ifdef TESTU01
	unif01_Gen pcg64;
	pcg64.name = NAME;
	pcg64.Write = write_state;
	pcg64.GetBits = pcg64i;
	pcg64.GetU01 = pcg6401;
	TESTU01(&pcg64);
#else
	int x;
	for(;;) {
		x = pcg64i(NULL,NULL);
		fwrite(&x, 4, 1, stdout);
	}
#endif
	return 0;
}
