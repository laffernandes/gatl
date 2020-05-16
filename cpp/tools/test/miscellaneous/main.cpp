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

#include <gatl/ga4h.hpp>
#include <gatl/ga5e.hpp>
#include <gtest/gtest.h>

template<typename CoefficientType, typename Expression>
std::string to_string(ga::clifford_expression<CoefficientType, Expression> const &arg) {
    using namespace ga5e;

    std::stringstream ss;
    ss << arg;
    return ss.str();
}

TEST(Miscellaneous, ConstantScalar) {
    using namespace ga5e;

    EXPECT_EQ(to_string(c<5>), "<5> * <1>");
    EXPECT_EQ(to_string(c<-3>), "<-3> * <1>");
    EXPECT_EQ(to_string(c<0>), "<0> * <1>");
}

TEST(Miscellaneous, UnitBasisVector) {
    using namespace ga5e;

    EXPECT_EQ(to_string(e(c<1>)), "<1> * <e1>");
    EXPECT_EQ(to_string(e(c<5>)), "<1> * <e5>");
    EXPECT_EQ(to_string(e(1)), "<1> * e1");
    EXPECT_EQ(to_string(e(5)), "<1> * e5");
}

TEST(Miscellaneous, UnitConstantBasisBlade) {
    using namespace ga5e;

    EXPECT_EQ(to_string(unit_constant_basis_blade_t<1, 3, 4>()), "<1> * <e1^e3^e4>");
    EXPECT_EQ(to_string(unit_constant_basis_blade_t<2>()), "<1> * <e2>");
}

TEST(Miscellaneous, Simplification1) {
    using namespace ga5e;

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
    using namespace ga5e;

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
    using namespace ga5e;

    auto lazy = make_lazy_context(scalar(10.0), scalar(5.0), scalar(3.0));

    EXPECT_EQ(to_string(lazy.eval(lazy.argument<0>() * (lazy.argument<1>() + lazy.argument<2>()))), "80 * <1>");
    EXPECT_EQ(to_string(lazy.eval(lazy.argument<0>() * c<0>)), "<0> * <1>");
    EXPECT_EQ(to_string(lazy.eval(c<0> * lazy.argument<0>())), "<0> * <1>");
}

TEST(Miscellaneous, Simplification4) {
    using namespace ga4h;

    auto addition = [](auto const &x, auto const &y, auto eval) {
        return eval(x + x + y);
    };

    auto subtraction = [](auto const &x, auto eval) {
        return eval(x - x);
    };

    auto product = [](auto const &x, auto const &y, auto eval) {
        auto p = ep + x * e1 + y * e3;
        auto d = x * e1 + y * e2;
        return eval(p ^ d);
    };

    auto span_line = [](auto const &x, auto const &y, auto const &z, auto eval) {
        auto p = ep + x * e1 + y * e2 + z * e3;
        auto d = x * e1 + y * e2 + z * e3;
        return eval(p ^ d);
    };

    auto lazy = make_lazy_context(scalar(5.0), scalar(3.0), scalar(10.0), scalar(-7.0));
    auto eval = [&](auto const &arg) -> decltype(auto) { return arg; };
    auto lazy_eval = [&](auto const &arg) -> decltype(auto) { return lazy.eval(arg); };

    EXPECT_EQ(to_string(addition(lazy.argument<0>(), lazy.argument<1>(), lazy_eval)), "13 * <1>");

    EXPECT_EQ(to_string(subtraction(lazy.argument<0>(), lazy_eval)), "<0> * <1>");

    EXPECT_EQ(to_string(product(5.0, 3.0, eval)), "15 * <e1^e2> + (-15) * <e1^e3> + (-9) * <e2^e3> + (-5) * <e1^e5> + (-3) * <e2^e5>");
    EXPECT_EQ(to_string(product(lazy.argument<0>(), lazy.argument<1>(), lazy_eval)), "15 * <e1^e2> + (-15) * <e1^e3> + (-9) * <e2^e3> + (-5) * <e1^e5> + (-3) * <e2^e5>");

    EXPECT_EQ(to_string(span_line(10.0, 5.0, -7.0, eval)), "0 * <e1^e2> + 0 * <e1^e3> + 0 * <e2^e3> + (-10) * <e1^e5> + (-5) * <e2^e5> + 7 * <e3^e5>");
    EXPECT_EQ(to_string(span_line(lazy.argument<2>(), lazy.argument<0>(), lazy.argument<3>(), lazy_eval)), "(-10) * <e1^e5> + (-5) * <e2^e5> + 7 * <e3^e5>");
}
