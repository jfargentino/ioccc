/**
 * Copyright (c) 2016 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "xorshift.h"
#include "uuid4.h"
#include <stdio.h>

/****************************************************************************/

enum {
    UUID4_ESUCCESS =  0,
    UUID4_EFAILURE = -1
};

static int _init_seed_once(uint64_t seed[2]) {
  int res;
  FILE *fp = fopen("/dev/urandom", "rb");
  if (!fp) {
    return UUID4_EFAILURE;
  }
  res = fread(seed, 1, 2 * sizeof(uint64_t), fp);
  fclose(fp);
  if ( res !=  2 * sizeof(uint64_t) ) {
    return UUID4_EFAILURE;
  }
  return UUID4_ESUCCESS;
}

uint64_t uuid4_init_seed(uint64_t seed[2]) {
    do {
        if (_init_seed_once(seed) != UUID4_ESUCCESS) {
            return 0;
        }
    } while (seed[0] == 0 && seed[1] == 0);
    return seed[0] + seed[1];
}

/****************************************************************************/

static uint64_t _uuid4_generate(uint64_t (*xs128)(uint64_t s[2]),
                                uint64_t seed[2],
                                char dst[UUID4_LEN]) {
    char const * template = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    char const * digit = "0123456789abcdef";
    union { unsigned char b[16]; uint64_t word[2]; } s;
    int i, n;
    /* get random */
    s.word[0] = xs128(seed);
    s.word[1] = xs128(seed);
    /* build string */
    i = 0;
    while (*template) {
        n = s.b[i >> 1];
        n = (i & 1) ? (n >> 4) : (n & 0xf);
        switch (*template) {
            case 'x' : *dst = digit[n];             i++; break;
            case 'y' : *dst = digit[(n & 0x3) + 8]; i++; break;
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

