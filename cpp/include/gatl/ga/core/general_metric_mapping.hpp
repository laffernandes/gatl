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

#ifndef __GA_CORE_GENERAL_METRIC_MAPPING_HPP__
#define __GA_CORE_GENERAL_METRIC_MAPPING_HPP__

namespace ga {

    namespace detail {

        // Returns the determinant of a square submatrix of the metric matrix induced by the general metric of the space.
        template<typename GeneralMetricSpace, typename RowBasisVectors, typename ColumnBasisVectors, ndims_t N>
        struct determinant;

        template<typename GeneralMetricSpace, typename RowBasisVectors, typename ColumnBasisVectors, ndims_t N>
        using determinant_t = typename determinant<GeneralMetricSpace, RowBasisVectors, ColumnBasisVectors, N>::type;

        template<typename GeneralMetricSpace, typename RowBasisVectors, typename ColumnBasisVectors, ndims_t N>
        struct determinant {
        private:

            using row1_basis_vector = rightmost_one_t<RowBasisVectors>;
            using other_rows_basis_vectors = bitwise_xor_t<RowBasisVectors, row1_basis_vector>;
            using row1 = addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<row1_basis_vector> > >;

            template<index_t ColumnIndex, typename _Dummy = void>
            struct sum {
            private:

                using coli_basis_vector = indirect_element_bitset_t<ColumnBasisVectors, ColumnIndex - 1>;
                using coli = addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<coli_basis_vector> > >;

            public:

                using type = addition_t<
                    typename sum<ColumnIndex - 1>::type,
                    product_t<
                        product_t<
                            std::conditional_t<(ColumnIndex & 1) == 0, constant_value<-1>, constant_value<1> >,
                            typename GeneralMetricSpace::template entry<row1, coli>::type,
                            value_mapping
                        >,
                        determinant_t<GeneralMetricSpace, other_rows_basis_vectors, bitwise_xor_t<ColumnBasisVectors, coli_basis_vector>, N - 1>,
                        value_mapping
                    >
                >;
            };

            template<typename _Dummy>
            struct sum<1, _Dummy> {
            private:

                using col1_basis_vector = rightmost_one_t<ColumnBasisVectors>;
                using col1 = addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<col1_basis_vector> > >;

            public:

                using type = product_t<
                    typename GeneralMetricSpace::template entry<row1, col1>::type,
                    determinant_t<GeneralMetricSpace, other_rows_basis_vectors, bitwise_xor_t<ColumnBasisVectors, col1_basis_vector>, N - 1>,
                    value_mapping
                >;
            };

        public:

            using type = typename sum<N>::type;
        };

        template<typename GeneralMetricSpace, typename RowBasisVectors, typename ColumnBasisVectors>
        struct determinant<GeneralMetricSpace, RowBasisVectors, ColumnBasisVectors, 2> {
        private:

            using row1_basis_vector = rightmost_one_t<RowBasisVectors>;
            using row2_basis_vector = bitwise_xor_t<RowBasisVectors, row1_basis_vector>;

            using col1_basis_vector = rightmost_one_t<ColumnBasisVectors>;
            using col2_basis_vector = bitwise_xor_t<ColumnBasisVectors, col1_basis_vector>;

            using row1 = addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<row1_basis_vector> > >;
            using row2 = addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<row2_basis_vector> > >;

            using col1 = addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<col1_basis_vector> > >;
            using col2 = addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<col2_basis_vector> > >;

            using a11 = typename GeneralMetricSpace::template entry<row1, col1>::type;
            using a12 = typename GeneralMetricSpace::template entry<row1, col2>::type;
            using a21 = typename GeneralMetricSpace::template entry<row2, col1>::type;
            using a22 = typename GeneralMetricSpace::template entry<row2, col2>::type;

        public:

            using type = addition_t<product_t<a11, a22, value_mapping>, product_t<constant_value<-1>, product_t<a21, a12, value_mapping>, value_mapping> >;
        };

        template<typename GeneralMetricSpace, typename RowBasisVectors, typename ColumnBasisVectors>
        struct determinant<GeneralMetricSpace, RowBasisVectors, ColumnBasisVectors, 1> {
        private:

            using row = addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<RowBasisVectors> > >;
            using col = addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<ColumnBasisVectors> > >;

