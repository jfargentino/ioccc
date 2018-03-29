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

int
z
(
int
*
x
,
int 
w
)
{
static
int 
y 
; 
y 
=
w
?
y
?
y
: 
*
x
:
w
;
return
w 
? 
z 
(
*
x
<<=
1
,
w
--
)
:
*
x
^
y
;
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


static inline uint32_t _xorshift_lrr ( uint32_t * seed,
                                       unsigned int seed_len,
                                       unsigned int a,
                                       unsigned int b,
                                       unsigned int c ) {
    uint32_t seed0 = seed[0];
    unsigned int k = 0;
    while (k < seed_len - 1) {
        seed[k] = seed[k+1];
        k ++;
    }
    _xorl32(&seed0,   a);
    _xorr32(&seed0,   b);
    _xorr32(&seed[k], c);
    seed[k] = seed[k] ^ seed0;
    return seed[k];
}

                           static
                           inline
                         uint32_t
                        _xorshift_                    (
                         uint32_t            * seed           ,
                         unsigned  int const * abc            ,
                         unsigned  int         len    )         {
                         uint32_t seed_k_ =          0        ;
                         unsigned  int k  =          0        ;
                          while (      k  <    len - 1)         {
                                  seed_k_ ^=     k % 2  
                                ? seed[k] ^ seed[k] >> abc[k] 
                                : seed[k] ^ seed[k] << abc[k] ;
                                  seed[k] = seed[   ++     k] ; }
                                  seed_k_ ^=     k % 2 
                                ? seed[k] ^ seed[k] >> abc[k] 
                                : seed[k] ^ seed[k] << abc[k] ;
                                  seed[k] = seed_k_;
                                  return    seed[k];            }

// xorshift64star is _xorshift64_abc(seed, 12, 25, 27) * 0x2545F4914F6CDD1D
// see the list of the (a,b,c) triplets in Marsaglia
// a, b & c < 64
                                                          static inline uint64_t
                   _xorshift64_rlr ( uint64_t * seed,
                                     unsigned int a ,
                                     unsigned int b ,
                                     unsigned int c ) {
           _xorr64 (seed, a);
           _xorl64 (seed, b);
    return _xorr64 (seed, c);                         }



static inline uint64_t _xorshift64_lrl (uint64_t * seed,
                                        unsigned int a,
                                        unsigned int b,
                                        unsigned int c) {
           _xorl64 (seed, a);
           _xorr64 (seed, b);
    return _xorl64 (seed, c);
}

#endif

