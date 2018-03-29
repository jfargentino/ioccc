#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Retranscrypt from Marsaglia's paper, quite word for word */

uint32_t _xor(){
static uint32_t y=2463534242;
y^=(y<<13); y^=(y>>17); return (y^=(y<<15)); }

uint64_t _xor64bis(){
static uint64_t x=88172645463325252LL;
x^=(x<<13); x^=(x>>7); return (x^=(x<<17)); }

static unsigned int a64[] = { 10,  8,  2, 23 };
static unsigned int b64[] = { 13,  9,  7,  3 };
static unsigned int c64[] = { 10, 22,  3, 24 };
uint32_t _xor64(unsigned int a, unsigned int b, unsigned int c){
static uint32_t x=123456789,y=362436069;
uint32_t t=(x^=(x<<a)); x=y; return y=(y^(y>>c))^(t^(t>>b)); }

static unsigned int a96[] = { 10, 13,  1, 10 };
static unsigned int b96[] = {  5, 19, 17,  1 };
static unsigned int c96[] = { 26,  3,  2, 26 };
uint32_t _xor96(unsigned int a, unsigned int b, unsigned int c){
static uint32_t x=123456789,y=362436069,z=521288629;
uint32_t t=(x^=(x<<a)); x=y; y=z; return z=(z^(z>>c))^(t^(t>>b)); }

static unsigned int a128[] = {  5, 15, 23,  5 };
static unsigned int b128[] = { 14,  4, 24, 12 };
static unsigned int c128[] = {  1, 21,  3, 29 };
uint32_t _xor128(unsigned int a, unsigned int b, unsigned int c){
static uint32_t x=123456789,y=362436069,z=521288629,w=88675123;
uint32_t t=(x^=(x<<a)); x=y; y=z; z=w; return w=(w^(w>>c))^(t^(t>>b)); }

static unsigned int a160[] = { 2,  7,  1 };
static unsigned int b160[] = { 1, 13,  1 };
static unsigned int c160[] = { 4,  6, 20 };
uint32_t _xor160(unsigned int a, unsigned int b, unsigned int c){
static uint32_t x=123456789,y=362436069,z=521288629,
                      w=88675123,v=5783321;
uint32_t t=(x^=(x<<a)); x=y; y=z; z=w; w=v; return v=(v^(v>>c))^(t^(t>>b)); }

uint32_t _xor96bis(){
static uint32_t x=123456789,y=362436069,z=521288629;
uint32_t t=(x^=(x<<3))^(y^(y>>19))^(z^(z<<6));x=y;y=z;return (z=t); }

uint32_t _xor128bis(){
static uint32_t x=123456789,y=362436069,z=521288629,w=88675123;
uint32_t t=(x^=(x<<20))^(y^(y>>11))^(z^(z<<27))^(w^(w>>6));x=y;y=z;z=w;return (w=t); }

uint32_t _xorwow(){
static uint32_t x=123456789,y=362436069,z=521288629,
                      w=88675123,v=5783321,d=6615241;
uint32_t t;
t=(x^=(x>>2)); x=y; y=z; z=w; w=v; v=(v^(v<<4))^(t^(t<<1));
return (d+=362437)+v; }

uint32_t _xor128ter(){
static uint32_t x=123456789,y=362436069,z=521288629,w=88675123;
uint32_t t;
t=(x^=(x<<11));x=y;y=z;z=w; return w=(w^(w>>19))^(t^(t>>8)); }

uint32_t _mwc(){
static uint32_t x=123456789,y=362436069,z=77465321,c=13579;
uint64_t t;
t=916905990LL*x+c; x=y; y=z; c=(t>>32); return z=(t&0xffffffff); }


int main (int argc, char ** argv) {
    unsigned long long k = 0;
    if (argc > 1) {
        k = strtoull (argv[1], NULL, 0);
    }
    if (k < 1) {
        k = 1;
    }
    while (k > 0) {
        printf("%08x %016lx ", _xor(), _xor64bis());
        printf("%08x %08x ",
               _xor64(a64[0],b64[0],c64[0]),
               _xor96(a96[0],b96[0],c96[0]));
        printf("%08x %08x ",
               _xor128(a128[0],b128[0],c128[0]),
               _xor160(a160[0],b160[0],c160[0]));
        printf("%08x %08x ", _xor96bis(), _xor128bis());
        printf("%08x %08x %08x\n", _xorwow(), _xor128ter(), _mwc());
        k --;
    }
}

