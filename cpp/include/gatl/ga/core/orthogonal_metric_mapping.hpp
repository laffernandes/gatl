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

#ifndef __GA_CORE_ORTHOGONAL_METRIC_MAPPING_HPP__
#define __GA_CORE_ORTHOGONAL_METRIC_MAPPING_HPP__

namespace ga {

    namespace detail {

        // The implementation of mapping for products assuming spaces with orthogonal metric.
        template<typename OrthogonalMetricSpace, typename GradedProduct>
        struct orthogonal_metric_mapping {

            template<typename LeftBasisBlade, typename RightBasisBlade>
            struct multiply {
            private:

                static_assert(safe_rshift(possible_grades_v<LeftBasisBlade> | possible_grades_v<RightBasisBlade>, OrthogonalMetricSpace::vector_space_dimensions + 1) == bitset_t(0), "The possible grades exceed the number of dimensions of the vectors space.");

                constexpr static bitset_t result_possible_grades = GradedProduct::template possible_grades_result<possible_grades_v<LeftBasisBlade>, possible_grades_v<RightBasisBlade>, OrthogonalMetricSpace::vector_space_dimensions>::value;

                using left_basis_vectors = basis_vectors_t<LeftBasisBlade>;
                using right_basis_vectors = basis_vectors_t<RightBasisBlade>;

                using common_basis_vectors = bitwise_and_t<left_basis_vectors, right_basis_vectors>;
                using result_basis_vectors = bitwise_xor_t<left_basis_vectors, right_basis_vectors>;

                using candidate_basis_blade = std::conditional_t<
                    result_possible_grades == (bitset_t(1) << OrthogonalMetricSpace::vector_space_dimensions),
                    constant_basis_blade<OrthogonalMetricSpace::basis_vectors>, // pseudoscalar
                    deduce_basis_blade_t<result_possible_grades, result_basis_vectors> // something else
                >;

                using test_type = std::conditional_t<
                    result_possible_grades != bitset_t(0),
                    typename GradedProduct::template are_valid_grades<count_one_bits_t<left_basis_vectors>, count_one_bits_t<right_basis_vectors>, count_one_bits_t<result_basis_vectors> >::type,
                    std::false_type
                >;

            public:

                using type = component_t<
                    if_else_t<
                        test_type,
                        product_t<reordering_sign_t<left_basis_vectors, right_basis_vectors>, typename OrthogonalMetricSpace::template metric_factor<common_basis_vectors>::type, value_mapping>,
                        constant_value<0>
                    >,
                    candidate_basis_blade
                >;
            };
        };

    }

}

#endif // __GA_CORE_ORTHOGONAL_METRIC_MAPPING_HPP__
