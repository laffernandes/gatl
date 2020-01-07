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

#ifndef __GA_CORE_EXTERIOR_PRODUCT_MAPPING__
#define __GA_CORE_EXTERIOR_PRODUCT_MAPPING__

namespace ga {

    namespace detail {

        // The implementation of the mapping concept for the exterior product.
        template<ndims_t VectorSpaceDimensions>
        struct exterior_product_mapping {
        private:

            constexpr static bitset_t all_possible_grades = safe_rshift(bitset_t(~0), std::numeric_limits<bitset_t>::digits - (VectorSpaceDimensions + 1));
            constexpr static bitset_t basis_vectors = all_possible_grades >> 1;

            template<bitset_t LeftPossibleGrades, bitset_t RightPossibleGrades>
            struct possible_grades_result {
            private:

                constexpr static bitset_t left_grade_bitset = rightmost_set_bit(LeftPossibleGrades);
                constexpr static bitset_t possible_grades = (left_grade_bitset * RightPossibleGrades) & all_possible_grades;

            public:

                constexpr static bitset_t value = possible_grades_result<possible_grades != bitset_t(0) ? (LeftPossibleGrades ^ left_grade_bitset) : bitset_t(0), RightPossibleGrades>::value | possible_grades;
            };

            template<bitset_t RightPossibleGrades>
            struct possible_grades_result<bitset_t(0), RightPossibleGrades> {
                constexpr static bitset_t value = bitset_t(0);
            };

        public:

            template<typename LeftBasisBlade, typename RightBasisBlade>
            struct multiply {
            private:

                static_assert(safe_rshift(possible_grades_v<LeftBasisBlade> | possible_grades_v<RightBasisBlade>, VectorSpaceDimensions + 1) == bitset_t(0), "The possible grades exceed the number of dimensions of the vectors space.");

                constexpr static bitset_t result_possible_grades = possible_grades_result<possible_grades_v<LeftBasisBlade>, possible_grades_v<RightBasisBlade> >::value;

                using left_basis_vectors = basis_vectors_t<LeftBasisBlade>;
                using right_basis_vectors = basis_vectors_t<RightBasisBlade>;
                using result_basis_vectors = bitwise_or_t<left_basis_vectors, right_basis_vectors>;

                using candidate_basis_blade = std::conditional_t<
                    result_possible_grades == (bitset_t(1) << VectorSpaceDimensions),
                    constant_basis_blade<basis_vectors>, // pseudoscalar
                    deduce_basis_blade_t<result_possible_grades, result_basis_vectors> // something else
                >;

                using test_type = std::conditional_t<
                    result_possible_grades != bitset_t(0),
                    equal_t<addition_t<count_one_bits_t<left_basis_vectors>, count_one_bits_t<right_basis_vectors> >, count_one_bits_t<result_basis_vectors> >,
                    std::false_type
                >;

            public:

                using type = component_t<
                    if_else_t<
                        test_type,
                        reordering_sign_t<left_basis_vectors, right_basis_vectors>,
                        constant_value<0>
                    >,
                    candidate_basis_blade
                >;
            };
        };

    }

}

#endif // __GA_CORE_EXTERIOR_PRODUCT_MAPPING__
