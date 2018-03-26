#ifndef SEED_H
#define SEED_H

#include <stdint.h>

uint32_t seedx32(uint32_t * seed, int seed_len);
#define  seed32(s)   seedx32(s, 1)
#define  seed4x32(s) seedx32(s, 4)
#define  seed5x32(s) seedx32(s, 5)

uint64_t seedx64(uint64_t * seed, int seed_len);
#define  seed64(s)    seedx64(s, 1)
#define  seed2x64(s)  seedx64(s, 2)
#define  seed16x64(s) seedx64(s, 16)

#endif

