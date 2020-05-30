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

#ifndef __GA_EXTRA_DELTA_PRODUCT_HPP__
#define __GA_EXTRA_DELTA_PRODUCT_HPP__

namespace ga {

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename ToleranceType, typename MetricSpaceType>
    constexpr decltype(auto) dp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol, metric_space<MetricSpaceType> const &mtr) GA_NOEXCEPT {
        auto [lazy, lhs_, rhs_, tol_] = make_lazy_context_tuple(lhs, rhs, scalar(tol));
        return lazy.eval(take_largest_grade(gp(lhs_, rhs_, mtr), tol_));
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightExpression, typename ToleranceType, std::enable_if_t<!is_metric_space_v<ToleranceType>, int> = 0>
    constexpr decltype(auto) dp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol) GA_NOEXCEPT {
        return dp(lhs, rhs, tol, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightCoefficient, typename ToleranceType, std::enable_if_t<!is_metric_space_v<ToleranceType>, int> = 0>
    constexpr decltype(auto) dp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs, ToleranceType const &tol) GA_NOEXCEPT {
        return dp(lhs, rhs, tol, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient, typename ToleranceType, std::enable_if_t<!is_metric_space_v<ToleranceType>, int> = 0>
    constexpr decltype(auto) dp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs, ToleranceType const &tol) GA_NOEXCEPT {
        return dp(lhs, rhs, tol, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename ToleranceType, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<RightType>, int> = 0>
    constexpr decltype(auto) dp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, ToleranceType const &tol, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return dp(lhs, scalar(rhs), tol, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename ToleranceType, std::enable_if_t<!(is_clifford_expression_v<RightType> || is_metric_space_v<ToleranceType>), int> = 0>
    constexpr decltype(auto) dp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, ToleranceType const &tol) GA_NOEXCEPT {
        return dp(lhs, scalar(rhs), tol, detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename ToleranceType, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<LeftType>, int> = 0>
    constexpr decltype(auto) dp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return dp(scalar(lhs), rhs, tol, detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename ToleranceType, std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_metric_space_v<ToleranceType>), int> = 0>
    constexpr decltype(auto) dp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol) GA_NOEXCEPT {
        return dp(scalar(lhs), rhs, tol, detail::real_metric_space());
    }

    template<typename LeftType, typename RightType, typename ToleranceType, typename MetricSpaceType, std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>), int> = 0>
    constexpr decltype(auto) dp(LeftType const &lhs, RightType const &rhs, ToleranceType const &tol, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return dp(scalar(lhs), scalar(rhs), tol, detail::real_metric_space());
    }

    template<typename LeftType, typename RightType, typename ToleranceType, std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType> || is_metric_space_v<ToleranceType>), int> = 0>
    constexpr decltype(auto) dp(LeftType const &lhs, RightType const &rhs, ToleranceType const &tol) GA_NOEXCEPT {
        return dp(scalar(lhs), scalar(rhs), tol, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType>
    constexpr decltype(auto) dp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) GA_NOEXCEPT {
        return dp(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), mtr);
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) dp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) GA_NOEXCEPT {
        return dp(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) dp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) GA_NOEXCEPT {
        return dp(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) dp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) GA_NOEXCEPT {
        return dp(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<RightType> > = 0>
    constexpr decltype(auto) dp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return dp(lhs, scalar(rhs), default_tolerance<std::common_type_t<LeftCoefficientType, RightType> >(), detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, std::enable_if_t<!is_clifford_expression_v<RightType>, int> = 0>
    constexpr decltype(auto) dp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) GA_NOEXCEPT {
        return dp(lhs, scalar(rhs), default_tolerance<std::common_type_t<LeftCoefficientType, RightType> >(), detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<LeftType>, int> = 0>
    constexpr decltype(auto) dp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return dp(scalar(lhs), rhs, default_tolerance<std::common_type_t<LeftType, RightCoefficientType> >(), detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, std::enable_if_t<!is_clifford_expression_v<LeftType>, int> = 0>
    constexpr decltype(auto) dp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) GA_NOEXCEPT {
        return dp(scalar(lhs), rhs, default_tolerance<std::common_type_t<LeftType, RightCoefficientType> >(), detail::real_metric_space());
    }

    template<typename LeftType, typename RightType, typename MetricSpaceType, std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>), int> = 0>
    constexpr decltype(auto) dp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return dp(scalar(lhs), scalar(rhs), default_tolerance<std::common_type_t<LeftType, RightType> >(), detail::real_metric_space());
    }

    template<typename LeftType, typename RightType, std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>), int> = 0>
    constexpr decltype(auto) dp(LeftType const &lhs, RightType const &rhs) GA_NOEXCEPT {
        return dp(scalar(lhs), scalar(rhs), default_tolerance<std::common_type_t<LeftType, RightType> >(), detail::real_metric_space());
    }

}

#endif // __GA_EXTRA_DELTA_PRODUCT_HPP__
