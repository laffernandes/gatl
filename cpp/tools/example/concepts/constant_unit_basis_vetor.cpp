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
    std::cout << "-- Constant unit basis vector defined in compilation time" << std::endl;
    std::cout << std::endl;

    auto a = e(c<1>);
    //auto a = e1; // helper from ga3e

    std::cout << "a = " << a << std::endl;
    std::cout << std::endl;

    std::cout << "sizeof(a) = " << sizeof(a) << " bytes" << std::endl;
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
