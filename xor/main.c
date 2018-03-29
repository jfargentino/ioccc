#include "uuid4.h"
#include "xorfile.h"
#include "xorjump.h"
#include "xorshift.h"
#include "xorstream.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*****************************************************************************/

static void usage (FILE * file, char const * argv0) {
    fprintf (file,
"\n%s [-x XORSHIFT] [-b] [-t] [-v] [-o] [-s SEED0 SEED1] [-j] [-l] [-h] [LOOP]\n\n",
             argv0);
    fprintf (file, "Print LOOP (1 per default) uuid4\n");
    fprintf (file, "\t-x XORSHIFT to benchmark an algo, see \"-l\"(*).\n");
    fprintf (file, "\t-b for the benchmark mode (dieharder) in binary.\n");
    fprintf (file, "\t-t for the benchmark mode in text.\n");
    fprintf (file, "\t-v verbose mode, displays the seed on stderr.\n");
    fprintf (file, "\t-o to use xoroshiro in uuid.\n");
    fprintf (file, "\t-s SEED0 SEED1 to set the seed(**).\n");
    fprintf (file, "\t-j each \"-j\" to jump 2^64 loop(***).\n");
    fprintf (file, "\t-l to list xorshift available.\n");
    fprintf (file, "\t-h to print this help.\n\n");
    fprintf (file, "*  : Only xorshift128plus and xoroshiro128plus\n");
    fprintf (file, "     are availables for uuid4.\n");
    fprintf (file, "** : Only 2x64bits seed supported.\n");
    fprintf (file, "***: Only xorshift128plus and xoroshiro128plus\n");
    fprintf (file, "     are supporting jump.\n\n");
}

/*****************************************************************************/

