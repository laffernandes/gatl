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
#include <gatl/ga/model/general.hpp>

using namespace ga;

// Set my metric space. This is just an example. Use <gatl/ga2c.hpp> in practical applications.
using my_space_t = constant_general_metric_space_t<
        1,  0,  0,  0,
        0,  1,  0,  0,
        0,  0,  0, -1,
        0,  0, -1,  0
    >;

// Declare some useful variables.
static my_space_t const space;
static std::array<std::string, 4> const basis_vectors_names = { "e1", "e2", "no", "ni" };

// Declare some useful constant blades.
static auto const e1 = e(c<1>);
static auto const e2 = e(c<2>);
static auto const no = e(c<3>);
static auto const ni = e(c<4>);

static auto const ep = (ni / c<2>) - no;
static auto const em = (ni / c<2>) + no;

static auto const I = pseudoscalar(space);
static auto const Ie = rcont(I, op(no, ni, space), space);

// Use GATL macros do overload operations.
_GA_CORE_OVERLOAD(space)
_GA_UTIL_OVERLOAD(space)
_GA_EXTRA_OVERLOAD(space, basis_vectors_names)

// Now you can use your own geometric model.
int main() {
    double x1, y1, x2, y2;

    std::cout << "-- Input" << std::endl;
    std::cout << std::endl;

    std::cout << "x1 = "; std::cin >> x1;
    std::cout << "y1 = "; std::cin >> y1;
    std::cout << "x2 = "; std::cin >> x2;
    std::cout << "y2 = "; std::cin >> y2;
    std::cout << std::endl;

    std::cout << "-- Those are my point" << std::endl;
    auto p1 = no + x1 * e1 + y1 * e2 + ((x1 * x1 + y1 * y1) / c<2>) * ni;
    auto p2 = no + x2 * e1 + y2 * e2 + ((x2 * x2 + y2 * y2) / c<2>) * ni;

    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;
    std::cout << std::endl;
    
    std::cout << "-- This is a circle passing through p1, p2, and the origin" << std::endl;
    auto C = p1 ^ p2 ^ no;

    std::cout << "C = " << C << std::endl;
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
