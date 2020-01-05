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

#ifndef __GA_EXTRA_FAST_PLUNGE_HPP__
#define __GA_EXTRA_FAST_PLUNGE_HPP__

namespace ga {

    // Returns the plunge of the given pair of blades. This function does not allow lazy evaluation. This operation is described in L. Dorst, D. Fontijne, and S. Mann (2007), "Geometric Algebra for Computer Science", MK, and the algorithm for computing the joint of the given blades is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename ToleranceType, typename MetricSpaceType>
    constexpr decltype(auto) fast_plunge(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol, metric_space<MetricSpaceType> const &mtr) {
        auto join = fast_join(lhs, rhs, tol, mtr);
        return op(dual(rhs, join, mtr), dual(lhs, join, mtr), mtr);
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType>
    constexpr decltype(auto) fast_plunge(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
        return fast_plunge(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), mtr);
    }

}

#endif // __GA_EXTRA_FAST_PLUNGE_HPP__