        public:

            using type = typename GeneralMetricSpace::template entry<row, col>::type;
        };

        template<typename GeneralMetricSpace, typename RowBasisVectors, typename ColumnBasisVectors>
        struct determinant<GeneralMetricSpace, RowBasisVectors, ColumnBasisVectors, 0> {
            using type = constant_value<1>;
        };

        // The implementation of mapping for products assuming spaces with general (non-orthogonal) metric.
        template<typename GeneralMetricSpace, typename GradedProduct>
        struct general_metric_mapping {

            template<typename LeftBasisBlade, typename RightBasisBlade>
            struct multiply {
            private:

                static_assert(safe_rshift(possible_grades_v<LeftBasisBlade> | possible_grades_v<RightBasisBlade>, GeneralMetricSpace::vector_space_dimensions + 1) == bitset_t(0), "The possible grades exceed the number of dimensions of the vectors space.");

                constexpr static bitset_t candidate_possible_grades = GradedProduct::template possible_grades_result<possible_grades_v<LeftBasisBlade>, possible_grades_v<RightBasisBlade>, GeneralMetricSpace::vector_space_dimensions>::value;
                
                using left_basis_vectors = basis_vectors_t<LeftBasisBlade>;
                using right_basis_vectors = basis_vectors_t<RightBasisBlade>;

                using left_grade = count_one_bits_t<left_basis_vectors>;
                using right_grade = count_one_bits_t<right_basis_vectors>;

                // Returns the resulting component in function of the graded product.
                template<typename CandidateComponent>
                struct result_component {
                private:

                    constexpr static bitset_t possible_grades = candidate_possible_grades & possible_grades_v<basis_blade_t<CandidateComponent> >;
                    
                    using basis_blade = std::conditional_t<
                        possible_grades == (bitset_t(1) << GeneralMetricSpace::vector_space_dimensions),
                        constant_basis_blade<GeneralMetricSpace::basis_vectors>, // pseudoscalar
                        deduce_basis_blade_t<possible_grades, basis_vectors_t<basis_blade_t<CandidateComponent> > > // something else
                    >;

                    using coefficient = if_else_t<
                        std::conditional_t<
                            possible_grades != bitset_t(0),
                            typename GradedProduct::template are_valid_grades<left_grade, right_grade, count_one_bits_t<basis_vectors_t<basis_blade> > >::type,
                            std::false_type
                        >,
                        coefficient_t<CandidateComponent>,
                        constant_value<0>
                    >;

                public:

                    using type = component_t<coefficient, basis_blade>;
                };

                template<typename CandidateComponent>
                using result_component_t = typename result_component<CandidateComponent>::type;

                // Summation indexed by the combination of k basis vectors used to index (indirectly) the rows of the metric matrix on the evaluation of the interior product.
                template<bitset_t ColumnBasisVectors, bitset_t IndirectRowBasisVectors>
                struct indirect_rows_summation;

                template<bitset_t ColumnBasisVectors, bitset_t IndirectRowBasisVectors>
                using indirect_rows_summation_t = typename indirect_rows_summation<ColumnBasisVectors, IndirectRowBasisVectors>::type;

                template<bitset_t ColumnBasisVectors, bitset_t IndirectRowBasisVectors>
                struct indirect_rows_summation {
                private:

                    constexpr static default_integral_t order = ones(ColumnBasisVectors);

                    using row_basis_vectors = indirect_subset_t<right_basis_vectors, IndirectRowBasisVectors>;
                    using row_basis_vectors_complement = bitwise_xor_t<right_basis_vectors, row_basis_vectors>;

                    using column_basis_vectors = constant_bitset<ColumnBasisVectors>;

                    using candidate_component = product_t<
                        product_t<
                            component_t<if_else_t<logical_and_t<less_or_equal_t<constant_value<order>, left_grade>, less_or_equal_t<constant_value<order>, right_grade> >, constant_value<1>, constant_value<0> >, LeftBasisBlade>,
                            component_t<determinant_t<GeneralMetricSpace, row_basis_vectors, column_basis_vectors, order>, constant_basis_blade<ColumnBasisVectors ^ GeneralMetricSpace::basis_vectors> >,
                            regressive_product_mapping<GeneralMetricSpace::vector_space_dimensions>
                        >,
                        component_t<reordering_sign_t<row_basis_vectors, row_basis_vectors_complement>, deduce_basis_blade_t<safe_rshift(possible_grades_v<RightBasisBlade>, order), row_basis_vectors_complement> >,
                        exterior_product_mapping<GeneralMetricSpace::vector_space_dimensions>
                    >;

