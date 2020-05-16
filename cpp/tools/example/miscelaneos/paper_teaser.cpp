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

#include <gatl/ga3h.hpp>

using namespace ga3h;

int main() {
    double x_, y_, z_, phi_deg_;
    std::cout << "x = "; std::cin >> x_;
    std::cout << "y = "; std::cin >> y_;
    std::cout << "z = "; std::cin >> z_;
    std::cout << std::endl;
    std::cout << "phi_deg = "; std::cin >> phi_deg_;
    std::cout << std::endl;

    double phi_ = phi_deg_ * (M_PI / 180.0);

    auto lazy = make_lazy_context(scalar(x_), scalar(y_), scalar(z_), scalar(phi_));
    auto [x, y, z, phi] = lazy.arguments();

    auto a = vector(x, y, z, c<0>);
    auto R = cos(phi / c<2>) - sin(phi / c<2>) * (e1^e2);
    auto b = R * a * ~R;

    auto b_ = lazy.eval(b);

    std::cout << "b = " << b_ << std::endl;

    return EXIT_SUCCESS;
}
