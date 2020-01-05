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

#ifndef __GA3E_HPP__
#define __GA3E_HPP__

#include "ga/core.hpp"
#include "ga/util.hpp"
#include "ga/extra.hpp"
#include "ga/model/euclidean.hpp"

namespace ga3e {

    using namespace ga;

    _GA_EUCLIDEAN_ALGEBRA_DEFINITION(space, basis_vectors_names, 3, "e1", "e2", "e3")

    static auto const e1 = e(c<1>);
    static auto const e2 = e(c<2>);
    static auto const e3 = e(c<3>);

    _GA_CORE_OVERLOAD(space)
    _GA_UTIL_OVERLOAD(space)
    _GA_EXTRA_OVERLOAD(space, basis_vectors_names)
    _GA_EUCLIDEAN_ALGEBRA_OVERLOAD(space)

}

#endif // __GA3E_HPP__
