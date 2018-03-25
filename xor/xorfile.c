#include "xorfile.h"

void xorbin32 (FILE * file, uint32_t round,
               enum xorshift_t method, uint32_t * seed32) {
    while (round > 0) {
        uint32_t x = xorstream32(method, seed32);
        fwrite (&x, sizeof(uint32_t), 1, file);
        round --;
    }
}

void xorbin64 (FILE * file, uint32_t round,
               enum xorshift_t method, uint64_t * seed64) {
    while (round > 0) {
        uint64_t x = xorstream64(method, seed64);
        fwrite (&x, sizeof(uint64_t), 1, file);
        round --;
    }
}

void xorbin(FILE * file, uint32_t round,
            enum xorshift_t method, uint32_t * seed32) {

    switch (method) {
        
        case XORSHIFT32:
        case XORSHIFT128:
        case XORWOW:
        xorbin32(file, round, method, seed32);
        break;

        case SPLITMIX64:
        case XORSHIFT64STAR:
        case XORSHIFT1024STAR:
        case XORSHIFT128PLUS:
        case XOROSHIRO128PLUS:
        xorbin64(file, round, method, (uint64_t*)seed32);
        break;

        default:
        break;

    }
}

void xorhex32 (FILE * file, uint32_t round,
               enum xorshift_t method, uint32_t * seed32) {
    while (round > 0) {
        fprintf (file, "%08X\n", xorstream32(method, seed32));
        round --;
    }
}

void xorhex64 (FILE * file, uint32_t round,
               enum xorshift_t method, uint64_t * seed64) {
    while (round > 0) {
        fprintf (file, "%016lX\n", xorstream64(method, seed64));
        round --;
    }
}

void xorhex(FILE * file, uint32_t round,
            enum xorshift_t method, uint32_t * seed32) {

    switch (method) {
        
        case XORSHIFT32:
        case XORSHIFT128:
        case XORWOW:
        xorhex32(file, round, method, seed32);
        break;

        case SPLITMIX64:
        case XORSHIFT64STAR:
        case XORSHIFT1024STAR:
        case XORSHIFT128PLUS:
        case XOROSHIRO128PLUS:
        xorhex64(file, round, method, (uint64_t*)seed32);
        break;

        default:
        break;

    }
}

