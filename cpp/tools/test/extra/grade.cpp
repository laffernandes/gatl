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

TEST(Extra, Grade0) {
    EXPECT_EQ(grade(8.0), 0);
    EXPECT_EQ(grade(c<1>), 0);
}

TEST(Extra, Grade1) {
    EXPECT_EQ(grade(e1), 1);
}

TEST(Extra, Grade2) {
    EXPECT_EQ(grade(e1^e2), 2);
    EXPECT_EQ(grade((e1^e2) + (e1^e3)), 2);
    EXPECT_EQ(grade((e(1)^e2) + (e1^e3)), 2);
    EXPECT_EQ(grade((9.0 * e1^e2) + (e1^e3)), 2);
    EXPECT_EQ(grade((9 * e(1)^e2) + (e1^e3)), 2);
}

TEST(Extra, Grade3) {
    EXPECT_EQ(grade(c<5, double> - e1), MIXED_GRADE);
    EXPECT_EQ(grade(5.0 - e1), MIXED_GRADE);
}

TEST(Extra, Grade4) {
    EXPECT_EQ(grade(c<0>), UNDETERMINED_GRADE);
    EXPECT_EQ(grade(0 * e1), UNDETERMINED_GRADE);
}
