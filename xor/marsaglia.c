#include <stdint.h>

#if 0

uint32_t xor(){
static uint32_t y=2463534242;
y^=(y<<13); y^=(y>>17); return (y^=(y<<15)); }

uint64_t xor64bis(){
static uint64_t x=88172645463325252LL;
x^=(x<<13); x^=(x>>7); return (x^=(x<<17)); }

static unsigned int a64[] = { 10,  8,  2, 23 };
static unsigned int b64[] = { 13,  9,  7,  3 };
static unsigned int c64[] = { 10, 22,  3, 24 };
uint32_t xor64(unsigned int a, unsigned int b, unsigned int c){
static uint32_t x=123456789,y=362436069;
uint32_t t=(x^=(x<<a)); x=y; return y=(y^(y>>c))^(t^(t>>b)); }

static unsigned int a96[] = { 10, 13,  1, 10 };
static unsigned int b96[] = {  5, 19, 17,  1 };
static unsigned int c96[] = { 26,  3,  2, 26 };
uint32_t xor96(unsigned int a, unsigned int b, unsigned int c){
static uint32_t x=123456789,y=362436069,z=521288629;
uint32_t t=(x^=(x<<a)); x=y; y=z; return z=(z^(z>>c))^(t^(t>>b)); }

static unsigned int a128[] = {  5, 15, 23,  5 };
static unsigned int b128[] = { 14,  4, 24, 12 };
static unsigned int c128[] = {  1, 21,  3, 29 };
uint32_t xor128(unsigned int a, unsigned int b, unsigned int c){
static uint32_t x=123456789,y=362436069,z=521288629,w=88675123;
uint32_t t=(x^=(x<<a)); x=y; y=z; z=w; return w=(w^(w>>c))^(t^(t>>b)); }

static unsigned int a160[] = { 2,  7,  1 };
static unsigned int b160[] = { 1, 13,  1 };
static unsigned int c160[] = { 4,  6, 20 };
uint32_t xor160(unsigned int a, unsigned int b, unsigned int c){
static uint32_t x=123456789,y=362436069,z=521288629,
                      w=88675123,v=5783321;
uint32_t t=(x^=(x<<a)); x=y; y=z; z=w; w=v; return v=(v^(v>>c))^(t^(t>>b)); }

uint32_t xor96bis(){
static uint32_t x=123456789,y=362436069,z=521288629;
uint32_t t=(x^=(x<<3))^(y^(y>>19))^(z^(z<<6));x=y;y=z;return (z=t); }

uint32_t xor128bis(){
static uint32_t x=123456789,y=362436069,z=521288629,w=88675123;
uint32_t t=(x^=(x<<20))^(y^(y>>11))^(z^(z<<27))^(w^(w>>6));x=y;y=z;z=w;return (w=t); }

uint32_t xorwow(){
static uint32_t x=123456789,y=362436069,z=521288629,
                      w=88675123,v=5783321,d=6615241;
uint32_t t;
t=(x^=(x>>2)); x=y; y=z; z=w; w=v; v=(v^(v<<4))^(t^(t<<1));
return (d+=362437)+v; }

uint32_t xor128ter(){
static uint32_t x=123456789,y=362436069,z=521288629,w=88675123;
uint32_t t;
t=(x^=(x<<11));x=y;y=z;z=w; return w=(w^(w>>19))^(t^(t>>8)); }

uint32_t mwc(){
static uint32_t x=123456789,y=362436069,z=77465321,c=13579;
uint64_t t;
t=916905990LL*x+c; x=y; y=z; c=(t>>32); return z=(t&0xffffffff); }

#else


uint32_t xor (void) {
    static uint32_t seed = 2463534242u;
    seed ^= seed << 13;
    seed ^= seed >> 17;
    return seed ^= seed << 15;
}

uint64_t xor64bis (void) {
    static uint64_t seed = 88172645463325252u;
    seed ^= seed << 13;
    seed ^= seed >>  7;
    seed ^= seed << 17;
    return seed;
}

static unsigned int a64[] = { 10,  8,  2, 23 };
static unsigned int b64[] = { 13,  9,  7,  3 };
static unsigned int c64[] = { 10, 22,  3, 24 };

uint32_t xor64 (unsigned int a, unsigned int b, unsigned int c) {
    static uint32_t seed[2] = { 123456789u, 362436069u };

    seed[0] ^= seed[0] << a; uint32_t seed0 = seed[0];
    seed[0]  = seed[1];
    seed[1]  = (seed[1]^(seed[1] >> c)) ^ (seed0^(seed0 >> b));
    
    return seed[1];
}

static unsigned int a96[] = { 10, 13,  1, 10 };
static unsigned int b96[] = {  5, 19, 17,  1 };
static unsigned int c96[] = { 26,  3,  2, 26 };

