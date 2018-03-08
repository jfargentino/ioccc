//////////////////////////////////////////////////////////////////////////////
/* Integer square root by Halleck's method, with Legalize's speedup */
uint64_t isqrt (uint64_t x) {
    uint64_t squaredbit = 0, remainder = 0, root = 0;
    if (x < 1) {
        return 0;
    }
    /* Load the binary constant 01 00 00 ... 00, where the number
     * of zero bits to the right of the single one bit
     * is even, and the one bit is as far left as is consistant
     * with that condition.)
     */
    //squaredbit = (~0L >> 1) & ~(~0L >> 2);
    squaredbit = (uint64_t) ( (UINT64_MAX >> 1) & ~(UINT64_MAX >> 2) );
    /* This portable load replaces the loop that used to be 
     * here, and was donated by  legalize@xmission.com 
     */
    /* Form bits of the answer. */
    remainder = x;
    root = 0;
    while (squaredbit > 0) {
        if (remainder >= (squaredbit | root)) {
            remainder -= (squaredbit | root);
            root >>= 1;
            root |= squaredbit;
        } else {
            root >>= 1;
        }
        squaredbit >>= 2; 
    }
    return root;
}

uint64_t isqrt64 (uint64_t n) {  
    uint64_t root = 0, remainder = n, place = 0x4000000000000000;  
    while (place > remainder) {
        place = place >> 2;
    }
    while (place) {  
        if (remainder >= root + place) {  
            remainder = remainder - root - place;  
            root = root + (place << 1);  
        }
        root = root >> 1;  
        place = place >> 2;  
    }
    return root;  
}

uint64_t _isqrt64(uint64_t n) {  
    uint64_t c = 0x80000000;  
    uint64_t g = 0x80000000;  
    for(;;) {
        if(g*g > n) {
            g ^= c;
        }
        c >>= 1;
        if(c == 0) {
            return g;
        }
        g |= c;
    }
}

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

//TEST_ASSERT_EQUAL_UINT32(104743, nth(10001));
// (1<<31)-1 == INT32_MAX;

bool test_isqrt (uint64_t x) {
    static uint64_t k = 0;
    uint64_t y[2];
    y[0] = isqrt64(x);
    //y[1] = floorl(sqrtl(x));
    bool res = (y[0] == y[1]);
    k ++;
if ((!res) || ((k % 1000000) == 0))
//if (!res)
fprintf (stderr, "sqrt(%lx) == %lx %c= %lu\n",
         x, y[1], res?'=':'!', y[0]);
    return res;
}

int main (void) {
    //for (uint64_t k = 0; k < UINT64_MAX; k++) {
    for (uint64_t k = UINT64_MAX; k != 0; k--) {
        test_isqrt(k);
    }
    return 0;
}

