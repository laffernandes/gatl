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

#include <gatl/ga.hpp>
#include <gatl/ga/model/signed/metric_space.hpp>
#include <gtest/gtest.h>

using namespace ga;

signed_metric_space<6, 1, 0> const space;
std::array<std::string, 7> const basis_vectors = { "e1", "e2", "e3", "e4", "e5", "e6", "e7" };

auto const e1 = e(c<1>);
auto const e2 = e(c<2>);
auto const e3 = e(c<3>);
auto const e4 = e(c<4>);
auto const e5 = e(c<5>);
auto const e6 = e(c<6>);
auto const e7 = e(c<7>);

auto const constant_values_and_constant_basis_blades = c<1> + op(e1, (c<1> + op(e2, (c<1> + op(e3, (c<1> + op(e4, (c<1> + op(e5, (c<1> + op(e6, (c<1> + e7), space)), space)), space)), space)), space)), space);
auto const dynamic_values_and_constant_basis_blades = 1 + op(1 * e1, (1 + op(1 * e2, (1 + op(1 * e3, (1 + op(1 * e4, (1 + op(1 * e5, (1 + op(1 * e6, (1 + 1 * e7), space)), space)), space)), space)), space)), space);

template<typename ValueType>
bool test_grade(bitset_t const basis_vectors, ValueType const value, std::string const &pattern) {
    return pattern[detail::ones(basis_vectors)] == (value == -1 ? '-' : (value == 1 ? '+' : '?'));
}

template<typename CoefficientType, typename Expression>
bool test_using_constant_basis_blades(clifford_expression<CoefficientType, Expression> const &arg, std::string const &pattern) {
    return for_each_component(arg, [&](bitset_t const basis_vectors, auto const &value, entry_source_t const, entry_source_t const, bool &keep_going) { keep_going = test_grade(basis_vectors, value, pattern); });
}

template<typename Function>
bool test_using_dynamic_basis_blades(Function f, std::string const &pattern) {
    scaled_basis_blade_t<int, 0, space.vector_space_dimensions> x(make_sequential_storage(1), make_sequential_storage(bitset_t(0)));
    for (ndims_t n = 0; n != space.vector_space_dimensions; ++n) {
        *x.bitsets().begin() = detail::first_combination(n);
        const auto result = f(x);
        if (!test_grade(*result.bitsets().begin(), *result.values().begin(), pattern)) {
            return false;
        }
    }
    return true;
}

TEST(SignChangeOperations, Conjugation) {
    EXPECT_TRUE(test_using_constant_basis_blades(conjugate(constant_values_and_constant_basis_blades), "+--++--+"));
    EXPECT_TRUE(test_using_constant_basis_blades(conjugate(dynamic_values_and_constant_basis_blades), "+--++--+"));
    EXPECT_TRUE(test_using_dynamic_basis_blades([](auto const &arg) { return conjugate(arg); }, "+--++--+"));
}

TEST(SignChangeOperations, Involution) {
    EXPECT_TRUE(test_using_constant_basis_blades(involute(constant_values_and_constant_basis_blades), "+-+-+-+-"));
    EXPECT_TRUE(test_using_constant_basis_blades(involute(dynamic_values_and_constant_basis_blades), "+-+-+-+-"));
    EXPECT_TRUE(test_using_dynamic_basis_blades([](auto const &arg) { return involute(arg); }, "+-+-+-+-"));
}

TEST(SignChangeOperations, Reversion) {
    EXPECT_TRUE(test_using_constant_basis_blades(reverse(constant_values_and_constant_basis_blades), "++--++--"));
    EXPECT_TRUE(test_using_constant_basis_blades(reverse(dynamic_values_and_constant_basis_blades), "++--++--"));
    EXPECT_TRUE(test_using_dynamic_basis_blades([](auto const &arg) { return reverse(arg); }, "++--++--"));
}
