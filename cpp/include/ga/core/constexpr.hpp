#ifndef __GA_CORE_CONSTEXPR_HPP__
#define __GA_CORE_CONSTEXPR_HPP__

namespace ga {

	namespace detail {

		// Returns the absolute integer value.
		constexpr default_integral_t iabs(default_integral_t arg) {
			return arg >= 0 ? arg : -arg;
		}

		// Returns the greater value.
		template<typename Type>
		constexpr Type greater(Type const &lhs, Type const &rhs) {
			return lhs >= rhs ? lhs : rhs;
		}

		// Returns the smaller value;
		template<typename Type>
		constexpr Type smaller(Type const &lhs, Type const &rhs) {
			return lhs <= rhs ? lhs : rhs;
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

		// Returns the leftmost set bit in the given bitset.
		constexpr default_bitset_t _leftmost_set_bit_impl(default_bitset_t const arg, int const n) {
			return n != std::numeric_limits<default_bitset_t>::digits ? _leftmost_set_bit_impl(arg | (arg >> 1), n << 1) : ((arg >> 1) + default_bitset_t(1));
		}

		constexpr default_bitset_t leftmost_set_bit(default_bitset_t const arg) {
			return arg != default_bitset_t(0) ? _leftmost_set_bit_impl(arg, 1) : default_bitset_t(0);
		}

		// Returns the rightmost set bit in the given bitset.
		constexpr default_bitset_t rightmost_set_bit(default_bitset_t const arg) {
			return arg & -std::make_signed_t<default_bitset_t>(arg);
		}

		// Returns the index of the set bit, assuming that there is a single set bit in the bitset.
		constexpr index_t set_bit_index(default_bitset_t const arg) {
			return ones(arg - default_bitset_t(1));
		}

		// Returns the bitset of the first k-combination.
		constexpr default_bitset_t first_combination(ndims_t const k) {
			return default_bitset_t((default_bitset_t(1) << k) - 1);
		}
		
		// Returns the next combination of k elements in n, or zero when there is not more combinations within the given mask defined as (default_bitset_t(1) << n) - 1.
		constexpr default_bitset_t _next_combination_impl_b(default_bitset_t const curr, default_bitset_t const rightmost_one, default_bitset_t const temp) {
			return temp != default_bitset_t(0) ? (temp + (((temp ^ curr) / rightmost_one) >> 2)) : default_bitset_t(0);
		}

		constexpr default_bitset_t _next_combination_impl_a(default_bitset_t const curr, default_bitset_t const mask, default_bitset_t const rightmost_one) {
			return _next_combination_impl_b(curr, rightmost_one, (rightmost_one + curr) & mask);
		}

		constexpr default_bitset_t next_combination(default_bitset_t const curr, default_bitset_t const mask) {
			return _next_combination_impl_a(curr, mask, rightmost_set_bit(curr));
		}

		// Cast the given integral type to the default floating point type.
		template<typename Type, typename = std::enable_if_t<std::is_integral_v<Type> > >
		constexpr decltype(auto) cast_to_floating_point(Type const &arg) {
			return static_cast<default_floating_point_t>(arg);
		}

		template<typename Type, typename = std::enable_if_t<!std::is_integral_v<Type> > >
		constexpr decltype(auto) cast_to_floating_point(Type &&arg) {
			return std::move(arg);
		}

		// Returns the square of a given value.
		template<typename Type>
		constexpr decltype(auto) square(Type &&arg) {
			return std::move(arg) * std::move(arg);
		}

		// Returns the sum of a given values.
		template<typename Type, typename... NextTypes>
		constexpr decltype(auto) sum(Type &&arg, NextTypes &&... next_args) {
			return std::move(arg) + sum(std::move(next_args)...);
		}

		template<typename Type>
		constexpr decltype(auto) sum(Type const &&arg) {
			return std::move(arg);
		}

	}

}

#endif // __GA_CORE_CONSTEXPR_HPP__
