#ifndef _XORSHIFT_H
#define _XORSHIFT_H

// Low-level ///////////////////////////////////////////////////////////////////

static inline uint32_t _xorr32 (uint32_t * x, unsigned int k) {
    return (*x) ^= (*x) >> k;
}

static inline uint32_t _xorl32 (uint32_t * x, unsigned int k) {
    return (*x) ^= (*x) << k;
}

static inline uint64_t _xorr64 (uint64_t * x, unsigned int k) {
    return (*x) ^= (*x) >> k;
}

static inline uint64_t _xorl64 (uint64_t * x, unsigned int k) {
    return (*x) ^= (*x) << k;
}

// General functions ///////////////////////////////////////////////////////////

// xorshift32 is _xor_shift32_abc(seed, 13, 17, 15)
// see the list of the (a,b,c) triplets in Marsaglia
// a, b & c < 32
static inline uint32_t _xorshift32_rlr (uint32_t * seed,
                                        unsigned int a,
                                        unsigned int b,
                                        unsigned int c) {
           _xorr32 (seed, a);
           _xorl32 (seed, b);
    return _xorr32 (seed, c);
}

static inline uint32_t _xorshift32_lrl (uint32_t * seed,
                                        unsigned int a,
                                        unsigned int b,
                                        unsigned int c) {
           _xorl32 (seed, a);
           _xorr32 (seed, b);
    return _xorl32 (seed, c);
}


#include "xobshuft.h"
#if defined XOB && XOB > 0
#endif
static inline 
uint32_t _xorshift_lrr ( uint32_t  *  seed    ,
                         unsigned int seed_len,
                         unsigned int a       ,
                         unsigned int b       ,
                         unsigned int c       ) {
    
    uint32_t seed0 = seed[0];
    unsigned int k = 0;
    while (k < seed_len - 1) {
        seed[k] = seed[k+1];
        k ++;
    }

#if !defined XOB || XOB <= 0
    _xorl32(&seed0,   a);
    _xorr32(&seed0,   b);
    _xorr32(&seed[k], c);
#else
    x0rsh1(&seed0,1,a);
    x0rsh1(&seed0,0,b);
    x0rsh1(&seed[k],0,c);
#endif
    
    seed[k] = seed[k] ^ seed0;
    return seed[k];
}


// xorshift64star is _xorshift64_abc(seed, 12, 25, 27) * 0x2545F4914F6CDD1D
// see the list of the (a,b,c) triplets in Marsaglia
// a, b & c < 64
static inline
uint64_t   _xorshift64_rlr ( uint64_t * seed,
                             unsigned int a ,
                             unsigned int b ,
                             unsigned int c ) {
           _xorr64 (seed, a);
           _xorl64 (seed, b);
    return _xorr64 (seed, c);
}



static inline 
uint64_t   _xorshift64_lrl ( uint64_t * seed,
                             unsigned int a ,
                             unsigned int b ,
                             unsigned int c ) {
           _xorl64 (seed, a);
           _xorr64 (seed, b);
    return _xorl64 (seed, c);
}

////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2004, 2006, 2008 R. P. Brent.
//  from xorgens.c version 3.05, R. P. Brent, 20080920.
#define UINT64 (sizeof(unsigned int)>>3)
#define UINT32 (1 - UINT64) 
#define wlen   (64*UINT64 + 32*UINT32)
static uint64_t _xor4096_init (uint64_t seed) {
  /* 32-bit or 64-bit integer random number generator 
     with period at least 2**4096-1.
     One random number uniformly distributed in [0..2**wlen) is returned,
     where wlen = 8*sizeof(UINT) = 32 or 64.
     R. P. Brent, 20060628.
  */

#define wlen64  64
#define r64     64
#define s64     53
#define a64     33
#define b64     26
#define c64     27
#define d64     29
#define ws64    27

#define wlen32  32
#define r32     128
#define s32     95
#define a32     17
#define b32     12
#define c32     13
#define d32     15
#define ws32    16

  static UINT w, weyl, zero = 0, x[r];
  UINT t, v;
  static int i = -1 ;              /* i < 0 indicates first call */
  int k;
  
  if ((i < 0) || (seed != zero)) { /* Initialisation necessary */
  
  /* weyl = odd approximation to 2**wlen*(3-sqrt(5))/2. */

    if (UINT32) 
      weyl = 0x61c88647;
    else 
      weyl = ((((UINT)0x61c88646)<<16)<<16) + (UINT)0x80b583eb;
                 
    v = (seed!=zero)? seed:~seed;  /* v must be nonzero */

    for (k = wlen; k > 0; k--) {   /* Avoid correlations for close seeds */
      v ^= v<<10; v ^= v>>15;      /* Recurrence has period 2**wlen-1 */ 
      v ^= v<<4;  v ^= v>>13;      /* for wlen = 32 or 64 */
      }
    for (w = v, k = 0; k < r; k++) { /* Initialise circular array */
      v ^= v<<10; v ^= v>>15; 
      v ^= v<<4;  v ^= v>>13;
      x[k] = v + (w+=weyl);                
      }
    for (i = r-1, k = 4*r; k > 0; k--) { /* Discard first 4*r results */ 
      t = x[i = (i+1)&(r-1)];   t ^= t<<a;  t ^= t>>b; 
      v = x[(i+(r-s))&(r-1)];   v ^= v<<c;  v ^= v>>d;          
      x[i] = t^v;       
      }
    }
    
  /* Apart from initialisation (above), this is the generator */

  t = x[i = (i+1)&(r-1)];            /* Assumes that r is a power of two */
  v = x[(i+(r-s))&(r-1)];            /* Index is (i-s) mod r */
  t ^= t<<a;  t ^= t>>b;             /* (I + L^a)(I + R^b) */
  v ^= v<<c;  v ^= v>>d;             /* (I + L^c)(I + R^d) */
  x[i] = (v ^= t);                   /* Update circular array */
  w += weyl;                         /* Update Weyl generator */
  return (v + (w^(w>>ws)));          /* Return combination */

#undef UINT64
#undef UINT32
#undef wlen
#undef r
#undef s
#undef a
#undef b
#undef c
#undef d
#undef ws 
  }

#endif

