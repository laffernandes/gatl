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

#include <gatl/ga3e.hpp>
#include <gtest/gtest.h>

using namespace ga3e;

template<typename CoefficientType, typename Expression>
std::string to_string(ga::clifford_expression<CoefficientType, Expression> const &arg) {
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

TEST(PlusAndMinus, UnaryPlus) {
    EXPECT_EQ(to_string(+e(1)), "<1> * e1");
    EXPECT_EQ(to_string(+e(c<2>)), "<1> * <e2>");
}

TEST(PlusAndMinus, UnaryMinus) {
    EXPECT_EQ(to_string(-e(1)), "<-1> * e1");
    EXPECT_EQ(to_string(-e(c<2>)), "<-1> * <e2>");
}

TEST(PlusAndMinus, BinaryPlus) {
    EXPECT_EQ(to_string(e(c<1>) + e(c<2>)), "<1> * <e1> + <1> * <e2>");
    EXPECT_EQ(to_string(c<5> + e(c<1>) + e(c<2>) + e(c<1>)), "<5> * <1> + <2> * <e1> + <1> * <e2>");
    EXPECT_EQ(to_string(5.0 + e(c<1>) + e(c<2>)), "5 * <1> + <1> * <e1> + <1> * <e2>");
    EXPECT_EQ(to_string(e(c<1>) + 5.0 + e(c<1>) + e(c<2>) + e(c<1>)), "5 * <1> + <3> * <e1> + <1> * <e2>");
}

TEST(PlusAndMinus, BinaryMinus) {
    EXPECT_EQ(to_string(e(c<1>) - e(c<2>)), "<1> * <e1> + <-1> * <e2>");
    EXPECT_EQ(to_string(e(c<2>) - e(c<1>)), "<-1> * <e1> + <1> * <e2>");
    EXPECT_EQ(to_string(c<5> - e(c<1>) + e(c<2>) + e(c<1>)), "<5> * <1> + <1> * <e2>");
    EXPECT_EQ(to_string(5.0 - e(c<1>) - e(c<2>)), "5 * <1> + <-1> * <e1> + <-1> * <e2>");
    EXPECT_EQ(to_string(e(c<1>) - 5.0 - e(c<2>) - e(c<2>) - e(c<3>)), "(-5) * <1> + <1> * <e1> + <-2> * <e2> + <-1> * <e3>");
}
