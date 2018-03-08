#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

//////////////////////////////////////////////////////////////////////////////
#define _PRIME_MAX (1024*1024)
static size_t const PRIME_MAX = _PRIME_MAX;
static size_t PRIME_NB = 1;
static uint64_t PRIME[_PRIME_MAX] = { 2 };

static uint64_t sieve_highest_prime (uint64_t N) {
    // keep only odd numbers
    bool * sieve = malloc ((N/2)*sizeof(bool));
    if (sieve == NULL) {
        return 0;
    }
    memset (sieve, true, (N/2)*sizeof(bool));
    uint64_t p = 3;
    size_t k = 1;
    while ((p > 0) && (p < N/3)) {
        PRIME[k++] = p;
        for (uint64_t n = 3; n < N/p; n += 2) {
            if (n*p & 1) {
                size_t odd = (n*p)/2 - 1;
                sieve[odd] = false;
            }
        }
        p +=2;
        while ((sieve[p/2-1] == false) && (p < N/3)) {
            p +=2;
        }
    }
    free(sieve);
    if (k > PRIME_NB) {
        PRIME_NB = k;
    }
    return PRIME[k-1];
}

uint64_t nth(size_t k) {
    if (k == 0) {
        return 0;
    }
    uint64_t N = 128;
    do {
        sieve_highest_prime(N);
        N *= 2;
    } while (PRIME_NB < k);
    return PRIME[k-1];
}

