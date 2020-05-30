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
    double x, y, z, phi_deg;

    std::cout << "-- Input" << std::endl;
    std::cout << std::endl;

    std::cout << "x = "; std::cin >> x;
    std::cout << "y = "; std::cin >> y;
    std::cout << "z = "; std::cin >> z;
    std::cout << std::endl;

    std::cout << "phi_deg = "; std::cin >> phi_deg;
    std::cout << std::endl;

    double phi = phi_deg * (M_PI / 180.0);

    auto a = vector(x, y, z);

    auto lazy = make_lazy_context(a, scalar(phi));
    auto [a_, phi_] = lazy.arguments();
    
    auto R_ = cos(phi_ / c<2>) - sin(phi_ / c<2>) * (e1^e2);
    auto b_ = R_ * a_ * ~R_;

    auto b = lazy.eval(b_);

    std::cout << "-- Result" << std::endl;
    std::cout << std::endl;

    std::cout << "b = " << b << std::endl;
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
