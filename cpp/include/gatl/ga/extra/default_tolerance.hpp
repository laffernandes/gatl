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

#ifndef __GA_EXTRA_DEFAULT_TOLERANCE_HPP__
#define __GA_EXTRA_DEFAULT_TOLERANCE_HPP__

#ifndef GA_DEFAULT_FLT_TOLERANCE
    #define GA_DEFAULT_FLT_TOLERANCE 1.0e-8f
#else
    static_assert(GA_DEFAULT_FLT_TOLERANCE >= 0, "GA_DEFAULT_FLT_TOLERANCE must be a non-negative value.")
#endif // GA_DEFAULT_FLT_TOLERANCE

#ifndef GA_DEFAULT_DBL_TOLERANCE
    #define GA_DEFAULT_DBL_TOLERANCE 1.0e-8
#else
    static_assert(GA_DEFAULT_DBL_TOLERANCE >= 0, "GA_DEFAULT_DBL_TOLERANCE must be a non-negative value.")
#endif // GA_DEFAULT_DBL_TOLERANCE

namespace ga {

    template<typename ValueType>
    constexpr decltype(auto) default_tolerance() GA_NOEXCEPT {
        return c<0, ValueType>;
    }

    template<>
    constexpr decltype(auto) default_tolerance<std::float_t>() GA_NOEXCEPT {
        return scalar(GA_DEFAULT_FLT_TOLERANCE);
    }

    template<>
    constexpr decltype(auto) default_tolerance<std::double_t>() GA_NOEXCEPT {
        return scalar(GA_DEFAULT_DBL_TOLERANCE);
    }

}

#endif // __GA_EXTRA_DEFAULT_TOLERANCE_HPP__
