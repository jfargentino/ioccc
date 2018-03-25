#include "seed.h"
#include <stdio.h>

/****************************************************************************/

enum {
    UUID4_ESUCCESS =  0,
    UUID4_EFAILURE = -1
};

static int _init_seed_once(uint32_t * seed, size_t seed_length) {
  int res;
  FILE *fp = fopen("/dev/urandom", "rb");
  if (!fp) {
    return UUID4_EFAILURE;
  }
  res = fread(seed, 1, seed_length * sizeof(uint32_t), fp);
  fclose(fp);
  if ( res != seed_length * sizeof(uint32_t) ) {
    return UUID4_EFAILURE;
  }
  return UUID4_ESUCCESS;
}

uint32_t _seed_sum(uint32_t * seed, size_t seed_len) {
    uint32_t sum = 0;
    while (seed_len > 0) {
        sum += seed[seed_len-1];
        seed_len --;
    }
    return sum;
}

uint32_t _init_seed_while(uint32_t * seed, size_t seed_len) {
    do {
        if (_init_seed_once(seed, seed_len) != UUID4_ESUCCESS) {
            return 0;
        }
    } while (_seed_sum (seed, seed_len) == 0);
    return _seed_sum (seed, seed_len);
}

uint32_t seed32(uint32_t * seed) {
    return _init_seed_while((uint32_t*)seed, 1);
}

uint32_t seed64(uint32_t * seed) {
    return _init_seed_while((uint32_t*)seed, 2);
}

uint32_t seed128(uint32_t * seed) {
    return _init_seed_while((uint32_t*)seed, 4);
}

uint32_t seed160(uint32_t * seed) {
    return _init_seed_while((uint32_t*)seed, 5);
}

uint32_t seed1024(uint32_t * seed) {
    return _init_seed_while((uint32_t*)seed, 16);
}

