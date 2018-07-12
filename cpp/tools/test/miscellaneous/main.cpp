/**
Copyright (C) 2018 Leandro Augusto Frata Fernandes

author     : Fernandes, Leandro A. F.
e-mail     : laffernandes@ic.uff.br
home page  : http://www.ic.uff.br/~laffernandes
repository : https://github.com/laffernandes/gatl.git

This file is part of The Geometric Algebra Template Library (GATL).

GATL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GATL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GATL. If not, see <https://www.gnu.org/licenses/>.
/**/

#include <ga5e.hpp>
#include <gtest/gtest.h>

using namespace ga5e;

template<typename CoefficientType, typename Expression>
std::string to_string(ga::clifford_expression<CoefficientType, Expression> const &arg) {
	std::stringstream ss;
	ss << arg;
	return ss.str();
}

TEST(Miscellaneous, ConstantScalar) {
	EXPECT_EQ(to_string(c<5>), "<5> * <1>");
	EXPECT_EQ(to_string(c<-3>), "<-3> * <1>");
	EXPECT_EQ(to_string(c<0>), "<0> * <1>");
}

TEST(Miscellaneous, UnitBasisVector) {
	EXPECT_EQ(to_string(e(c<1>)), "<1> * <e1>");
	EXPECT_EQ(to_string(e(c<5>)), "<1> * <e5>");
	EXPECT_EQ(to_string(e(1)), "<1> * e1");
	EXPECT_EQ(to_string(e(5)), "<1> * e5");
}

TEST(Miscellaneous, UnitConstantBasisBlade) {
	EXPECT_EQ(to_string(unit_constant_basis_blade_t<1, 3, 4>()), "<1> * <e1^e3^e4>");
	EXPECT_EQ(to_string(unit_constant_basis_blade_t<2>()), "<1> * <e2>");
}

TEST(Miscellaneous, Simplification1) {
	auto x = c<2> / c<3>;
	auto y = c<4>;
	auto z = c<7> / c<5>;
	std::string result = "<56> * pow(<15>, <-1>) * <1>";

	EXPECT_EQ(to_string((x * y) * z), result);
	EXPECT_EQ(to_string(x * (y * z)), result);
	EXPECT_EQ(to_string((x * z) * y), result);
	EXPECT_EQ(to_string(x * (z * y)), result);
	EXPECT_EQ(to_string((y * x) * z), result);
	EXPECT_EQ(to_string(y * (x * z)), result);
	EXPECT_EQ(to_string((y * z) * x), result);
	EXPECT_EQ(to_string(y * (z * x)), result);
	EXPECT_EQ(to_string((z * x) * y), result);
	EXPECT_EQ(to_string(z * (x * y)), result);
	EXPECT_EQ(to_string((z * y) * x), result);
	EXPECT_EQ(to_string(z * (y * x)), result);
}

TEST(Miscellaneous, Simplification2) {
	auto x = c<2> / c<3>;
	auto y = c<4>;
	auto z = c<7> / c<5>;
	std::string result = "(<4> + <31> * pow(<15>, <-1>)) * <1>";

	EXPECT_EQ(to_string((x + y) + z), result);
	EXPECT_EQ(to_string(x + (y + z)), result);
	EXPECT_EQ(to_string((x + z) + y), result);
	EXPECT_EQ(to_string(x + (z + y)), result);
	EXPECT_EQ(to_string((y + x) + z), result);
	EXPECT_EQ(to_string(y + (x + z)), result);
	EXPECT_EQ(to_string((y + z) + x), result);
	EXPECT_EQ(to_string(y + (z + x)), result);
	EXPECT_EQ(to_string((z + x) + y), result);
	EXPECT_EQ(to_string(z + (x + y)), result);
	EXPECT_EQ(to_string((z + y) + x), result);
	EXPECT_EQ(to_string(z + (y + x)), result);
}

TEST(Miscellaneous, Simplification3) {
	auto const lazy = make_lazy_context(scalar(10.0), scalar(5.0), scalar(3.0));

	EXPECT_EQ(to_string(lazy.eval(lazy.argument<0>() * (lazy.argument<1>() + lazy.argument<2>()))), "80 * <1>");
	EXPECT_EQ(to_string(lazy.eval(lazy.argument<0>() * c<0>)), "<0> * <1>");
	EXPECT_EQ(to_string(lazy.eval(c<0> * lazy.argument<0>())), "<0> * <1>");
}
