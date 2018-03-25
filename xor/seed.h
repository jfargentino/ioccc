#ifndef SEED_H
#define SEED_H

#include <stdint.h>

uint32_t seed32(uint32_t * seed);

uint32_t seed64(uint32_t * seed);

uint32_t seed128(uint32_t * seed);

uint32_t seed160(uint32_t * seed);

uint32_t seed1024(uint32_t * seed);

#endif

