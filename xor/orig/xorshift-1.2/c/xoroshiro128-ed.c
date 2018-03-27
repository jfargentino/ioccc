/*		 
 * Copyright (C) 2014-2016 Sebastiano Vigna 
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 3 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <immintrin.h>
#include <sstream>
#include <cstring>
#include <cassert>
#include <stdint.h>
#include <inttypes.h>
#include <memory>
using std::shared_ptr;
#include <MTToolBox/AbstractGenerator.hpp>
#include <MTToolBox/AlgorithmEquidistribution.hpp>
#include "reverse.h"

using namespace MTToolBox;
using namespace std;


class Xoroshiro128 : public EquidistributionCalculatable<uint64_t> {
	public:
		Xoroshiro128(int a, int b, int c, uint64_t s) {
			this->a = a;
			this->b = b;
			this->c = c;
			seed(s);
		}

    	Xoroshiro128(const Xoroshiro128& src) : EquidistributionCalculatable<uint64_t>() {
			a = src.a;
			b = src.b;
			c = src.c;
			memcpy(s, src.s, sizeof s);
		}

		static inline uint64_t rotl(const uint64_t x, int k) {
			return (x << k) | (x >> (64 - k));
		}

		uint64_t generate() {
			const uint64_t s0 = s[0];
			uint64_t s1 = s[1];
			s1 ^= s0;
			s[0] = rotl(s0, a) ^ s1 ^ (s1 << b);
			s[1] = rotl(s1, c);
			return s[0];
		}
		
		Xoroshiro128 * clone() const {
			return new Xoroshiro128(*this);
		}

		uint64_t generate(int outBitLen) {
			return generate() & -1LL << (64 - outBitLen);
		}

		void seed(uint64_t value) {
			((uint64_t *)s)[0] = value;
			for(int i = 1; i < 2; i++) ((uint64_t *)s)[i] =  (6364136223846793005ULL * (((uint64_t *)s)[i - 1] ^ (((uint64_t *)s)[i - 1] >> 62)) + value);
		}

		int bitSize() const {
			return 128;
		}

		void add(EquidistributionCalculatable<uint64_t>& other) {
			Xoroshiro128* that = dynamic_cast<Xoroshiro128 *>(&other);
			if(that == 0) throw std::invalid_argument("the adder should have the same type as the addee.");

			for(int i = 0; i < 2; i++) ((uint64_t *)s)[i] ^= ((uint64_t *)that->s)[i];
		}
		
		void setZero() {
			memset(s, 0, sizeof s);
		}
		
		bool isZero() const {
			for(int i = 0; i < 2; i++) if (((uint64_t *)s)[i]) return false;
			return true;
		}

		void setUpParam(AbstractGenerator<uint64_t>& ab) {
			assert(false);
		}

		const std::string getHeaderString() {
			return "";
		}

		const std::string getParamString() {
			return "";
		}
	private:
		uint64_t s[2];
		int a, b, c;
};

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "%s A B C\n", argv[0]);
		exit(1);
	}

	Xoroshiro128 Xoroshiro128(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), 1);
	AlgorithmEquidistribution<uint64_t> eq(Xoroshiro128, 64);
	int veq[64];
	const int delta = eq.get_all_equidist(veq);
	const int bitSize = Xoroshiro128.bitSize();
	for (int i = 0; i < 64; i++) cout << "k("<< dec << setw(2) << (i + 1) << "):" << setw(5) << veq[i] << "  d(" << setw(2) << (i + 1) << "):" << setw(5) << (bitSize / (i + 1)) - veq[i] << endl;
	cout << "delta:" << delta << endl;
	return 0;
}
