#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// '-'-'-'
// '/'/'/'

static int32_t negate(int32_t x) {
    return ~(x) + 1;
}

static int32_t op1 (int32_t x) {
    return x & (x - 1);
}

static int32_t op2 (int32_t x) {
    return x & (x + 1);
}

static int32_t op3 (int32_t x) {
    return x & (-x);
}

static int32_t op4 (int32_t x) {
    return (~x) & (x + 1);
}

static int32_t op5 (int32_t x) {
    return (~x) & (x - 1);
}

static int32_t op6 (int32_t x) {
    return ~(x | (-x));
}

static int32_t op7 (int32_t x) {
    return (x & (-x)) - 1;
}

static int32_t op8 (int32_t x) {
    return x ^ (x - 1);
}

static int32_t op9 (int32_t x) {
    return x | (x - 1);
}

static int32_t not (int32_t x) {
    return ~(x);
}

static int32_t or (int32_t x, int32_t y) {
    return x | y;
}

static int32_t xor (int32_t x, int32_t y) {
    return x ^ y;
}

static int32_t and (int32_t x, int32_t y) {
    return ~ ((~x) | (~y));
}

static int32_t add (int32_t x, int32_t y) {
    return xor (xor(x,y), and(x,y) << 1);
}

static void test_op2 (int32_t x, int32_t y) {
    //printf ("%08X & %08X = %08X\n", x, y, and(x, y));
    printf ("%08X + %08X = %08X\n", x, y, add(x, y));
}

static int32_t mersenne1 (int32_t k) {
    return (1 << k) - 1;
}
static int32_t mersenne2 (int32_t k) {
    return (1 << mersenne1(k)) - 1;
}
static uint64_t mersenneK (uint32_t k, uint32_t K) {
    if (K == 0) {
        return (1u << k) - 1;
    }
    return (1u << mersenneK(k, K-1)) - 1;
}

static int32_t mersenne (int32_t k) {
    return (1 << ((1 << k) - 1)) - 1;
}

static void test_op (int32_t x) {
    printf ("0x%08X:\n", x);
    printf (" 0x%08X,\n", op1(x));
    printf (" 0x%08X,\n", op2(x));
    printf (" 0x%08X,\n", op3(x));
    printf (" 0x%08X,\n", op4(x));
    printf (" 0x%08X,\n", op5(x));
    printf (" 0x%08X,\n", op6(x));
    printf (" 0x%08X,\n", op7(x));
    printf (" 0x%08X,\n", op8(x));
    printf (" 0x%08X,\n\n", op9(x));
}

int main (int argc, char ** argv) {
    for (int k = 1; k < argc; k++) {
        //printf ("%+d\n", negate(atoi(argv[k])));
        //test_op (atoi(argv[k]));
        //test_op2 (atoi(argv[k]), atoi(argv[k-1]));
        printf("M%d = %lx\n", atoi(argv[k]), mersenneK(atoi(argv[k]), 1));
    }
    return 0;
}

