#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//#define DBGFILE stderr
#ifdef DBGFILE
#   define DBG(...) fprintf(DBGFILE, ##__VA_ARGS__)
#else
#   define DBG(...)
#endif

//////////////////////////////////////////////////////////////////////////////
#define _PRIME_MAX (1024*1024)
static size_t const PRIME_MAX = _PRIME_MAX;
static size_t PRIME_NB = 1;
static uint64_t PRIME[_PRIME_MAX] = {        2,   3,   5,
                                        7,  11,  13,  17,
                                       19,  23,  29,  31,
                                       37,  41,  43,  47,
                                       53,  59,  61,  67,
                                       71,  73,  79,  83,
                                       89,  97, 101, 103,
                                      107, 109, 113, 127 };

static void _dump_prime (FILE* file, size_t n, size_t col) {
    if ((n == 0) || (n > PRIME_NB)) {
        n = PRIME_NB;
    }
    int k = 1;
    for (k = 1; k <= n; k++) {
        //fprintf (file, "%016lX%c", PRIME[k-1], ((k%col) == 0) ? '\n' : ' ');
        //fprintf (file, "%9lu%c", PRIME[k-1], ((k%col) == 0) ? '\n' : ' ');
        fprintf (file, "%lu%c", PRIME[k-1], ((k%col) == 0) ? '\n' : ' ');
    }
    //fprintf (file, "%c%zu\n", ((k%col) == 0) ? ' ' : '\n', PRIME_NB);
}

//////////////////////////////////////////////////////////////////////////////

struct sieve_t {
    unsigned int tests:7;     // whit prime test it passes
    unsigned int prime:1;     // is prime for sureœ
};

void sieve_fprint (FILE* file,
                   struct sieve_t const * s,
                   uint64_t N, size_t col);

struct sieve_t * sieve_create (uint64_t N) {
    // keep only odd numbers
    struct sieve_t * s = malloc ((N/2)*sizeof(struct sieve_t));
    if (s == NULL) {
        return NULL;
    }
    DBG ("SIEVE[%lu]\n", N);
    memset (s, 0xFFFFFFFF, (N/2)*sizeof(struct sieve_t));
    uint64_t p = 3;
//sieve_fprint(stderr, s, N, 80);
    while ((p > 0) && (p < N/3)) {
        PRIME[PRIME_NB++] = p;
        for (uint64_t n = 3; n < N/p; n += 2) {
            if (n*p & 1) {
                size_t odd = (n*p)/2 - 1;
                s[odd].prime = 0;
                // TODO update tests fields
                //s[odd].tests = ???;
            }
        }
//sieve_fprint(stderr, s, N, 80);
        p +=2;
        while ((s[p/2-1].prime == 0) && (p < N/3)) {
            p +=2;
        }
    }
//sieve_fprint(stderr, s, N, 80);
    return s;
}

void sieve_fprint (FILE* file,
                   struct sieve_t const * s,
                   uint64_t N, size_t col) {
    fprintf (file, "12");
    size_t c = 2;
    for (int n = 3; n < N; n += 2) {
        fprintf (file, "%c", s[n/2-1].prime ? '#' : ' ');// TODO tests
        c ++; if (c == col) { fprintf (file, "\n"); c = 0; }
        fprintf (file, " ");
        c ++; if (c == col) { fprintf (file, "\n"); c = 0; }
    }
    if (c > 0) {
        while (c < 80) {
            fprintf (file, "?");
            c++;
        }
    }
    fprintf (file, "\n%016lX\n", N);
}

int main (int argc, char ** argv) {
    for (int k = 1; k < argc; k++) {
        int N = atoi(argv[k]);
        struct sieve_t * s = sieve_create (N);
        if (NULL == s) {
            fprintf (stderr, "can not create sieve %d\n", N);
        } else {
            //sieve_fprint (stdout, s, N, 80);
            free (s);
        }
    }
    //fprintf (stdout, "%zu primes:\n", PRIME_NB);
    _dump_prime (stdout, 0, 1);
    return 0;
}

