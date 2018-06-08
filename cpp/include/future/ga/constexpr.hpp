#ifndef __FUTURE_GA_CONSTEXPR_HPP__
#define __FUTURE_GA_CONSTEXPR_HPP__

namespace ga {

	namespace detail {

		// Returns the absolute integer value.
		constexpr default_integral_t absolute(default_integral_t arg) {
			return arg >= 0 ? arg : -arg;
		}

		// Returns the greater value.
		template<class Type>
		constexpr Type greater(Type const &lhs, Type const &rhs) {
			return lhs >= rhs ? lhs : rhs;
		}

		// Returns the greatest common divisor of two integer values.
		constexpr default_integral_t gcd(default_integral_t lhs, default_integral_t rhs) {
			return rhs == 0 ? lhs : gcd(rhs, lhs % rhs);
		}

		// Returns the sign of the given integer value.
		constexpr default_integral_t sign(default_integral_t arg) {
			return arg > 0 ? 1 : (arg < 0 ? -1 : 0);
		}

		// Returns the A raised to the power of B, where A is an integer values and B is non-negative.
		constexpr default_integral_t ipow(default_integral_t base, default_integral_t exponent) {
			return exponent == 1 ? base : (exponent == 0 ? 1 : (ipow(base, exponent >> 1) * ipow(base, exponent >> 1) * ipow(base, exponent % 2)));
		}

		// Returns the square root of the given integer value (isqrt(A) = B, for A >= 1) when it is possible to have an integer value as result.
		constexpr default_integral_t _isqrt_impl(default_integral_t sq, default_integral_t dlt, default_integral_t a) {
			return sq <= a ? _isqrt_impl(sq + dlt, dlt + 2, a) : (dlt >> 1) - 1;
		}

		constexpr default_integral_t isqrt(default_integral_t arg) {
			return _isqrt_impl(1, 3, arg);
		}

		// Returns the number of 1 bits in the given bitset.
		constexpr std::uint64_t _ones_impl_a(std::uint64_t const bitset) {
			return (bitset & 0x5555555555555555ull) + ((bitset >> 1) & 0x5555555555555555ull);
		}

		constexpr std::uint64_t _ones_impl_b(std::uint64_t const a) {
			return (a & 0x3333333333333333ull) + ((a >> 2) & 0x3333333333333333ull);
		}
		
		constexpr std::uint64_t _ones_impl_c(std::uint64_t const b) {
			return (b & 0x0F0F0F0F0F0F0F0Full) + ((b >> 4) & 0x0F0F0F0F0F0F0F0Full);
		}
		
		constexpr default_integral_t ones(default_bitset_t const arg) {
			return static_cast<default_integral_t>((_ones_impl_c(_ones_impl_b(_ones_impl_a(arg))) * 0x0101010101010101ull) >> 56);
		}

		// Returns the number of swaps performed to merge two basis blades expanded by orthogonal basis vectors and make a basis blade in canonical order.
		constexpr default_integral_t swaps_count(default_bitset_t const lhs, default_bitset_t const rhs) {
			return lhs != default_bitset_t(0) ? (ones(lhs & rhs) + swaps_count((lhs >> 1), rhs)) : 0;
		}

		// Cast the given integral type to the default floating point type.
		template<class Type, class = std::enable_if_t<std::is_integral_v<Type> > >
		constexpr decltype(auto) cast_to_floating_point(Type const &arg) {
			return static_cast<default_floating_point_t>(arg);
		}

		template<class Type, class = std::enable_if_t<!std::is_integral_v<Type> > >
		constexpr decltype(auto) cast_to_floating_point(Type &&arg) {
			return std::move(arg);
		}

		// Returns the square of a given value.
		template<class Type>
		constexpr decltype(auto) square(Type const &arg) {
			return arg * arg;
		}

	}

}

#endif // __FUTURE_GA_CONSTEXPR_HPP__
