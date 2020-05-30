/* Copyright (C) Leandro Augusto Frata Fernandes
 * 
 * author     : Fernandes, Leandro A. F.
 * e-mail     : laffernandes@ic.uff.br
 * home page  : http://www.ic.uff.br/~laffernandes
 * repository : https://github.com/laffernandes/gatl.git
 * 
 * This file is part of The Geometric Algebra Template Library (GATL).
 * 
 * GATL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * GATL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GATL. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __GA_CORE_CONSTEXPR_HPP__
#define __GA_CORE_CONSTEXPR_HPP__

namespace ga {

    namespace detail {

        // Returns the absolute integer value.
        GA_ALWAYS_INLINE constexpr default_integral_t iabs(default_integral_t arg) GA_NOEXCEPT {
            return arg >= 0 ? arg : -arg;
        }

        // Returns the greatest common divisor of two integer values.
        GA_ALWAYS_INLINE constexpr default_integral_t gcd(default_integral_t lhs, default_integral_t rhs) GA_NOEXCEPT {
            return rhs == 0 ? lhs : gcd(rhs, lhs % rhs);
        }

        // Returns the sign of the given integer value.
        GA_ALWAYS_INLINE constexpr default_integral_t sign(default_integral_t arg) GA_NOEXCEPT {
            return arg > 0 ? 1 : (arg < 0 ? -1 : 0);
        }

        // Returns the A raised to the power of B, where A is an integer values and B is non-negative.
        GA_ALWAYS_INLINE constexpr default_integral_t ipow(default_integral_t base, default_integral_t exponent) GA_NOEXCEPT {
            return exponent == 1 ? base : (exponent == 0 ? 1 : (ipow(base, exponent >> 1) * ipow(base, exponent >> 1) * ipow(base, exponent % 2)));
        }

        // Returns the square root of the given integer value (isqrt(A) = B, for A >= 1) when it is possible to have an integer value as result.
        GA_ALWAYS_INLINE constexpr default_integral_t _isqrt_impl(default_integral_t sq, default_integral_t dlt, default_integral_t a) GA_NOEXCEPT {
            return sq <= a ? _isqrt_impl(sq + dlt, dlt + 2, a) : (dlt >> 1) - 1;
        }

        GA_ALWAYS_INLINE constexpr default_integral_t isqrt(default_integral_t arg) GA_NOEXCEPT {
            return _isqrt_impl(1, 3, arg);
        }

        // Returns the number of 1 bits in the given bitset.
        GA_ALWAYS_INLINE constexpr std::uint64_t _ones_impl_a(std::uint64_t const bitset) GA_NOEXCEPT {
            return (bitset & 0x5555555555555555ull) + ((bitset >> 1) & 0x5555555555555555ull);
        }

        GA_ALWAYS_INLINE constexpr std::uint64_t _ones_impl_b(std::uint64_t const a) GA_NOEXCEPT {
            return (a & 0x3333333333333333ull) + ((a >> 2) & 0x3333333333333333ull);
        }
        
        GA_ALWAYS_INLINE constexpr std::uint64_t _ones_impl_c(std::uint64_t const b) GA_NOEXCEPT {
            return (b & 0x0F0F0F0F0F0F0F0Full) + ((b >> 4) & 0x0F0F0F0F0F0F0F0Full);
        }
        
        GA_ALWAYS_INLINE constexpr default_integral_t ones(bitset_t const arg) GA_NOEXCEPT {
            return static_cast<default_integral_t>((_ones_impl_c(_ones_impl_b(_ones_impl_a(arg))) * 0x0101010101010101ull) >> 56);
        }

        // Returns the number of swaps performed to merge two basis blades expanded by orthogonal basis vectors and make a basis blade in canonical order.
        GA_ALWAYS_INLINE constexpr default_integral_t swaps_count(bitset_t const lhs, bitset_t const rhs) GA_NOEXCEPT {
            return lhs != bitset_t(0) ? (ones(lhs & rhs) + swaps_count((lhs >> 1), rhs)) : 0;
        }

        // Returns the leftmost set bit in the given bitset.
        GA_ALWAYS_INLINE constexpr bitset_t _leftmost_set_bit_impl(bitset_t const arg, int const n) GA_NOEXCEPT {
            return n != std::numeric_limits<bitset_t>::digits ? _leftmost_set_bit_impl(arg | (arg >> 1), n << 1) : ((arg >> 1) + bitset_t(1));
        }

        GA_ALWAYS_INLINE constexpr bitset_t leftmost_set_bit(bitset_t const arg) GA_NOEXCEPT {
            return arg != bitset_t(0) ? _leftmost_set_bit_impl(arg, 1) : bitset_t(0);
        }

        // Returns the rightmost set bit in the given bitset.
        GA_ALWAYS_INLINE constexpr bitset_t rightmost_set_bit(bitset_t const arg) GA_NOEXCEPT {
            return arg & -std::make_signed_t<bitset_t>(arg);
        }

        // Returns the index of the set bit, assuming that there is a single set bit in the bitset.
        GA_ALWAYS_INLINE constexpr index_t set_bit_index(bitset_t const arg) GA_NOEXCEPT {
            return ones(arg - bitset_t(1));
        }

        // Returns the bitset of the first k-combination.
        GA_ALWAYS_INLINE constexpr bitset_t first_combination(ndims_t const k) GA_NOEXCEPT {
            return bitset_t((bitset_t(1) << k) - 1);
        }
        
        // Returns the next combination of k elements in n, or zero when there is not more combinations within the given mask defined as (bitset_t(1) << n) - 1.
        GA_ALWAYS_INLINE constexpr bitset_t _next_combination_impl_b(bitset_t const curr, bitset_t const rightmost_one, bitset_t const temp) GA_NOEXCEPT {
            return temp != bitset_t(0) ? (temp + (((temp ^ curr) / rightmost_one) >> 2)) : bitset_t(0);
        }

        GA_ALWAYS_INLINE constexpr bitset_t _next_combination_impl_a(bitset_t const curr, bitset_t const mask, bitset_t const rightmost_one) GA_NOEXCEPT {
            return _next_combination_impl_b(curr, rightmost_one, (rightmost_one + curr) & mask);
        }

        GA_ALWAYS_INLINE constexpr bitset_t next_combination(bitset_t const curr, bitset_t const mask) GA_NOEXCEPT {
            return _next_combination_impl_a(curr, mask, rightmost_set_bit(curr));
        }

        // Cast the given integral type to the default floating point type.
        template<typename Type, std::enable_if_t<std::is_integral_v<Type>, int> = 0>
        GA_ALWAYS_INLINE constexpr decltype(auto) cast_to_floating_point(Type const &arg) GA_NOEXCEPT {
            return static_cast<default_floating_point_t>(arg);
        }

        template<typename Type, std::enable_if_t<!std::is_integral_v<Type>, int> = 0>
        GA_ALWAYS_INLINE constexpr decltype(auto) cast_to_floating_point(Type &&arg) GA_NOEXCEPT {
            return std::move(arg);
        }

        // Returns the square of a given value.
        template<typename Type>
        GA_ALWAYS_INLINE constexpr decltype(auto) square(Type &&arg) GA_NOEXCEPT {
            return std::move(arg) * std::move(arg);
        }

        // Returns the cube of a given value.
        template<typename Type>
        GA_ALWAYS_INLINE constexpr decltype(auto) cube(Type &&arg) GA_NOEXCEPT {
            return std::move(arg) * std::move(arg) * std::move(arg);
        }

        // Safe right-shifting operation.
        template<typename LeftType, typename RightType>
        GA_ALWAYS_INLINE constexpr LeftType safe_rshift(LeftType const lhs, RightType const rhs) GA_NOEXCEPT {
            return (sizeof(LeftType) * 8) > rhs ? lhs >> rhs : LeftType(0);
        }

    }

}

#endif // __GA_CORE_CONSTEXPR_HPP__
