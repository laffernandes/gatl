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

#ifndef __GA_EXTRA_TESTS_HPP__
#define __GA_EXTRA_TESTS_HPP__

namespace ga {

    // Returns whether the given Clifford expression is equal to zero up to an assumed numerical error.
    template<typename CoefficientType, typename Expression, typename ToleranceType>
    constexpr bool is_zero(clifford_expression<CoefficientType, Expression> const &arg, ToleranceType const &tol) {
        return for_each_component(arg, [&](bitset_t const, CoefficientType const &value, entry_source_t const, entry_source_t const, bool &keep_going) { keep_going = abs(value) <= (CoefficientType)tol; });
    }

    template<typename CoefficientType, typename Expression>
    constexpr bool is_zero(clifford_expression<CoefficientType, Expression> const &arg) {
        return is_zero(arg, default_tolerance<CoefficientType>());
    }

    // Returns whether the given Clifford expression is a null multivector up to an assumed numerical error.
    template<typename CoefficientType, typename Expression, typename ToleranceType, typename MetricSpaceType>
    constexpr bool is_null(clifford_expression<CoefficientType, Expression> const &arg, ToleranceType const &tol, metric_space<MetricSpaceType> const &mtr) GA_NOEXCEPT {
        return is_zero(rnorm_sqr(arg, mtr), tol);
    }

    // Returns whether the given Clifford expression is a unit multivector up to an assumed numerical error.
    template<typename CoefficientType, typename Expression, typename ToleranceType, typename MetricSpaceType>
    constexpr bool is_unit(clifford_expression<CoefficientType, Expression> const &arg, ToleranceType const &tol, metric_space<MetricSpaceType> const &mtr) GA_NOEXCEPT {
        return is_zero(abs(rnorm_sqr(arg, mtr)) - c<1>, tol);
    }

}

#endif // __GA_EXTRA_TESTS_HPP__
