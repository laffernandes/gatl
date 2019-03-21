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

#include "common.hpp"
#include <gatl/ga2e.hpp>

using namespace ga2e;

constexpr ga::ndims_t N = space_t::vector_space_dimensions;
constexpr std::size_t SIZE = 1 << N;

auto prod = [](auto const &lhs, auto const &rhs) { return hip(lhs, rhs); };

auto truth = [](auto const &lhs, auto const &rhs) {
    grade_t const lhs_grade = grade(lhs);
    grade_t const rhs_grade = grade(rhs);
    auto const aux = gp(lhs, rhs);
    if (lhs_grade != 0 && rhs_grade != 0) {
        return take_grade(aux, std::abs(lhs_grade - rhs_grade));
    }
    else {
        return take_grade(aux, -1);
    }
};

TEST(MultiplicationTable, CompileTimeVSCompileTime) {
    EXPECT_TRUE(compile_time_vs_compile_time<N>(prod, truth));
}

TEST(MultiplicationTable, CompileTimeVSRuntime) {
    EXPECT_TRUE(compile_time_vs_runtime<N>(prod, truth));
}

TEST(MultiplicationTable, RuntimeVSRuntime) {
    EXPECT_TRUE(runtime_vs_runtime<N>(prod, truth));
}