#define _VERBOSE_print(verbose, file, fmt, ...) \
    if (verbose) { fprintf (file, fmt, ## __VA_ARGS__); }

static void _VERBOSE_print_seed (bool verbose,
                                 enum xorshift_t xor_shift,
                                 uint64_t const * seed64) {

    uint32_t const * seed32 = (uint32_t const *) seed64;

    switch (xor_shift) {

        case XORSHIFT32:
        _VERBOSE_print (verbose, stderr, "%08X\n", *seed32);
        return;
        
        case XORSHIFT128:
        _VERBOSE_print (verbose, stderr,
                        "%08X %08X %08X %08X\n",
                        seed32[0], seed32[1], seed32[2], seed32[3]);
        return;

        case XORWOW:
        _VERBOSE_print (verbose, stderr,
                        "%08X %08X %08X %08X %08X\n",
                        seed32[0], seed32[1], seed32[2], seed32[3],
                        seed32[4]);
        return;

        case SPLITMIX64:
        case XORSHIFT64STAR:
        _VERBOSE_print (verbose, stderr, "%016lX\n", *seed64);
        return;
        
        case XORSHIFT116PLUS:
        case LEHMER128:
        case XORSHIFT128PLUS:
        case XOROSHIRO128PLUS:
        _VERBOSE_print (verbose, stderr,
                        "%016lX %016lX\n",
                        seed64[0], seed64[1]);
        return;

        case XORSHIFT1024STAR:
        _VERBOSE_print (verbose, stderr,
                        "%016lX %016lX %016lX %016lX\n",
                        seed64[0], seed64[1], seed64[2], seed64[3]);
        _VERBOSE_print (verbose, stderr,
                        "%016lX %016lX %016lX %016lX\n",
                        seed64[4], seed64[5], seed64[6], seed64[7]);
        _VERBOSE_print (verbose, stderr,
                        "%016lX %016lX %016lX %016lX\n",
                        seed64[8], seed64[9], seed64[10], seed64[11]);
        _VERBOSE_print (verbose, stderr,
                        "%016lX %016lX %016lX %016lX\n",
                        seed64[12], seed64[13], seed64[14], seed64[15]);
        return;

        case XORSHIFT4096STAR:
        for (int k = 0; k < 8; k++) {
            _VERBOSE_print (verbose, stderr,
                            "%016lX %016lX %016lX %016lX "
                            "%016lX %016lX %016lX %016lX\n",
                            seed64[k+0], seed64[k+1], seed64[k+2], seed64[k+3],
                            seed64[k+4], seed64[k+5], seed64[k+6], seed64[k+7]);
        }
        return;

        default:
        return;
    }
}

/*****************************************************************************/

static long _dt (struct timespec const * t1,
                 struct timespec const * t0) {
    return (t1->tv_sec - t0->tv_sec) * 1000000000
                                     + (t1->tv_nsec - t0->tv_nsec);
}

/*****************************************************************************/

static char const * const XORSHIFT_LITERAL[XORSHIFT_NB] = {
    "xorshift32",
    "xorshift128",
    "xorwow",
    "splitmix64",
    "xorshift64star",
    "xorshift116plus",
    "lehmer128",
    "xorshift128plus",
    "xoroshiro128plus"
    "xorshift1024star",
    "xorshift4096star",
};

static enum xorshift_t str2xorshift (char * const str) {
    enum xorshift_t x = XORSHIFT32;
    while (x < XORSHIFT_NB) {
        if (strcmp (str, XORSHIFT_LITERAL[x]) == 0) {
            return x;
        }
        x ++;
    }
    return x;
}

/*****************************************************************************/

int main (int argc, char ** argv) {
    
    enum xorshift_t xor_shift = XORSHIFT128PLUS;
    bool bench   = false;
    bool text    = false;
    bool verbose = false;
    bool xoro    = false;
    uint64_t seed[16] = { 0 };
    seed16x64 (seed);
    int jump = 0;
    int loop = 1;

    for (int k = 1; k < argc; k++) {

        if (*argv[k] == '-') {
            argv[k] ++;
        }

        switch (*argv[k]) {
            
            case 'l':
            case 'L':
            for (enum xorshift_t x = XORSHIFT32; x < XORSHIFT_NB; x++) {
                fprintf (stdout, "%16s %2dx%d%s\n",
                         XORSHIFT_LITERAL[x],
                         (x < SPLITMIX64) ? xorseed32_length(x)
                                          : xorseed64_length(x),
                         (x < SPLITMIX64) ? 32 : 64,
                         (x == xor_shift) ? " -> default" : "");
            }
            exit (EXIT_SUCCESS);
            
            case 'x':
            case 'X':
            if (k + 1 >= argc) {
                fprintf (stderr, "xorshift option needs 1 argument.\n");
                usage (stdout, argv[0]);
                exit (EXIT_FAILURE);
            }
            xor_shift = str2xorshift (argv[k+1]);
            if (xor_shift >= XORSHIFT_NB) {
                fprintf (stderr, "xorshift %s unknown.\n", argv[k+1]);
                usage (stdout, argv[0]);
                exit (EXIT_FAILURE);
            }
            k ++;
            // TODO for now, force verbose and benchmark
            verbose = true;
            bench   = true;
            break;
            
            case 'b':
            case 'B':
            bench = true;
            break;
            
            case 't':
            case 'T':
            bench = true;
            text  = true;
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
                fprintf (stderr, "seed option needs 2 arguments.\n");
                usage (stdout, argv[0]);
                exit (EXIT_FAILURE);
            }
            // TODO check endptr != argv[k+x]
            // TODO other seed size
            seed[0] = strtoull (argv[k+1], NULL, 0);
            seed[1] = strtoull (argv[k+2], NULL, 0);
            k += 2;
            break;
            
            case 'j':
            case 'J':
            jump ++;
            break;

            case 'h':
            case 'H':
            case '?':
            usage (stdout, argv[0]);
            exit (EXIT_SUCCESS);

            default:
            loop = atoi (argv[k]);
            if (loop <= 0) {
                usage (stdout, argv[0]);
                exit (EXIT_FAILURE);
            }
            break;
        }
    }
    
    _VERBOSE_print_seed (verbose, xor_shift, seed);
    
    struct timespec res = { 0 };
    clock_getres (CLOCK_MONOTONIC, &res);

    struct timespec t0 = { 0 };
    clock_gettime (CLOCK_MONOTONIC, &t0);

    int j = jump;
    while (j) {
        xorshift128_jump (seed, xoro);
        _VERBOSE_print_seed (verbose, xor_shift, seed);
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

    if (bench) {
        // spit on stdout for dieharder
        if (text) {
            if (xor_shift < SPLITMIX64) {
                xorhex32 (stdout, loop, xor_shift, seed);
            } else {
                xorhex64 (stdout, loop, xor_shift, seed);
            }
        } else {
            //xorbin64 (stdout, loop, xor_shift, seed);
            xorbin32 (stdout, loop, xor_shift, seed);
        }
    } else {
        // Print UUID4
        while (loop > 0) {
            char uuid[UUID4_LEN];
            xoro ? uuid4_generate_xoro (seed, uuid)
                 : uuid4_generate (seed, uuid);
            fprintf (stdout, "%*.*s\n", UUID4_LEN-1, UUID4_LEN-1, uuid);
            _VERBOSE_print_seed (verbose, xor_shift, seed);
            loop --;
        }
    }

    clock_gettime (CLOCK_MONOTONIC, &t0);
    if ( (bench) && (loop > 0) ) {
        long ns = _dt (&t0, &t1);
        fprintf (stderr,
                 "%ldns/%s, %ldns for %d loops,\n"
                 "resolution %ld.%09ldns\n",
                 ns/loop, XORSHIFT_LITERAL[xor_shift], ns, loop,
                 res.tv_sec, res.tv_nsec);
    }

    exit (EXIT_SUCCESS);
}

