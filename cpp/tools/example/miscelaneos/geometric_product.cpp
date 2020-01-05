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

using namespace ga3e;

int main() {
    std::cout << "-- A more interesting example" << std::endl;
    std::cout << std::endl;

    auto u = c<4> * e1 - c<2> * e2 + c<1> * e3;
    auto v = 6.5 * e1 + c<5> * e2 - 2 * e3;
    auto r = u * v;
    //auto r = gp(u, v); The * operator is an alias to ga::gp()

    std::cout << "u = " << u << std::endl;
    std::cout << "v = " << v << std::endl;
    std::cout << "r = gp(u, v) = " << r << std::endl;
    std::cout << std::endl;
    std::cout << "sizeof(u) = " << sizeof(u) << " bytes" << std::endl;
    std::cout << "sizeof(v) = " << sizeof(v) << " bytes" << std::endl;
    std::cout << "sizeof(r) = " << sizeof(r) << " bytes" << std::endl;
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
