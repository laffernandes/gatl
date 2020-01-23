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

#ifndef __GA_TEST_HPP__
#define __GA_TEST_HPP__

#include <gatl/ga.hpp>
#include <gtest/gtest.h>

//TODO Missing testing cases: rp, *, ^, conjugation, involution, reversion, math

template<ga::ndims_t N>
using runtime_entry_t = ga::scaled_basis_blade_t<double, 0, N>;

template<ga::ndims_t N>
using table_entry_t = ga::scaled_basis_blade_t<double, 0, N>;

template<typename CoefficientType, typename Coefficient, ga::bitset_t BasisBlade>
ga::bitset_t get_bitset(ga::clifford_expression<CoefficientType, ga::detail::component<Coefficient, ga::detail::constant_basis_blade<BasisBlade> > > const &) {
    return BasisBlade;
}

template<typename CoefficientType, typename Coefficient, ga::bitset_t PossibleGrades>
ga::bitset_t get_bitset(ga::clifford_expression<CoefficientType, ga::detail::component<Coefficient, ga::detail::dynamic_basis_blade<PossibleGrades, ga::detail::stored_bitset> > > const &arg) {
    return *arg.bitsets().begin();
}

template<typename Product, typename Truth, typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression>
bool check(Product prod, Truth truth, ga::clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, ga::clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
    auto const prod_result = prod(lhs, rhs);
    auto const truth_result = truth(lhs, rhs);
    auto const diff_result = prod_result - truth_result;

    if (is_zero(diff_result)) {
        return true;
    }

    std::clog << "-- FAILURE --" << std::endl;
    std::clog << "lhs = " << lhs << std::endl;
    std::clog << "rhs = " << rhs << std::endl;
    std::clog << "prod(lhs, rhs) = " << prod_result << std::endl;
    std::clog << "truth(lhs, rhs) = " << truth_result << std::endl;
    std::clog << "diff = " << diff_result << std::endl;
    return false;
}

template<ga::ndims_t N, ga::bitset_t LeftBitset, ga::bitset_t RightBitset = ga::detail::first_combination(N)>
struct _compile_time_vs_compile_time_iterate_right {
    template<typename Product, typename Truth>
    GA_ALWAYS_INLINE static bool run(Product prod, Truth truth) {
        ga::clifford_expression<ga::default_integral_t, ga::detail::component<ga::detail::constant_value<1>, ga::detail::constant_basis_blade<LeftBitset> > > lhs;
        ga::clifford_expression<ga::default_integral_t, ga::detail::component<ga::detail::constant_value<1>, ga::detail::constant_basis_blade<RightBitset> > > rhs;
        return _compile_time_vs_compile_time_iterate_right<N, LeftBitset, RightBitset - 1>::run(prod, truth)
            && check(prod, truth, lhs, rhs);
    }
};

template<ga::ndims_t N, ga::bitset_t LeftBitset>
struct _compile_time_vs_compile_time_iterate_right<N, LeftBitset, ga::bitset_t(0)> {
    template<typename Product, typename Truth>
    GA_ALWAYS_INLINE static bool run(Product prod, Truth truth) {
        ga::clifford_expression<ga::default_integral_t, ga::detail::component<ga::detail::constant_value<1>, ga::detail::constant_basis_blade<LeftBitset> > > lhs;
        ga::clifford_expression<ga::default_integral_t, ga::detail::component<ga::detail::constant_value<1>, ga::detail::constant_basis_blade<ga::bitset_t(0)> > > rhs;
        return check(prod, truth, lhs, rhs);
    }
};

template<ga::ndims_t N, ga::bitset_t LeftBitset = ga::detail::first_combination(N)>
struct _compile_time_vs_compile_time_iterate_left {
    template<typename Product, typename Truth>
    GA_ALWAYS_INLINE static bool run(Product prod, Truth truth) {
        return _compile_time_vs_compile_time_iterate_left<N, LeftBitset - 1>::run(prod, truth)
            && _compile_time_vs_compile_time_iterate_right<N, LeftBitset>::run(prod, truth);
    }
};

