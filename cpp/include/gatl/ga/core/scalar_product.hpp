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

#ifndef __GA_CORE_SCALAR_PRODUCT_HPP__
#define __GA_CORE_SCALAR_PRODUCT_HPP__

namespace ga {

    namespace detail {

        struct sp_mapping {
        public:

            template<typename LeftGrade, typename RightGrade, typename ResultGrade>
            struct are_valid_grades {
                using type = equal_t<ResultGrade, constant_value<0> >;
            };

            template<bitset_t LeftPossibleGrades, bitset_t RightPossibleGrades, ndims_t VectorSpaceDimensions>
            struct possible_grades_result {
                constexpr static bitset_t value = (LeftPossibleGrades & RightPossibleGrades) != bitset_t(0) ? bitset_t(1) : bitset_t(0);
            };
        };

    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType>
    constexpr decltype(auto) sp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) GA_NOEXCEPT {
        auto lazy = make_lazy_context(lhs, rhs);
        return lazy.eval(clifford_expression<default_integral_t, detail::product_t<typename decltype(lazy)::template argument_expression_t<0>, typename decltype(lazy)::template argument_expression_t<1>, detail::metric_space_mapping_t<MetricSpaceType, detail::sp_mapping> > >());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) sp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) GA_NOEXCEPT {
        return sp(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) sp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) GA_NOEXCEPT {
        return sp(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) sp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) GA_NOEXCEPT {
        return sp(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<RightType>, int> = 0>
    constexpr decltype(auto) sp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return sp(lhs, scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, std::enable_if_t<!is_clifford_expression_v<RightType>, int> = 0>
    constexpr decltype(auto) sp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) GA_NOEXCEPT {
        return sp(lhs, scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<LeftType>, int> = 0>
    constexpr decltype(auto) sp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return sp(scalar(lhs), rhs, detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, std::enable_if_t<!is_clifford_expression_v<LeftType>, int> = 0>
    constexpr decltype(auto) sp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) GA_NOEXCEPT {
        return sp(scalar(lhs), rhs, detail::real_metric_space());
    }

    template<typename LeftType, typename RightType, typename MetricSpaceType, std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>), int> = 0>
    constexpr decltype(auto) sp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return sp(scalar(lhs), scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftType, typename RightType, std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>), int> = 0>
    constexpr decltype(auto) sp(LeftType const &lhs, RightType const &rhs) GA_NOEXCEPT {
        return sp(scalar(lhs), scalar(rhs), detail::real_metric_space());
    }

}

#endif // __GA_CORE_SCALAR_PRODUCT_HPP__
