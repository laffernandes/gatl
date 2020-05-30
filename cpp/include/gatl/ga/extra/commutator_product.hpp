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

#ifndef __GA_EXTRA_COMMUTATOR_PRODUCT_HPP__
#define __GA_EXTRA_COMMUTATOR_PRODUCT_HPP__

namespace ga {

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType>
    constexpr decltype(auto) cp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) GA_NOEXCEPT {
        auto [lazy, lhs_, rhs_] = make_lazy_context_tuple(lhs, rhs);
        return lazy.eval((gp(lhs_, rhs_, mtr) - gp(rhs_, lhs_, mtr)) / c<2>);
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) cp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) GA_NOEXCEPT {
        return cp(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) cp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) GA_NOEXCEPT {
        return cp(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) cp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) GA_NOEXCEPT {
        return cp(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<RightType>, int> = 0>
    constexpr decltype(auto) cp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return cp(lhs, scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, std::enable_if_t<!is_clifford_expression_v<RightType>, int> = 0>
    constexpr decltype(auto) cp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) GA_NOEXCEPT {
        return cp(lhs, scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<LeftType>, int> = 0>
    constexpr decltype(auto) cp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return cp(scalar(lhs), rhs, detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, std::enable_if_t<!is_clifford_expression_v<LeftType>, int> = 0>
    constexpr decltype(auto) cp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) GA_NOEXCEPT {
        return cp(scalar(lhs), rhs, detail::real_metric_space());
    }

    template<typename LeftType, typename RightType, typename MetricSpaceType, std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>), int> = 0>
    constexpr decltype(auto) cp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return cp(scalar(lhs), scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftType, typename RightType, std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>), int> = 0>
    constexpr decltype(auto) cp(LeftType const &lhs, RightType const &rhs) GA_NOEXCEPT {
        return cp(scalar(lhs), scalar(rhs), detail::real_metric_space());
    }

}

#endif // __GA_EXTRA_COMMUTATOR_PRODUCT_HPP__
