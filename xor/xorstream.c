#include "xorstream.h"
#include "xorshift.h"
 
/******************************************************************************/

int xorseed32_length (enum xorshift_t method) {
    switch (method) {
        case XORSHIFT32:       return 1;
        case XORSHIFT128:      return 4;
        case XORWOW:           return 5;
        case SPLITMIX64:       return 2;  // uint64_t
        case XORSHIFT64STAR:   return 2;  // uint64_t
        case XORSHIFT1024STAR: return 32; // uint64_t
        case XORSHIFT128PLUS:  return 4;  // uint64_t
        case XOROSHIRO128PLUS: return 4;  // uint64_t
        default:               return 0;
    }
    return -1;
}

int xorseed64_length (enum xorshift_t method) {
    switch (method) {
        case XORSHIFT32:       return 1; // uint32_t
        case XORSHIFT128:      return 2; // uint32_t
        case XORWOW:           return 3; // uint32_t
        case SPLITMIX64:       return 1; 
        case XORSHIFT64STAR:   return 1;
        case XORSHIFT1024STAR: return 16;
        case XORSHIFT128PLUS:  return 2;
        case XOROSHIRO128PLUS: return 2;
        default:               return 0;
    }
    return -1;
}

/******************************************************************************/

static uint32_t _u64to32 (uint64_t x) {
    union { uint32_t half[2]; uint64_t word; } y;
    y.word = x;
    // TODO other op(s)
    return y.half[0] ^ y.half[1];
}

uint32_t xorstream32(enum xorshift_t method, uint32_t * seed32) {

    uint64_t * seed64 = (uint64_t*) seed32;

    switch (method) {
        
        case XORSHIFT32:       return xorshift32(seed32);

        case XORSHIFT128:      return xorshift128(seed32);
        
        case XORWOW:           return xorwow(seed32);

        case SPLITMIX64:       return _u64to32(splitmix64(seed64));

        case XORSHIFT64STAR:   return _u64to32(xorshift64star(seed64));

        case XORSHIFT1024STAR: return _u64to32(xorshift1024star(seed64));

        case XORSHIFT128PLUS:  return _u64to32(xorshift128plus(seed64));

        case XOROSHIRO128PLUS: return _u64to32(xoroshiro128plus(seed64));

        default:               break;

    }
    return 0;
}

/******************************************************************************/

uint64_t xorstream64(enum xorshift_t method, uint64_t * seed64) {

    uint32_t * seed32 = (uint32_t*) seed64;
    union { uint32_t half[2]; uint64_t word; } x;

    switch (method) {
        
        case XORSHIFT32:
        x.half[0] = xorshift32(seed32);
        x.half[1] = xorshift32(seed32);
        return x.word;

        case XORSHIFT128:
        x.half[0] = xorshift128(seed32);
        x.half[1] = xorshift128(seed32);
        return x.word;
        
        case XORWOW:
        x.half[0] = xorwow(seed32);
        x.half[1] = xorwow(seed32);
        return x.word;

        case SPLITMIX64:       return splitmix64(seed64);

        case XORSHIFT64STAR:   return xorshift64star(seed64);

        case XORSHIFT1024STAR: return xorshift1024star(seed64);

        case XORSHIFT128PLUS:  return xorshift128plus(seed64);

        case XOROSHIRO128PLUS: return xoroshiro128plus(seed64);

        default:               break;

    }
    return 0;
}

