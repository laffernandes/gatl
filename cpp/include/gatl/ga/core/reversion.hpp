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

#ifndef __GA_CORE_REVERSION_HPP__
#define __GA_CORE_REVERSION_HPP__

namespace ga {

    template<typename CoefficientType, typename Expression>
    constexpr decltype(auto) reverse(clifford_expression<CoefficientType, Expression> const &arg) GA_NOEXCEPT {
        auto lazy = make_lazy_context(arg);
        return lazy.eval(clifford_expression<default_integral_t, detail::graded_unary_minus_t<typename decltype(lazy)::template argument_expression_t<0>, (bitset_t)0xCCCCCCCCCCCCCCCCull> >());
    }

    template<typename Type>
    constexpr decltype(auto) reverse(Type const &arg) GA_NOEXCEPT {
        return reverse(scalar(arg));
    }

}

#endif // __CORE_GA_REVERSION_HPP__
