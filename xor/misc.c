
uint64_t gcd64 (uint64_t a, uint64_t b) {

    if (a < b) {
        // swap costs many lies of ASM
        uint64_t x = a;
        a = b;
        b = a;
    }
    
    while (a > b) {
        uint64_t r = a % b;
        a = b;
        if (r > 0) {
            b = r;
        }
    }

    return b;
}

