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

#include <gatl/ga3c.hpp>

using namespace ga3c;

int main() {
    auto p1 = point(1.0,  0.0, c<0>);
    auto p2 = point(0.0, -1.0, c<0>);
    auto p3 = point(1.0, -2.0, c<0>);
    auto circle = p1 ^ p2 ^ p3;
    auto line = p1 ^ p2 ^ ni;
    auto tangent = lcont(-p1, circle);

    std::cout << "-- Input" << std::endl;
    std::cout << std::endl;
    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;
    std::cout << "p3 = " << p3 << std::endl;
    std::cout << std::endl;

    std::cout << "-- Round" << std::endl;
    std::cout << std::endl;
    std::cout << "   circle = p1^p2^p3 = " << circle << std::endl;
    std::cout << std::endl;
    std::cout << "direction = " << primal_round_direction(circle) << std::endl;
    std::cout << "   center = " << primal_round_location(circle) << std::endl;
    std::cout << "   radius = " << sqrt(primal_round_size_sqr(circle)) << std::endl;
    std::cout << std::endl;

    std::cout << "-- Flat" << std::endl;
    std::cout << std::endl;
    std::cout << "     line = p1^p2^ni = " << line << std::endl;
    std::cout << std::endl;
    std::cout << "direction = " << primal_flat_direction(line) << std::endl;
    std::cout << " location = " << primal_flat_location(line) << std::endl;
    std::cout << std::endl;

    std::cout << "-- Tangent Direction" << std::endl;
    std::cout << std::endl;
    std::cout << "  tangent = lcont(-p1, circle) = " << tangent << std::endl;
    std::cout << std::endl;
    std::cout << "direction = " << primal_tangent_direction(tangent) << std::endl;
    std::cout << " location = " << primal_tangent_location(tangent) << std::endl;
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
