#include "uuid4.h"
#include "xorshift128.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int _scmp (char const * left, char const * right) {
    if (left == NULL) {
        return (right == NULL) ? 0 : -1;
    }
    if (right == NULL) {
        return (left == NULL) ? 0 : +1;
    }
    while ( (*left != '\0') && (*right != '\0') && (*left == *right) ) {
        left ++;
        right ++;
    }
    return *left - *right;
}

#define _VERBOSE_print(verbose, file, fmt, ...) \
    if (verbose) { fprintf (file, fmt, ## __VA_ARGS__); }

static void _VERBOSE_print_seed (bool verbose, uint64_t seed[2]) {
    _VERBOSE_print (verbose, stderr, "0x%016lX 0x%016lX\n", seed[0], seed[1]);
}

int main (int argc, char ** argv) {
    
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

    while (jump) {
        root = xorshift128_jump (seed, xoro);
        _VERBOSE_print_seed (verbose, seed);
        jump --;
    }

    while (loop) {
        char dst[UUID4_LEN];
        root = xoro ? uuid4_generate_xoro (seed, dst)
                    : uuid4_generate (seed, dst);
        fprintf (stdout, "%*.*s\n", UUID4_LEN-1, UUID4_LEN-1, dst);
        _VERBOSE_print_seed (verbose, seed);
        loop --;
    }

    exit (EXIT_SUCCESS);
}

