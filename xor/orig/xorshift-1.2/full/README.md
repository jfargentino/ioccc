Computing full-period generators
================================

This directory contains all code and scripts that is necessary to compute
full-period generators for a number of combination of shifts and bits of
state. Other combinations can be easily accommodated.

To use the software, you must have [Ruby](https://www.ruby-lang.org/) and
[Fermat](http://home.bway.net/lewis/) installed. In particular, Fermat's
binary must be called `fermat`.

The scripts controlling the computation are in the `common` directory. The
other directories describe the type of generator: the first number is the
number of bits of state, the second string denotes which kind of basic
transformation is used, the third number the number of bits used by the
basic transformation. Thus, `128shift64` contains code computing the
parameters of full-period `xorshift` generators using 64-bit shifts and
128 bits of state, whereas `512simd256` contains code for `xorsimd`
generators using AVX2 256-bit operations and 512 bits of state.

To compute parameters for some full-period generators, go into the
corresponding directory and execute

	../common/testirred.sh THREADS
	../common/testprim.sh
	../common/printprim.sh >prim.txt

where `THREADS` is the degree of parallelism. If you perform multiple
computations, be sure to start from a clean slate (i.e., clean up old
generated files). At the end, the file `prim.txt` (which is already
available in each directory for your convenience) will contain a list of
parameters inducing a primitive polynomial (i.e., a full-period generator)
and its associated weight. For the exact meaning of the parameters, please
refer to my papers on the subject.

Note that the `testirred.f` file contains just some setup code for the
computation of irreducible polynomials, whereas the file `testprim.f`
has been generated using the Java class `XorShiftPoly` and contains code
checking primitivity by exponentiation to cofactors.

seba (<mailto:sebastiano.vigna@unimi.it>)
