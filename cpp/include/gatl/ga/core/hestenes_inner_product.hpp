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

#ifndef __GA_CORE_HESTENES_INNER_PRODUCT_HPP__
#define __GA_CORE_HESTENES_INNER_PRODUCT_HPP__

namespace ga {

    namespace detail {

        struct hip_mapping {
        private:

            template<bitset_t LeftPossibleGrades, bitset_t RightPossibleGrades>
            struct _possible_grades_result {
            private:

                constexpr static bitset_t left_grade_bitset = rightmost_set_bit(LeftPossibleGrades);
                constexpr static bitset_t possible_grades = RightPossibleGrades / left_grade_bitset;

            public:

                constexpr static bitset_t value = _possible_grades_result<(possible_grades != bitset_t(0) ? LeftPossibleGrades ^ left_grade_bitset : bitset_t(0)), RightPossibleGrades>::value | possible_grades;
            };

            template<bitset_t RightPossibleGrades>
            struct _possible_grades_result<bitset_t(0), RightPossibleGrades> {
                constexpr static bitset_t value = bitset_t(0);
            };

        public:

            template<typename LeftGrade, typename RightGrade, typename ResultGrade>
            struct are_valid_grades {
                using type = if_else_t<
                    logical_or_t<equal_t<LeftGrade, constant_value<0> >, equal_t<RightGrade, constant_value<0> > >,
                    std::false_type,
                    if_else_t<
                        less_or_equal_t<LeftGrade, RightGrade>,
                        equal_t<ResultGrade, addition_t<RightGrade, product_t<constant_value<-1>, LeftGrade, value_mapping> > >,
                        equal_t<ResultGrade, addition_t<LeftGrade, product_t<constant_value<-1>, RightGrade, value_mapping> > >
                    >
                >;
            };

            template<bitset_t LeftPossibleGrades, bitset_t RightPossibleGrades, ndims_t VectorSpaceDimensions>
            struct possible_grades_result {
            private:

                constexpr static bitset_t left_possible_grades = (LeftPossibleGrades | bitset_t(1)) ^ bitset_t(1);
                constexpr static bitset_t right_possible_grades = (RightPossibleGrades | bitset_t(1)) ^ bitset_t(1);

            public:

                constexpr static bitset_t value = _possible_grades_result<left_possible_grades, right_possible_grades>::value | _possible_grades_result<right_possible_grades, left_possible_grades>::value;
            };
        };

    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType>
    constexpr decltype(auto) hip(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) GA_NOEXCEPT {
        auto lazy = make_lazy_context(lhs, rhs);
        return lazy.eval(clifford_expression<default_integral_t, detail::product_t<typename decltype(lazy)::template argument_expression_t<0>, typename decltype(lazy)::template argument_expression_t<1>, detail::metric_space_mapping_t<MetricSpaceType, detail::hip_mapping> > >());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) hip(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) GA_NOEXCEPT {
        return hip(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) hip(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) GA_NOEXCEPT {
        return hip(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) hip(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) GA_NOEXCEPT {
        return hip(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<RightType>, int> = 0>
    constexpr decltype(auto) hip(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return hip(lhs, scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, std::enable_if_t<!is_clifford_expression_v<RightType>, int> = 0>
    constexpr decltype(auto) hip(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) GA_NOEXCEPT {
        return hip(lhs, scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<LeftType>, int> = 0>
    constexpr decltype(auto) hip(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return hip(scalar(lhs), rhs, detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, std::enable_if_t<!is_clifford_expression_v<LeftType>, int> = 0>
    constexpr decltype(auto) hip(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) GA_NOEXCEPT {
        return hip(scalar(lhs), rhs, detail::real_metric_space());
    }

    template<typename LeftType, typename RightType, typename MetricSpaceType, std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>), int> = 0>
    constexpr decltype(auto) hip(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return hip(scalar(lhs), scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftType, typename RightType, std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>), int> = 0>
    constexpr decltype(auto) hip(LeftType const &lhs, RightType const &rhs) GA_NOEXCEPT {
        return hip(scalar(lhs), scalar(rhs), detail::real_metric_space());
    }

}

#endif // __GA_CORE_HESTENES_INNER_PRODUCT_HPP__
