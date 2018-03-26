#include "seed.h"
#include <stdio.h>

/* Generic ******************************************************************/

enum {
    UUID4_ESUCCESS =  0,
    UUID4_EFAILURE = -1
};

static char const * const RANDOM_FILE_NAME = "/dev/urandom";
//static char const * const RANDOM_FILE_NAME = "/dev/random";

#define _init_once(type_t, seed, seed_len)                                 \
    static type_t _init_##type_t##_once (type_t * seed, int seed_len) {    \
        FILE *fp = fopen(RANDOM_FILE_NAME, "rb");                          \
        if (!fp) {                                                         \
            return UUID4_EFAILURE;                                         \
        }                                                                  \
        int res = fread(seed, sizeof(type_t), seed_len, fp);               \
        fclose(fp);                                                        \
        if ( res != seed_len * sizeof(type_t) ) {                          \
            return UUID4_EFAILURE;                                         \
        }                                                                  \
        return UUID4_ESUCCESS;                                             \
    }

#define _sum(type_t, seed, seed_len)                                \
    static type_t _##type_t##_sum(type_t * seed, int seed_len) {    \
        type_t sum = 0;                                             \
        while (seed_len > 0) {                                      \
            sum += seed[seed_len-1];                                \
            seed_len --;                                            \
        }                                                           \
        return sum;                                                 \
    }

#define _init_while(type_t, seed, seed_len)                                \
    static type_t _init_##type_t##_while(type_t * seed, int seed_len) {    \
    do {                                                                   \
        if (_init_##type_t##_once(seed, seed_len) != UUID4_ESUCCESS) {     \
            return 0;                                                      \
        }                                                                  \
    } while (_##type_t##_sum (seed, seed_len) == 0);                       \
    return _##type_t##_sum (seed, seed_len);                               \
}

/* 32 bits ******************************************************************/

_init_once(int32_t, seed, seed_len)
_sum(int32_t, seed, seed_len)

static int32_t _init_int32_t_while(int32_t * seed, int seed_len);
_init_while(int32_t, seed, seed_len)

uint32_t seedx32(uint32_t * seed, int seed_len) {
    return _init_int32_t_while(seed, seed_len);
}

/* 64 bits ******************************************************************/

_init_once(int64_t, seed, seed_len)
_sum(int64_t, seed, seed_len)

static int64_t _init_int64_t_while(int64_t * seed, int seed_len);
_init_while(int64_t, seed, seed_len)

uint64_t seedx64(uint64_t * seed, int seed_len) {
    return _init_int64_t_while(seed, seed_len);
}

