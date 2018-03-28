#ifndef XORSHIFT_H
#define XORSHIFT_H

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////////
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

/*
 * This generator is a variant of xorshift128+ for dynamic languages, such
 * as Erlang, that can use only 58 bits of a 64-bit integer. Only the lower
 * 58 bits of each state word are valid (the upper six are zeroes).
 * 
 * This generator passes BigCrush without systematic failures, but due to
 * the relatively short period it is acceptable only for applications with
 * a mild amount of parallelism; otherwise, use a xorshift1024* generator.
 *
 * The state must be seeded so that the lower 58 bits of s[ 0 ] and s[ 1 ]
 * are not all zeroes. If you have a nonzero 64-bit seed, we suggest to
 * pass it twice through MurmurHash3's avalanching function and take the
 * lower 58 bits, taking care that they are not all zeroes (you can apply
 * the avalanching function again if this happens).
 *
 * Written in 2014 by Sebastiano Vigna (vigna@acm.org) and 
 * Kenji Rikitake (kenji.rikitake@acm.org).
 *
 * To the extent possible under law, the author has dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * See <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
uint64_t xorshift116plus(int64_t seed[static 2]);

/*
 * This is probably the oldest known PRNG: a Lehmer generator (a.k.a.
 * multiplicative LCG). It simply multiplies the current state by a
 * constant. It is a very fast generator passing BigCrush, albeit slower
 * than xoroshiro128+, and with a smaller period (2^126). It needs support
 * for 128-bit integers from the compiler. The less significant bit,
 * moreover, has shorter period 2^62, the next bit 2^63, etc.
 *
 * Note, however, that as 128-bit processor and compilers will become
 * common this generator will likely become extremely fast. 
 *
 * The multiplier has been taken from
 *
 * Pierre L'Ecuyer. Tables of linear congruential generators of different
 * sizes and good lattice structure. Math. Comput. 68, 225 (1999), 249-260.
 *
 * IMPORTANT: On big-endian architectures, the role of s[0] and s[1] must
 * be exchanged.
 *
 * The state must be seeded with two 64-bit values, among which s[0] MUST be
 * odd.
 */
uint64_t lehmer128(uint64_t seed[static 2]);

/* xorshift128plus
 *
 * Written in 2014-2016 by Sebastiano Vigna (vigna@acm.org)
 *
 * This generator has been replaced by xoroshiro128plus, which is
 * significantly faster and has better statistical properties.
 *
 * It might be nonetheless useful for languages in which low-level rotate
 * instructions are not available. Due to the relatively short period it
 * is acceptable only for applications with a mild amount of parallelism;
 * otherwise, use a xorshift1024* generator.
 *
 * Note that the lowest bit of this generator is an LFSR of degree 128;
 * thus, it will fail linearity tests. The next bit can be described by an
 * LFSR of degree 8256, but in the long run it will fail linearity tests,
 * too. The other bits needs a much higher degree to be represented as
 * LFSRs.
 *
 * We suggest to use a sign test to extract a random Boolean value, and
 * right shifts to extract subsets of bits.
 *
 * The state must be seeded so that it is not everywhere zero. If you have
 * a 64-bit seed, we suggest to seed a splitmix64 generator and use its
 * output to fill s. Or to pass it twice through MurmurHash3's avalanching
 * function.
 *
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

/*
 * This is a fast, high-quality generator. If 1024 bits of state are too
 * much, try a xorshift128+ or xoroshiro128+ generator.
 *
 * Note that the two lowest bits of this generator are LFSRs of degree
 * 1024, and thus will fail binary rank tests. The other bits needs a much
 * higher degree to be represented as LFSRs.
 *
 * We suggest to use a sign test to extract a random Boolean value, and
 * right shifts to extract subsets of bits.
 *
 * The state must be seeded so that it is not everywhere zero. If you have
 * a 64-bit seed, we suggest to seed a splitmix64 or xorshift64* generator and
 * use its output to fill s.
 *
 * NOTE: as of 2017-10-08, this generator has a different multiplier (a
 * fixed-point representation of the golden ratio), which eliminates
 * linear dependencies from one of the lowest bits. The previous
 * multiplier was 1181783497276652981 (M_8 in the paper). If you need to
 * tell apart the two generators, you can refer to this generator as
 * xorshift1024*f and to the previous one as xorshift1024*M_8.
 *
 * Written in 2014 by Sebastiano Vigna (vigna@acm.org)
 *
 * To the extent possible under law, the author has dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * See <http://creativecommons.org/publicdomain/zero/1.0/>. 
 */
uint64_t xorshift1024star(uint64_t seed[static 16]);

/*
 * While you can use this generator, we rather suggest to use a
 * xorshift1024* generator.
 *
 * The state must be seeded so that it is not everywhere zero. If you have
 * a 64-bit seed,  we suggest to seed a xorshift64* generator and use its
 * output to fill s.
 *
 *  Written in 2014 by Sebastiano Vigna (vigna@acm.org)
 *
 * To the extent possible under law, the author has dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * See <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
uint64_t xorshift4096star(uint64_t seed[static 64]);

#endif