uint32_t xor96(unsigned int a, unsigned int b, unsigned int c){
    static uint32_t seed[3] = { 123456789u, 362436069u, 521288629u };

    seed[0] ^= seed[0] << a; uint32_t seed0 = seed[0];;
    seed[0]  = seed[1];
    seed[1]  = seed[2];
    seed[2]  = (seed[2]^(seed[2] >> c)) ^ (seed0^(seed0 >> b));
    
    return seed[2];
}

static unsigned int a128[] = {  5, 15, 23,  5 };
static unsigned int b128[] = { 14,  4, 24, 12 };
static unsigned int c128[] = {  1, 21,  3, 29 };

uint32_t xor128(unsigned int a, unsigned int b, unsigned int c){
    static uint32_t seed[4] = { 123456789u, 362436069u,
                                521288629u, 88675123u };
    
    seed[0] ^= seed[0] << a; uint32_t seed0 = seed[0];;
    seed[0]  = seed[1];
    seed[1]  = seed[2];
    seed[2]  = seed[3];
    seed[3]  = (seed[3]^(seed[3] >> c)) ^ (seed0^(seed0 >> b));

    return seed[3];
}

static unsigned int a160[] = { 2,  7,  1 };
static unsigned int b160[] = { 1, 13,  1 };
static unsigned int c160[] = { 4,  6, 20 };

uint32_t xor160(unsigned int a, unsigned int b, unsigned int c){
    static uint32_t seed[5] = { 123456789u, 362436069u,
                                521288629u, 88675123u, 5783321u };
    
    seed[0] ^= seed[0] << a; uint32_t seed0 = seed[0];;
    seed[0]  = seed[1];
    seed[1]  = seed[2];
    seed[2]  = seed[3];
    seed[3]  = seed[4];
    seed[4]  = (seed[4]^(seed[4] >> c)) ^ (seed0^(seed0 >> b));

    return seed[4];
}

uint32_t xor96bis(void) {
    static uint32_t seed[3] = { 123456789u, 362436069u, 521288629u };
    
    seed[0]   ^= seed[0] << 3;
    uint32_t s = seed[0] ^ (seed[1]^(seed[1] >> 19))
                         ^ (seed[2]^(seed[2] <<  6));
    seed[0]    = seed[1];
    seed[1]    = seed[2];
    seed[2]    = s;

    return seed[2];
}

uint32_t xor128bis(void) {
    static uint32_t seed[4] = { 123456789u, 362436069u,
                                521288629u, 88675123u };
    
    seed[0]   ^= seed[0] << 20;
    uint32_t s = seed[0] ^ (seed[1]^(seed[1] >> 11))
                         ^ (seed[2]^(seed[2] << 27))
                         ^ (seed[3]^(seed[3] >>  6));
    seed[0]    = seed[1];
    seed[1]    = seed[2];
    seed[2]    = seed[3];
    seed[3]    = s;

    return seed[3];
}

uint32_t xorwow (void){
    static uint32_t seed[5] = { 123456789u, 362436069u,
                                521288629u, 88675123u, 5783321u };
    static uint32_t d = 6615241u;

    seed[0] ^= seed[0] >> 2; uint32_t seed0 = seed[0];;
    seed[0]  = seed[1];
    seed[1]  = seed[2];
    seed[2]  = seed[3];
    seed[3]  = seed[4];
    seed[4]  = (seed[4]^(seed[4] << 4)) ^ (seed0^(seed0 << 1));
    
    d += 362437u;
    return d + seed[4]; 
}

uint32_t xor128ter (void) {
    static uint32_t seed[4] = { 123456789u, 362436069u,
                                521288629u, 88675123u  };

    seed[0] ^= seed[0] << 11; uint32_t seed0 = seed[0];
    seed[0]  = seed[1];
    seed[1]  = seed[2];
    seed[2]  = seed[3];
    seed[3]  = (seed[3]^(seed[3] >> 19)) ^ (seed0^(seed0 >> 8));
    
    return seed[3];
}

uint32_t mwc (void) {

    static uint32_t seed[3] = { 123456789u, 362436069u, 77465321u };
    static uint32_t carry = 13579u;
    
    uint64_t s = 916905990ll * seed[0] + carry;
    seed[0]    = seed[1];
    seed[1]    = seed[2];
    carry      = s >> 32;
    seed[2]    = s & 0xffffffff;
    
    return seed[2];
}

#endif

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char ** argv) {
    int k = 0;
    if (argc > 1) {
        k = atoi (argv[1]);
    }
    if (k < 1) {
        k = 1;
    }
    while (k > 0) {
        printf("%8x %16lx ", xor(), xor64bis());
        printf("%8x %8x ",
               xor64(a64[0],b64[0],c64[0]),
               xor96(a96[0],b96[0],c96[0]));
        printf("%8x %8x ",
               xor128(a128[0],b128[0],c128[0]),
               xor160(a160[0],b160[0],c160[0]));
        printf("%8x %8x ", xor96bis(), xor128bis());
        printf("%8x %8x %8x\n", xorwow(), xor128ter(),mwc());
        k --;
    }
}

