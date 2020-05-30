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

#ifndef __GA_EXTRA_VERSOR_INVERSE_HPP__
#define __GA_EXTRA_VERSOR_INVERSE_HPP__

namespace ga {

    template<typename CoefficientType, typename Expression, typename MetricSpaceType>
    constexpr decltype(auto) inv(clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
        auto [lazy, arg_] = make_lazy_context_tuple(arg);
        return lazy.eval(gp(reverse(arg_), inv(rnorm_sqr(arg_, mtr))));
    }

    template<typename CoefficientType, typename Coefficient>
    constexpr decltype(auto) inv(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
        return pow(arg, c<-1>);
    }

    template<typename Type, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<Type>, int> = 0>
    constexpr decltype(auto) inv(Type const &arg, metric_space<MetricSpaceType> const &) {
        return pow(scalar(arg), c<-1>);
    }

    template<typename Type, std::enable_if_t<!is_clifford_expression_v<Type>, int> = 0>
    constexpr decltype(auto) inv(Type const &arg) {
        return pow(scalar(arg), c<-1>);
    }

}

#endif // __GA_EXTRA_VERSOR_INVERSE_HPP__
