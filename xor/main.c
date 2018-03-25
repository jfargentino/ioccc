#include "uuid4.h"
#include "xorshift.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define _VERBOSE_print(verbose, file, fmt, ...) \
    if (verbose) { fprintf (file, fmt, ## __VA_ARGS__); }

static void _VERBOSE_print_seed (bool verbose, uint64_t seed[2]) {
    _VERBOSE_print (verbose, stderr, "0x%016lX 0x%016lX\n", seed[0], seed[1]);
}

static long _dt (struct timespec const * t1,
                 struct timespec const * t0) {
    return (t1->tv_sec - t0->tv_sec) * 1000000000
                                     + (t1->tv_nsec - t0->tv_nsec);
}

int main (int argc, char ** argv) {
    
    bool bench   = false;
    bool verbose = false;
    bool xoro    = false;
    uint64_t seed[2] = { 0 };
    uint64_t root = uuid4_init_seed (seed);
    int jump = 0;
    int loop = 1;

    for (int k = 1; k < argc; k++) {

        if (*argv[k] == '-') {
            argv[k] ++;
        }

        switch (*argv[k]) {
            
            case 'b':
            case 'B':
            bench = true;
            break;
            
            case 'v':
            case 'V':
            verbose = true;
            break;
            
            case 'o':
            case 'O':
            xoro = true;
            break;
            
            case 's':
            case 'S':
            if (k + 2 >= argc) {
                // TODO usage
                fprintf (stderr, "seed option need at least 2 arguments.\n");
                exit (EXIT_FAILURE);
            }
            // TODO check endptr != argv[k+x]
            seed[0] = strtoul (argv[k+1], NULL, 0);
            seed[1] = strtoul (argv[k+2], NULL, 0);
            root = seed[0] + seed[1];
            k += 2;
            break;
            
            case 'j':
            case 'J':
            jump ++;
            break;

            case 'h':
            case 'H':
            case '?':
            // TODO usage
            exit (EXIT_SUCCESS);

            default:
            loop = atoi (argv[k]);
            if (loop <= 0) {
                // TODO usage
                exit (EXIT_FAILURE);
            }
            break;
        }
    }
    
    _VERBOSE_print_seed (verbose, seed);
    
    struct timespec res = { 0 };
    clock_getres (CLOCK_MONOTONIC, &res);

    struct timespec t0 = { 0 };
    clock_gettime (CLOCK_MONOTONIC, &t0);

    int j = jump;
    while (j) {
        root = xorshift128_jump (seed, xoro);
        _VERBOSE_print_seed (verbose, seed);
        j --;
    }

    struct timespec t1 = { 0 };
    clock_gettime (CLOCK_MONOTONIC, &t1);
    if ( (bench) && (jump > 0) ) {
        long ns = _dt (&t1, &t0);
        fprintf (stderr,
                 "%ldns/jump, %ldns for %d jump(s), resolution %ld.%09ldns\n",
                 ns/jump, ns, jump, res.tv_sec, res.tv_nsec);
    }

    int l = loop;
    while (l) {
        char uuid[UUID4_LEN];
        root = xoro ? uuid4_generate_xoro (seed, uuid)
                    : uuid4_generate (seed, uuid);
        if (bench) {
            fwrite (seed, sizeof(uint64_t), 2, stdout);
        } else {
            fprintf (stdout, "%*.*s\n", UUID4_LEN-1, UUID4_LEN-1, uuid);
        }
        _VERBOSE_print_seed (verbose, seed);
        l --;
    }
    
    clock_gettime (CLOCK_MONOTONIC, &t0);
    if ( (bench) && (loop > 0) ) {
        long ns = _dt (&t0, &t1);
        fprintf (stderr,
                 "%ldns/uuid, %ldns for %d uuid(s), resolution %ld.%09ldns\n",
                 ns/loop, ns, loop, res.tv_sec, res.tv_nsec);
    }

    exit (EXIT_SUCCESS);
}

