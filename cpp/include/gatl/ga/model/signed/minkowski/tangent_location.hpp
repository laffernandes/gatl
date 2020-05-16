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

#ifndef __GA_MODEL_SIGNED_MINKOWSKI_TANGENT_LOCATION_HPP__
#define __GA_MODEL_SIGNED_MINKOWSKI_TANGENT_LOCATION_HPP__

namespace ga {

    // Returns the location parameter of a given dual tangent.
    template<typename CoefficientType, typename Expression, ndims_t D>
    constexpr decltype(auto) dual_tangent_location(clifford_expression<CoefficientType, Expression> const &dual_tangent, minkowski_metric_space<D> const &mtr) {
        auto [lazy, dual_tangent_] = make_lazy_context_tuple(dual_tangent);
        constexpr auto ni = e(c<D + 1>) + e(c<D + 2>);
        return lazy.eval(gp(dual_tangent_, inv(lcont(-ni, dual_tangent_, mtr), mtr), mtr));
    }

    // Returns the location parameter of a given primal tangent.
    template<typename CoefficientType, typename Expression, ndims_t D>
    constexpr decltype(auto) primal_tangent_location(clifford_expression<CoefficientType, Expression> const &primal_tangent, minkowski_metric_space<D> const &mtr) {
        auto [lazy, primal_tangent_] = make_lazy_context_tuple(primal_tangent);
        constexpr auto ni = e(c<D + 1>) + e(c<D + 2>);
        return lazy.eval(gp(primal_tangent_, inv(lcont(-ni, primal_tangent_, mtr), mtr), mtr));
    }

}

#endif // __GA_MODEL_SIGNED_MINKOWSKI_TANGENT_LOCATION_HPP__