                public:

                    using type = addition_t<
                        result_component_t<candidate_component>,
                        indirect_rows_summation_t<ColumnBasisVectors, next_combination(IndirectRowBasisVectors, leftmost_set_bit(possible_grades_v<RightBasisBlade>) - bitset_t(1))>
                    >;
                };

                template<bitset_t ColumnBasisVectors>
                struct indirect_rows_summation<ColumnBasisVectors, bitset_t(0)> {
                    using type = component_t<constant_value<0>, constant_basis_blade<bitset_t(0)> >;
                };

                // Summation indexed by the combination of k basis vectors used to index the columns of the metric matrix on the evaluation of the interior product.
                template<bitset_t ColumnBasisVectors, typename _Dummy = void>
                struct columns_summation;
                
                template<bitset_t ColumnBasisVectors>
                using columns_summation_t = typename columns_summation<ColumnBasisVectors>::type;

                template<bitset_t ColumnBasisVectors, typename _Dummy>
                struct columns_summation {
                    using type = addition_t<
                        product_t<
                            component_t<std::conditional_t<(ones(ColumnBasisVectors & (bitset_t)0x5555555555555555ull) & 1) == 0, constant_value<1>, constant_value<-1> >, constant_basis_blade<bitset_t(0)> >,
                            indirect_rows_summation_t<ColumnBasisVectors, first_combination(ones(ColumnBasisVectors))>,
                            exterior_product_mapping<GeneralMetricSpace::vector_space_dimensions>
                        >,
                        columns_summation_t<next_combination(ColumnBasisVectors, GeneralMetricSpace::basis_vectors)>
                    >;
                };

                template<typename _Dummy>
                struct columns_summation<bitset_t(0), _Dummy> {
                    using type = component_t<constant_value<0>, constant_basis_blade<bitset_t(0)> >;
                };

                // Summation indexed by the order of the generalized Grassmann product. It is actually the Clifford product of two scaled basis blades.
                template<default_integral_t Order, typename _Dummy = void>
                struct order_summation;

                template<default_integral_t Order>
                using order_summation_t = typename order_summation<Order>::type;

                template<default_integral_t Order, typename _Dummy>
                struct order_summation {
                    using type = addition_t<
                        order_summation_t<Order - 1>,
                        product_t<
                            component_t<
                                if_else_t<
                                    equal_t<
                                        bitwise_and_t<
                                            addition_t<constant_value<-2 * Order>, product_t<constant_value<Order>, left_grade, value_mapping> >,
                                            constant_value<1>
                                        >,
                                        constant_value<0>
                                    >,
                                    constant_value<1>,
                                    constant_value<-1>
                                >,
                                constant_basis_blade<bitset_t(0)>
                            >,
                            columns_summation_t<first_combination(Order)>,
                            exterior_product_mapping<GeneralMetricSpace::vector_space_dimensions>
                        >
                    >;
                };

                template<typename _Dummy>
                struct order_summation<0, _Dummy> {
                    using type = result_component_t<
                        product_t<
                            product_t<
                                component_t<constant_value<1>, LeftBasisBlade>,
                                component_t<constant_value<1>, constant_basis_blade<GeneralMetricSpace::basis_vectors> >,
                                regressive_product_mapping<GeneralMetricSpace::vector_space_dimensions>
                            >,
                            component_t<constant_value<1>, RightBasisBlade>,
                            exterior_product_mapping<GeneralMetricSpace::vector_space_dimensions>
                        >
                    >;
                };

            public:

                using type = order_summation_t<std::min(set_bit_index(leftmost_set_bit(possible_grades_v<LeftBasisBlade>)), set_bit_index(leftmost_set_bit(possible_grades_v<RightBasisBlade>)))>;
            };
        };

    }

}

#endif // __GA_CORE_GENRAL_METRIC_MAPPING_HPP__
