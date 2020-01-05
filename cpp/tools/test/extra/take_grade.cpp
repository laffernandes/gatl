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

auto ei = e(1);
auto ej = e(2);
auto ek = e(3);

TEST(Extra, TakeGrade1) {
    EXPECT_TRUE(is_zero(take_grade(e1, c<0>) - take_grade(e1, 0)));
    EXPECT_TRUE(is_zero(take_grade(e1, c<1>) - take_grade(e1, 1)));
    EXPECT_TRUE(is_zero(take_grade(e1, c<2>) - take_grade(e1, 2)));
}

TEST(Extra, TakeGrade2) {
    EXPECT_TRUE(is_zero(take_grade(e1^e2, c<0>) - take_grade(e1^e2, 0)));
    EXPECT_TRUE(is_zero(take_grade(e1^e2, c<1>) - take_grade(e1^e2, 1)));
    EXPECT_TRUE(is_zero(take_grade(e1^e2, c<2>) - take_grade(e1^e2, 2)));
}

TEST(Extra, TakeGrade3) {
    EXPECT_TRUE(is_zero(take_grade(ei, c<0>) - take_grade(e1, c<0>)));
    EXPECT_TRUE(is_zero(take_grade(ej, c<1>) - take_grade(e2, c<1>)));
    EXPECT_TRUE(is_zero(take_grade(ek, c<2>) - take_grade(e3, c<2>)));
}

TEST(Extra, TakeGrade4) {
    EXPECT_TRUE(is_zero(take_grade(ei^ej, c<0>) - take_grade(e1^e2, c<0>)));
    EXPECT_TRUE(is_zero(take_grade(ei^ej, c<1>) - take_grade(e1^e2, c<1>)));
    EXPECT_TRUE(is_zero(take_grade(ei^ej, c<2>) - take_grade(e1^e2, c<2>)));
}

TEST(Extra, TakeGrade5) {
    EXPECT_TRUE(is_zero(take_grade(ei^ej, c<0>) - take_grade(ei^ej, 0)));
    EXPECT_TRUE(is_zero(take_grade(ei^ej, c<1>) - take_grade(ei^ej, 1)));
    EXPECT_TRUE(is_zero(take_grade(ei^ej, c<2>) - take_grade(ei^ej, 2)));
}

TEST(Extra, TakeGrade6) {
    EXPECT_TRUE(is_zero(take_grade(c<1> + e1 + e2 + e3 + (e1^e2) + (e1^e3) + (e2^e3) + (e1^e2^e3), c<0>) - c<1>));
    EXPECT_TRUE(is_zero(take_grade(c<1> + e1 + e2 + e3 + (e1^e2) + (e1^e3) + (e2^e3) + (e1^e2^e3), c<1>) - (e1 + e2 + e3)));
    EXPECT_TRUE(is_zero(take_grade(c<1> + e1 + e2 + e3 + (e1^e2) + (e1^e3) + (e2^e3) + (e1^e2^e3), c<2>) - ((e1^e2) + (e1^e3) + (e2^e3))));
    EXPECT_TRUE(is_zero(take_grade(c<1> + e1 + e2 + e3 + (e1^e2) + (e1^e3) + (e2^e3) + (e1^e2^e3), c<3>) - (e1^e2^e3)));
}

TEST(Extra, TakeGrade7) {
    EXPECT_TRUE(is_zero(take_grade(c<1> + e1 + e2 + e3 + (e1^e2) + (e1^e3) + (e2^e3) + (e1^e2^e3), 0) - c<1>));
    EXPECT_TRUE(is_zero(take_grade(c<1> + e1 + e2 + e3 + (e1^e2) + (e1^e3) + (e2^e3) + (e1^e2^e3), 1) - (e1 + e2 + e3)));
    EXPECT_TRUE(is_zero(take_grade(c<1> + e1 + e2 + e3 + (e1^e2) + (e1^e3) + (e2^e3) + (e1^e2^e3), 2) - ((e1^e2) + (e1^e3) + (e2^e3))));
    EXPECT_TRUE(is_zero(take_grade(c<1> + e1 + e2 + e3 + (e1^e2) + (e1^e3) + (e2^e3) + (e1^e2^e3), 3) - (e1^e2^e3)));
}

TEST(Extra, TakeGrade8) {
    EXPECT_TRUE(is_zero(take_grade(1 + ei + ej + ek + (ei^ej) + (ei^ek) + (ej^ek) + (ei^ej^ek), c<0>) - c<1>));
    EXPECT_TRUE(is_zero(take_grade(1 + ei + ej + ek + (ei^ej) + (ei^ek) + (ej^ek) + (ei^ej^ek), c<1>) - (e1 + e2 + e3)));
    EXPECT_TRUE(is_zero(take_grade(1 + ei + ej + ek + (ei^ej) + (ei^ek) + (ej^ek) + (ei^ej^ek), c<2>) - ((e1^e2) + (e1^e3) + (e2^e3))));
    EXPECT_TRUE(is_zero(take_grade(1 + ei + ej + ek + (ei^ej) + (ei^ek) + (ej^ek) + (ei^ej^ek), c<3>) - (e1^e2^e3)));
}

TEST(Extra, TakeGrade9) {
    EXPECT_TRUE(is_zero(take_grade(1 + ei + ej + ek + (ei^ej) + (ei^ek) + (ej^ek) + (ei^ej^ek), 0) - c<1>));
    EXPECT_TRUE(is_zero(take_grade(1 + ei + ej + ek + (ei^ej) + (ei^ek) + (ej^ek) + (ei^ej^ek), 1) - (e1 + e2 + e3)));
    EXPECT_TRUE(is_zero(take_grade(1 + ei + ej + ek + (ei^ej) + (ei^ek) + (ej^ek) + (ei^ej^ek), 2) - ((e1^e2) + (e1^e3) + (e2^e3))));
    EXPECT_TRUE(is_zero(take_grade(1 + ei + ej + ek + (ei^ej) + (ei^ek) + (ej^ek) + (ei^ej^ek), 3) - (e1^e2^e3)));
}
