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

#ifndef __GA_EXTRA_MEET_AND_JOIN_HPP__
#define __GA_EXTRA_MEET_AND_JOIN_HPP__

namespace ga {

    namespace detail {

        // Returns a std::tuple<T1, T2> structure where T1 is the meet and T2 is the join of the given pair of blades. This implementation assumes that the grade of the left-hand side argument is lower or equal to the grade of the right-hand side argument.
        template<ndims_t N, typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename ToleranceType>
        GA_ALWAYS_INLINE constexpr decltype(auto) _meet_and_join_impl(bool const extra_sign_change, clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, grade_t const grade_lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, grade_t const grade_rhs, ToleranceType const &tol) {
            using delta_type = decltype(dp(lhs, rhs, real_metric_space()));
            using value_type = std::common_type_t<LeftCoefficientType, RightCoefficientType>;
            using meet_type = full_multivector_t<value_type, N, 0, std::min(largest_possible_grade_v<LeftExpression>, largest_possible_grade_v<RightExpression>)>;
            using join_type = full_multivector_t<value_type, N, std::max(smallest_possible_grade_v<LeftExpression>, smallest_possible_grade_v<RightExpression>), N>;

            constexpr auto em = real_metric_space(); // Euclidean metric

            auto project_vector = [&](auto const &vector, auto const &blade, auto const &inv_blade) {
                auto [lazy, vector_, blade_, inv_blade_] = make_lazy_context_tuple(vector, blade, inv_blade);
                return lazy.eval(take_grade(lcont(lcont(vector_, inv_blade_, em), blade_, em), c<1>));
            };

            meet_type meet; // initialized with zeros
            join_type join; // initialized with zeros

            if (grade_lhs == UNDETERMINED_GRADE || grade_rhs == UNDETERMINED_GRADE) {
                return std::make_pair(meet, join);
            }

            auto const delta = dp(lhs, rhs, em);

            grade_t const grade_delta = grade(delta, tol);
            grade_t const grade_meet = (grade_lhs + grade_rhs - grade_delta) >> 1;
            grade_t const grade_join = (grade_lhs + grade_rhs + grade_delta) >> 1;

            if (grade_delta != (grade_lhs + grade_rhs)) {
                trivial_copy(unit_scalar_t(), meet);
                grade_t current_grade_meet = 0;

                trivial_copy(unit_pseudoscalar_t<N>(), join);
                grade_t current_grade_join = N;

                auto const dual_delta = dual(delta, unit_pseudoscalar_t<N>(), em);
                auto const inv_dual_delta = inv(dual_delta, em);
                auto const inv_lhs = inv(lhs, em);

                bitset_t largest_basis_vectors = bitset_t(0);
                value_type largest_abs_value = -1;

                for_each_component(dual_delta, [&](bitset_t const basis_vectors, value_type const &value, entry_source_t const, entry_source_t const, bool &) {
                    auto const abs_value = std::abs(value);
                    if (largest_abs_value < abs_value) {
                        largest_basis_vectors = basis_vectors;
                        largest_abs_value = abs_value;
                    }
                });

                for_each_basis_vector(largest_basis_vectors, [&](index_t const index, bool &keep_going) {
                    full_vector_t<default_integral_t, N> f;
                    *(f.values().begin() + (index - 1)) = 1;

                    auto const d = project_vector(f, dual_delta, inv_dual_delta); // dual delta factor

                    auto const p = project_vector(d, lhs, inv_lhs); // projection
                    if (!is_zero(p, tol)) {
                        checked_trivial_copy(op(meet, p, em), meet, tol);
                        ++current_grade_meet;
                        if (current_grade_meet == grade_meet) {
                            trivial_copy(op(rcont(lhs, inv(meet, em), em), rhs, em), join);
                            keep_going = false;
                            return;
                        }
                    }

                    auto const r = d - p; // rejection
                    if (!is_zero(r, tol)) {
                        checked_trivial_copy(lcont(r, join, em), join, tol);
                        --current_grade_join;
                        if (current_grade_join == grade_join) {
                            trivial_copy(lcont(lcont(rhs, inv(join, em), em), lhs, em), meet);
                            keep_going = false;
                            return;
                        }
                    }
                });
            }
            else {
                trivial_copy(unit_scalar_t(), meet);
                checked_trivial_copy(delta, join, tol);
            }

            if (extra_sign_change && (((grade_join - grade_lhs) * (grade_join - grade_rhs)) & 1) != 0) {
                return std::make_pair(-meet, -join);
            }
            else {
                return std::make_pair(meet, join);
            }
        }

    }

    // Returns a std::tuple<T1, T2> structure where T1 is the meet and T2 is the join of the given pair of blades. This function does not allow lazy evaluation with arguments from a lazy context.
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename ToleranceType, typename MetricSpaceType>
    constexpr decltype(auto) meet_and_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol, metric_space<MetricSpaceType> const &mtr) {
        auto const tol_ = scalar(tol);
        grade_t const grade_lhs = grade(lhs, tol_);
        grade_t const grade_rhs = grade(rhs, tol_);
        return grade_lhs <= grade_rhs ? detail::_meet_and_join_impl<MetricSpaceType::vector_space_dimensions>(false, lhs, grade_lhs, rhs, grade_rhs, tol_) : detail::_meet_and_join_impl<MetricSpaceType::vector_space_dimensions>(true, rhs, grade_rhs, lhs, grade_lhs, tol_);
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType>
    constexpr decltype(auto) meet_and_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
        return meet_and_join(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), mtr);
    }

}

#endif // __GA_EXTRA_MEET_AND_JOIN_HPP__
