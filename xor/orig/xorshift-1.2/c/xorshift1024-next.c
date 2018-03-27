/*

This code implements multiplication by the matrix underlying a xorshift1024 generator.
It assumes that the state has been declared as

uint64_t s[16];
int p;

The parameters that must be defined are:

- A: the first shift (left).
- B: the second shift (right).
- C: the third shift (right).

*/

const uint64_t s0 = s[p];
uint64_t s1 = s[p = (p + 1) & 15];
s1 ^= s1 << A;
s[p] = s1 ^ s0 ^ (s1 >> B) ^ (s0 >> C);
