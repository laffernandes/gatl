#ifndef __GA_FUTURE_CONSTEXPR_HPP__
#define __GA_FUTURE_CONSTEXPR_HPP__

namespace future {

	namespace detail {

		// Returns the absolute integer value.
		constexpr default_integral_t absolute(default_integral_t a) {
			return a >= 0 ? a : -a;
		}

		// Returns the greatest common divisor of two integer values.
		constexpr default_integral_t gcd(default_integral_t a, default_integral_t b) {
			return b == 0 ? a : gcd(b, a % b);
		}

		// Returns the sign of the given integer value.
		constexpr default_integral_t sign(default_integral_t a) {
			return a > 0 ? 1 : (a < 0 ? -1 : 0);
		}

		// Returns the A raised to the power of B, where A is an integer values and B is non-negative.
		constexpr default_integral_t ipow(default_integral_t base, default_integral_t exponent) {
			return exponent == 1 ? base : (exponent == 0 ? 1 : (ipow(base, exponent >> 1) * ipow(base, exponent >> 1) * ipow(base, exponent % 2)));
		}

		// Returns the square root of the given integer value (isqrt(A) = B, for A >= 1) when it is possible to have an integer value as result.
		constexpr default_integral_t _isqrt_impl(default_integral_t sq, default_integral_t dlt, default_integral_t a) {
			return sq <= a ? _isqrt_impl(sq + dlt, dlt + 2, a) : (dlt >> 1) - 1;
		}

		constexpr default_integral_t isqrt(default_integral_t a) {
			return _isqrt_impl(1, 3, a);
		}

		// Returns the number of 1 bits in the given bitset.
		template<std::uint64_t Bitset>
		struct ones {
		private:

			constexpr static auto a = (Bitset & 0x5555555555555555ull) + ((Bitset >> 1) & 0x5555555555555555ull);
			constexpr static auto b = (a & 0x3333333333333333ull) + ((a >> 2) & 0x3333333333333333ull);
			constexpr static auto c = (b & 0x0F0F0F0F0F0F0F0Full) + ((b >> 4) & 0x0F0F0F0F0F0F0F0Full);

		public:

			constexpr static auto value = ((c * 0x0101010101010101ull) >> 56);
		};

		template<default_bitset_t Bitset>
		constexpr int ones_v = ones<Bitset>::value;

	}

}

#endif // __GA_FUTURE_CONSTEXPR_HPP__
