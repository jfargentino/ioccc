/*

This code implements multiplication by the matrix underlying a xoroshiro128 generator.
It assumes that the state has been declared as

uint64_t s[2];

The parameters that must be defined are:

- A: the first rotation (left).
- B: the shift (left).
- C: the second rotation (left).

*/

const uint64_t s0 = s[0];
uint64_t s1 = s[1];
const uint64_t result = s0 + s1;

s1 ^= s0;
s[0] = rotl(s0, A) ^ s1 ^ (s1 << B);
s[1] = rotl(s1, C);
