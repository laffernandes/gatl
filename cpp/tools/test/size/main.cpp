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

#include <gatl/ga5e.hpp>
#include <gtest/gtest.h>

using namespace ga5e;

TEST(Size, ConstantScalar) {
    auto a = c<5>;
    auto b = pow(c<2>, c<10>);

    EXPECT_EQ(sizeof(a), 1);
    EXPECT_EQ(sizeof(b), 1);
    EXPECT_EQ(sizeof(a + b), 1);
}

TEST(Size, ScaledScalar) {
    auto a = scalar(5.0);
    auto b = pow(2.0, 10);

    EXPECT_EQ(sizeof(a), sizeof(double));
    EXPECT_EQ(sizeof(b), sizeof(double));
    EXPECT_EQ(sizeof(a + b), sizeof(double));
}

TEST(Size, LazyArgument) {
    auto lazy = make_lazy_context(scalar(5.0), scalar(7), scalar(7.0));
    auto x = lazy.argument<0>() + lazy.argument<1>();
    auto y = c<5> + sqrt(lazy.argument<2>());
    auto z = c<5> + sqrt(c<7>) + cbrt(c<11>);

    EXPECT_EQ(sizeof(x), 1);
    EXPECT_EQ(sizeof(y), 1);
    EXPECT_EQ(sizeof(z), 1);
}

TEST(Size, MixedExpressions1) {
    auto lazy = make_lazy_context(scalar(5.0), scalar(7), scalar(7.0));

    auto x1 = c<5> + pow(c<2>, c<10>);
    auto x2 = scalar(5.0);
    auto x3 = lazy.argument<0>() + lazy.argument<1>();

    EXPECT_EQ(sizeof(decltype(x1 + x2)), sizeof(double));
    EXPECT_EQ(sizeof(decltype(x1 + x3)), 1);
    EXPECT_EQ(sizeof(decltype(x2 + x3)), sizeof(double));

    EXPECT_EQ(sizeof(decltype(x1 * x2)), sizeof(double));
    EXPECT_EQ(sizeof(decltype(x1 * x3)), 1);
    EXPECT_EQ(sizeof(decltype(x2 * x3)), 2 * sizeof(double));

    EXPECT_EQ(sizeof(decltype(sqrt(x1))), 1);
    EXPECT_EQ(sizeof(decltype(sqrt(x2))), sizeof(double));
    EXPECT_EQ(sizeof(decltype(sqrt(x3))), 1);

    EXPECT_EQ(sizeof(decltype(sqrt(c<4>))), 1);
    EXPECT_EQ(sizeof(decltype(sqrt(c<8>))), 1);
}

TEST(Size, MixedExpressions2) {
    double x = 10.0, y = 20.0, z = 30.0;
    auto p = (x * e1 + y * e2 + z * e3 + e4) ^ e5;
    auto r = gp(p, e3);

    EXPECT_EQ(sizeof(decltype(e1)), 1);
    EXPECT_EQ(sizeof(decltype(e1 + e2 + e3)), 1);
    EXPECT_EQ(sizeof(decltype(p)), 3 * sizeof(double));
    EXPECT_EQ(sizeof(decltype(r)), 3 * sizeof(double));
}
