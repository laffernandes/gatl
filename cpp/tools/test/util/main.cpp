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

TEST(Util, Vector1) {
    auto v = vector(c<0>, c<0>, c<0>);

    EXPECT_EQ(to_string(v), "<0> * <1>");
    EXPECT_EQ(sizeof(v), 1);
}

TEST(Util, Vector2) {
    auto v = vector(c<0>, c<0>, 10.5);

    EXPECT_EQ(to_string(v), "10.5 * <e3>");
    EXPECT_EQ(sizeof(v), sizeof(double));
}

TEST(Util, Vector3) {
    auto v = vector(c<4>, c<0>, 10.5);

    EXPECT_EQ(to_string(v), "<4> * <e1> + 10.5 * <e3>");
    EXPECT_EQ(sizeof(v), sizeof(double));
}
