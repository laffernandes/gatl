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

#ifndef __GA_EXTRA_FAST_MEET_AND_JOIN_HPP__
#define __GA_EXTRA_FAST_MEET_AND_JOIN_HPP__

namespace ga {

    namespace detail {

        // Implementation of the ga::fast_join() function.
        template<ndims_t N, typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename ToleranceType>
        GA_ALWAYS_INLINE constexpr decltype(auto) _fast_join_impl(bool const extra_sign_change, clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, grade_t const grade_lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, grade_t const grade_rhs, ToleranceType const &tol) {
            using value_type = std::common_type_t<LeftCoefficientType, RightCoefficientType>;
            using largest_type = full_derived_multivector_t<default_integral_t, RightExpression>;
            using join_type = full_multivector_t<value_type, N, std::max(smallest_possible_grade_v<LeftExpression>, smallest_possible_grade_v<RightExpression>), std::min(largest_possible_grade_v<LeftExpression> + largest_possible_grade_v<RightExpression>, (grade_t)N)>;

            constexpr auto em = real_metric_space(); // Euclidean metric

            auto project_vector = [&](auto const &vector, auto const &blade, auto const &inv_blade) {
                auto [lazy, vector_, blade_, inv_blade_] = make_lazy_context_tuple(vector, blade, inv_blade);
                return lazy.eval(take_grade(lcont(lcont(vector_, inv_blade_, em), blade_, em), c<1>));
            };

            join_type join; // initialized with zeros

            if (grade_lhs == UNDETERMINED_GRADE || grade_rhs == UNDETERMINED_GRADE) {
                return join;
            }

            checked_trivial_copy(unit(lhs, em), join, tol);
            grade_t current_grade_join = grade_lhs;

            if (grade_lhs == 0 || grade_lhs == N) {
                return join;
            }

            bitset_t largest_basis_vectors = bitset_t(0);
            RightCoefficientType largest_abs_value = -1;

            std::size_t largest_index = 0, current_stored_index = 0;

            for_each_component(rhs, [&](bitset_t const basis_vectors, RightCoefficientType const &value, entry_source_t const, entry_source_t const value_source, bool &) {
                if (value_source == MAPPED_RUNTIME_DEFINED_ENTRY) {
                    //TODO Not supported yet (map)
                    throw not_implemented_error("Sorry! The use of ga::clifford_expresion<CoefficientType, Expression> with ga::associative_container_t<ValueType> is not supported yet.");
                }

                auto const abs_value = std::abs(value);
                if (largest_abs_value < abs_value) {
                    largest_basis_vectors = basis_vectors;
                    largest_abs_value = abs_value;

                    largest_index = current_stored_index;
                }
                ++current_stored_index;
            });

            largest_type largest(typename largest_type::value_storage_type{}, rhs.bitsets(), typename largest_type::map_storage_type{});
            *(largest.values().begin() + largest_index) = 1;

            auto const inv_largest = reverse(largest);

            for_each_basis_vector(largest_basis_vectors, [&](index_t const index, bool &keep_going) {
                full_vector_t<default_integral_t, N> f;
                *(f.values().begin() + (index - 1)) = 1;

                auto const next_join = op(join, unit(project_vector(f, rhs, inv_largest), em), em);

                if (!is_zero(next_join, tol)) {
                    checked_trivial_copy(unit(next_join, em), join, tol);
                    ++current_grade_join;
                    keep_going = current_grade_join <= N;
                }
            });

            if (extra_sign_change && ((grade_lhs * grade_rhs) & 1) != 0) {
                return -join;
            }
            else {
                return join;
            }
        }

    }

    // Returns the join of the given pair of blades. This function does not allow lazy evaluation. The algorithm is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename ToleranceType, typename MetricSpaceType>
    constexpr decltype(auto) fast_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol, metric_space<MetricSpaceType> const &mtr) {
        auto const tol_ = scalar(tol);
        grade_t const grade_lhs = grade(lhs, tol_);
        grade_t const grade_rhs = grade(rhs, tol_);
        return grade_lhs >= grade_rhs ? detail::_fast_join_impl<MetricSpaceType::vector_space_dimensions>(false, lhs, grade_lhs, rhs, grade_rhs, tol_) : detail::_fast_join_impl<MetricSpaceType::vector_space_dimensions>(true, rhs, grade_rhs, lhs, grade_lhs, tol_);
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType>
    constexpr decltype(auto) fast_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
        return fast_join(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), mtr);
    }

    // Returns a std::tuple<T1, T2> structure where T1 is the meet and T2 is the join of the given pair of blades. This function does not allow lazy evaluation with arguments from a lazy context. The algorithm is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename ToleranceType, typename MetricSpaceType>
    constexpr decltype(auto) fast_meet_and_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol, metric_space<MetricSpaceType> const &mtr) {
        auto const join = fast_join(lhs, rhs, scalar(tol), mtr);
        auto const meet = lcont(lcont(rhs, inv(join, detail::real_metric_space()), detail::real_metric_space()), lhs, detail::real_metric_space());
        return std::make_tuple(meet, join);
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType>
    constexpr decltype(auto) fast_meet_and_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
        return fast_meet_and_join(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), mtr);
    }

}

#endif // __GA_EXTRA_FAST_MEET_AND_JOIN_HPP__