template<ga::ndims_t N>
struct _compile_time_vs_compile_time_iterate_left<N, ga::bitset_t(0)> {
    template<typename Product, typename Truth>
    GA_ALWAYS_INLINE static bool run(Product prod, Truth const &truth) {
        return _compile_time_vs_compile_time_iterate_right<N, ga::bitset_t(0)>::run(prod, truth);
    }
};

template<ga::ndims_t N, typename Product, typename Truth>
bool compile_time_vs_compile_time(Product prod, Truth truth) {
    return _compile_time_vs_compile_time_iterate_left<N>::run(prod, truth);
}

template<ga::ndims_t N, ga::bitset_t LeftBitset = ga::detail::first_combination(N)>
struct _compile_time_vs_runtime_iterate_left {
    template<typename Product, typename Truth>
    GA_ALWAYS_INLINE static bool run(Product prod, Truth truth, runtime_entry_t<N> const &rhs) {
        ga::clifford_expression<ga::default_integral_t, ga::detail::component<ga::detail::constant_value<1>, ga::detail::constant_basis_blade<LeftBitset> > > lhs;
        return _compile_time_vs_runtime_iterate_left<N, LeftBitset - 1>::run(prod, truth, rhs)
            && check(prod, truth, lhs, rhs);
    }
};

template<ga::ndims_t N>
struct _compile_time_vs_runtime_iterate_left<N, ga::bitset_t(0)> {
    template<typename Product, typename Truth>
    GA_ALWAYS_INLINE static bool run(Product prod, Truth const &truth, runtime_entry_t<N> const &rhs) {
        ga::clifford_expression<ga::default_integral_t, ga::detail::component<ga::detail::constant_value<1>, ga::detail::constant_basis_blade<ga::bitset_t(0)> > > lhs;
        return check(prod, truth, lhs, rhs);
    }
};

template<ga::ndims_t N, typename Product, typename Truth>
bool compile_time_vs_runtime(Product prod, Truth truth) {
    constexpr ga::bitset_t end_bitset = ga::bitset_t(1) << N;

    using value_storage_type = runtime_entry_t<N>::value_storage_type;
    using bitset_storage_type = runtime_entry_t<N>::bitset_storage_type;

    runtime_entry_t<N> rhs(value_storage_type{ 1.0 }, bitset_storage_type{});
    ga::bitset_t &rhs_bitset = *rhs.bitsets().begin();

    for (rhs_bitset = ga::bitset_t(0); rhs_bitset != end_bitset; ++rhs_bitset) {
        if (!_compile_time_vs_runtime_iterate_left<N>::run(prod, truth, rhs)) {
            return false;
        }
    }
    return true;
}

template<ga::ndims_t N, typename Product, typename Truth>
bool runtime_vs_runtime(Product prod, Truth truth) {
    constexpr ga::bitset_t end_bitset = ga::bitset_t(1) << N;

    using value_storage_type = runtime_entry_t<N>::value_storage_type;
    using bitset_storage_type = runtime_entry_t<N>::bitset_storage_type;

    runtime_entry_t<N> lhs(value_storage_type{ 1.0 }, bitset_storage_type{}), rhs(value_storage_type{ 1.0 }, bitset_storage_type{});
    ga::bitset_t &lhs_bitset = *lhs.bitsets().begin(), &rhs_bitset = *rhs.bitsets().begin();

    for (lhs_bitset = ga::bitset_t(0); lhs_bitset != end_bitset; ++lhs_bitset) {
        for (rhs_bitset = ga::bitset_t(0); rhs_bitset != end_bitset; ++rhs_bitset) {
            if (!check(prod, truth, lhs, rhs)) {
                return false;
            }
        }
    }
    return true;
}

#endif // __GA_TEST_HPP__
