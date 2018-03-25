#ifndef XORSHIFT_H
#define XORSHIFT_H

#include <stdint.h>

/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
uint32_t xorshift32(uint32_t * seed);

/* Algorithm "xor128" from p. 5 of Marsaglia, "Xorshift RNGs" */
uint32_t xorshift128(uint32_t seed[static 4]);

/* Algorithm "xorwow" from p. 5 of Marsaglia, "Xorshift RNGs" */
uint32_t xorwow(uint32_t seed[static 5]);

/* 
 * This is a fixed-increment version of Java 8's SplittableRandom generator
 * See http://dx.doi.org/10.1145/2714064.2660195 and
 * http://docs.oracle.com/javase/8/docs/api/java/util/SplittableRandom.html
 * It is a very fast generator passing BigCrush, and it can be useful if
 * for some reason you absolutely want 64 bits of state; otherwise, we
 * rather suggest to use a xoroshiro128+ (for moderately parallel
 * computations) or xorshift1024* (for massively parallel computations)
 * generator.
 * The state can be seeded with any value.
 *
 * Written in 2015 by Sebastiano Vigna (vigna@acm.org)
 * To the extent possible under law, the author has dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 * See <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
uint64_t splitmix64 (uint64_t * seed);

uint64_t xorshift64star(uint64_t * seed);

uint64_t xorshift1024star(uint64_t seed[static 16]);

/* xorshift128plus
 *
 * Written in 2014-2016 by Sebastiano Vigna (vigna@acm.org)
 *
 * This generator has been replaced by xoroshiro128plus, which is
 * significantly faster and has better statistical properties.

 * It might be nonetheless useful for languages in which low-level rotate
 * instructions are not available. Due to the relatively short period it
 * is acceptable only for applications with a mild amount of parallelism;
 * otherwise, use a xorshift1024* generator.

 * Note that the lowest bit of this generator is an LFSR of degree 128;
 * thus, it will fail linearity tests. The next bit can be described by an
 * LFSR of degree 8256, but in the long run it will fail linearity tests,
 * too. The other bits needs a much higher degree to be represented as
 * LFSRs.

 * We suggest to use a sign test to extract a random Boolean value, and
 * right shifts to extract subsets of bits.

 * The state must be seeded so that it is not everywhere zero. If you have
 * a 64-bit seed, we suggest to seed a splitmix64 generator and use its
 * output to fill s.

 * A previous version of this generator was adding the two halves of the
 * newly computed state. This version adds the two halves of the *current*
 * state (as xoroshiro128plus does), which improves speed due to better
 * internal parallelization from the CPU. The resulting streams are off by
 * one step.
 *
 * To the extent possible under law, the author has dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * See <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
uint64_t xorshift128plus(uint64_t seed[static 2]);

/* xoroshiro128plus
 *
 * Written in 2016 by David Blackman and Sebastiano Vigna (vigna@acm.org)
 *
 * This is the successor to xorshift128plus_next. It is the fastest
 * full-period generator passing BigCrush without systematic failures,
 * but due to the relatively short period it is acceptable only for
 * applications with a mild amount of parallelism; otherwise, use a
 * xorshift1024* generator.
 *
 * Beside passing BigCrush, this generator passes the PractRand test suite
 * up to (and included) 16TB, with the exception of binary rank tests, as
 * the lowest bit of this generator is an LFSR of degree 128. The next bit
 * can be described by an LFSR of degree 8256, but in the long run it will
 * fail linearity tests, too. The other bits needs a much higher degree to
 * be represented as LFSRs.
 *
 * We suggest to use a sign test to extract a random Boolean value, and
 * right shifts to extract subsets of bits.
 *
 * Note that the generator uses a simulated rotate operation, which most C
 * compilers will turn into a single instruction. In Java, you can use
 * Long.rotateLeft(). In languages that do not make low-level rotation
 * instructions accessible xorshift128+ could be faster.
 *
 * The state must be seeded so that it is not everywhere zero. If you have
 * a 64-bit seed, we suggest to seed a splitmix64 generator and use its
 * output to fill s.
 *
 * To the extent possible under law, the author has dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * See <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
uint64_t xoroshiro128plus(uint64_t seed[static 2]);

#endif

