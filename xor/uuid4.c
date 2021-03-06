/**
 * Copyright (c) 2016 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "xorshift.h"
#include "uuid4.h"

// TODO take a look at libuuid
// TODO other xorshift

static uint64_t _uuid4_generate(uint64_t (*xs128)(uint64_t s[2]),
                                uint64_t seed[2],
                                char dst[UUID4_LEN]) {
    char const * template = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    char const * digit = "0123456789abcdef";
    union { unsigned char b[16]; uint64_t word[2]; } s;
    /* get random */
    s.word[0] = xs128(seed);
    s.word[1] = xs128(seed);
    /* build string */
    int k = 0;
    while (*template) {
        int n = s.b[k >> 1];
            n = (k & 1) ? (n >> 4) : (n & 0xf);
        switch (*template) {
            case 'x' : *dst = digit[n];             k++; break;
            case 'y' : *dst = digit[(n & 0x3) + 8]; k++; break;
            default  : *dst = *template;
        }
        dst++, template++;
    }
    // trailing '\0'
    *dst = *template;
    if (*dst != '\0') {
        return 0;
    }
    return s.word[0] + s.word[1];
}

uint64_t uuid4_generate(uint64_t seed[2], char dst[UUID4_LEN]) {
    return _uuid4_generate (xorshift128plus, seed, dst);
}

uint64_t uuid4_generate_xoro(uint64_t seed[2], char dst[UUID4_LEN]) {
    return _uuid4_generate (xoroshiro128plus, seed, dst);
}

