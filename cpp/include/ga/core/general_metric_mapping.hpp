#ifndef __GA_CORE_GENERAL_METRIC_MAPPING_HPP__
#define __GA_CORE_GENERAL_METRIC_MAPPING_HPP__

namespace ga {

	namespace detail {

		// Returns the determinant of a square submatrix of the metric matrix induced by the general metric of the space.
		template<class GeneralMetricSpace, class RowBasisVectors, class ColumnBasisVectors, ndims_t N>
		struct determinant;

		template<class GeneralMetricSpace, class RowBasisVectors, class ColumnBasisVectors, ndims_t N>
		using determinant_t = typename determinant<GeneralMetricSpace, RowBasisVectors, ColumnBasisVectors, N>::type;

		template<class GeneralMetricSpace, class RowBasisVectors, class ColumnBasisVectors, ndims_t N>
		struct determinant {
		private:

			typedef rightmost_one_t<RowBasisVectors> row1_basis_vector;
			typedef bitwise_xor_t<RowBasisVectors, row1_basis_vector> other_rows_basis_vectors;
			typedef addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<row1_basis_vector> > > row1;

			template<index_t ColumnIndex>
			struct sum {
			private:

				typedef indirect_element_bitset_t<ColumnBasisVectors, ColumnIndex - 1>  coli_basis_vector;
				typedef addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<coli_basis_vector> > > coli;

			public:

				typedef addition_t<
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
				> type;
			};

			template<>
			struct sum<1> {
			private:

				typedef rightmost_one_t<ColumnBasisVectors>  col1_basis_vector;
				typedef addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<col1_basis_vector> > > col1;

			public:

				typedef product_t<
					typename GeneralMetricSpace::template entry<row1, col1>::type,
					determinant_t<GeneralMetricSpace, other_rows_basis_vectors, bitwise_xor_t<ColumnBasisVectors, col1_basis_vector>, N - 1>,
					value_mapping
				> type;
			};

		public:

			typedef typename sum<N>::type type;
		};

		template<class GeneralMetricSpace, class RowBasisVectors, class ColumnBasisVectors>
		struct determinant<GeneralMetricSpace, RowBasisVectors, ColumnBasisVectors, 2> {
		private:

			typedef rightmost_one_t<RowBasisVectors> row1_basis_vector;
			typedef bitwise_xor_t<RowBasisVectors, row1_basis_vector> row2_basis_vector;

			typedef rightmost_one_t<ColumnBasisVectors> col1_basis_vector;
			typedef bitwise_xor_t<ColumnBasisVectors, col1_basis_vector> col2_basis_vector;

			typedef addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<row1_basis_vector> > > row1;
			typedef addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<row2_basis_vector> > > row2;

			typedef addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<col1_basis_vector> > > col1;
			typedef addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<col2_basis_vector> > > col2;

			typedef typename GeneralMetricSpace::template entry<row1, col1>::type a11;
			typedef typename GeneralMetricSpace::template entry<row1, col2>::type a12;
			typedef typename GeneralMetricSpace::template entry<row2, col1>::type a21;
			typedef typename GeneralMetricSpace::template entry<row2, col2>::type a22;

		public:

			typedef addition_t<product_t<a11, a22, value_mapping>, product_t<constant_value<-1>, product_t<a21, a12, value_mapping>, value_mapping> > type;
		};

		template<class GeneralMetricSpace, class RowBasisVectors, class ColumnBasisVectors>
		struct determinant<GeneralMetricSpace, RowBasisVectors, ColumnBasisVectors, 1> {
		private:

			typedef addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<RowBasisVectors> > > row;
			typedef addition_t<constant_value<1>, count_one_bits_t<bitwise_dec_t<ColumnBasisVectors> > > col;

		public:

			typedef typename GeneralMetricSpace::template entry<row, col>::type type;
		};

		template<class GeneralMetricSpace, class RowBasisVectors, class ColumnBasisVectors>
		struct determinant<GeneralMetricSpace, RowBasisVectors, ColumnBasisVectors, 0> {
			typedef constant_value<1> type;
		};

		// The implementation of mapping for products assuming spaces with general (non-orthogonal) metric.
		template<class GeneralMetricSpace, class GradedProduct>
		struct general_metric_mapping {

			template<class LeftBasisBlade, class RightBasisBlade>
			struct multiply {
			private:

#pragma warning( push )
#pragma warning( disable: 4293 )
				static_assert(((possible_grades_v<LeftBasisBlade> | possible_grades_v<RightBasisBlade>) >> (GeneralMetricSpace::vector_space_dimensions + 1)) == default_bitset_t(0), "The possible grades exceed the number of dimensions of the vectors space.");
#pragma warning( pop )

				constexpr static default_bitset_t candidate_possible_grades = GradedProduct::template possible_grades_result<possible_grades_v<LeftBasisBlade>, possible_grades_v<RightBasisBlade>, GeneralMetricSpace::vector_space_dimensions>::value;
				
				typedef basis_vectors_t<LeftBasisBlade> left_basis_vectors;
				typedef basis_vectors_t<RightBasisBlade> right_basis_vectors;

				typedef count_one_bits_t<left_basis_vectors> left_grade;
				typedef count_one_bits_t<right_basis_vectors> right_grade;

				// Returns the resulting component in function of the graded product.
				template<class CandidateComponent>
				struct result_component {
				private:

					constexpr static default_bitset_t possible_grades = candidate_possible_grades & possible_grades_v<basis_blade_t<CandidateComponent> >;
					
					typedef std::conditional_t<
						possible_grades == (default_bitset_t(1) << GeneralMetricSpace::vector_space_dimensions),
						constant_basis_blade<GeneralMetricSpace::basis_vectors>, // pseudoscalar
						deduce_basis_blade_t<possible_grades, basis_vectors_t<basis_blade_t<CandidateComponent> > > // something else
					> basis_blade;

					typedef if_else_t<
						std::conditional_t<
							possible_grades != default_bitset_t(0),
							typename GradedProduct::template are_valid_grades<left_grade, right_grade, count_one_bits_t<basis_vectors_t<basis_blade> > >::type,
							std::false_type
						>,
						coefficient_t<CandidateComponent>,
						constant_value<0>
					> coefficient;

				public:

					typedef component_t<coefficient, basis_blade> type;
				};

				template<class CandidateComponent>
				using result_component_t = typename result_component<CandidateComponent>::type;

				// Summation indexed by the combination of k basis vectors used to index (indirectly) the rows of the metric matrix on the evaluation of the interior product.
				template<default_bitset_t ColumnBasisVectors, default_bitset_t IndirectRowBasisVectors>
				struct indirect_rows_summation;

				template<default_bitset_t ColumnBasisVectors, default_bitset_t IndirectRowBasisVectors>
				using indirect_rows_summation_t = typename indirect_rows_summation<ColumnBasisVectors, IndirectRowBasisVectors>::type;

				template<default_bitset_t ColumnBasisVectors, default_bitset_t IndirectRowBasisVectors>
				struct indirect_rows_summation {
				private:

					constexpr static default_integral_t order = ones(ColumnBasisVectors);

					typedef indirect_subset_t<right_basis_vectors, IndirectRowBasisVectors> row_basis_vectors;
					typedef bitwise_xor_t<right_basis_vectors, row_basis_vectors> row_basis_vectors_complement;

					typedef constant_bitset<ColumnBasisVectors> column_basis_vectors;

					typedef product_t<
						product_t<
							component_t<if_else_t<logical_and_t<less_or_equal_t<constant_value<order>, left_grade>, less_or_equal_t<constant_value<order>, right_grade> >, constant_value<1>, constant_value<0> >, LeftBasisBlade>,
							component_t<determinant_t<GeneralMetricSpace, row_basis_vectors, column_basis_vectors, order>, constant_basis_blade<ColumnBasisVectors ^ GeneralMetricSpace::basis_vectors> >,
							regressive_product_mapping<GeneralMetricSpace::vector_space_dimensions>
						>,
						component_t<reordering_sign_t<row_basis_vectors, row_basis_vectors_complement>, deduce_basis_blade_t<(possible_grades_v<RightBasisBlade> >> order), row_basis_vectors_complement> >,
						exterior_product_mapping<GeneralMetricSpace::vector_space_dimensions>
					> candidate_component;

				public:

					typedef addition_t<
						result_component_t<candidate_component>,
						indirect_rows_summation_t<ColumnBasisVectors, next_combination(IndirectRowBasisVectors, leftmost_set_bit(possible_grades_v<RightBasisBlade>) - default_bitset_t(1))>
					> type;
				};

				template<default_bitset_t ColumnBasisVectors>
				struct indirect_rows_summation<ColumnBasisVectors, default_bitset_t(0)> {
					typedef component_t<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > type;
				};

				// Summation indexed by the combination of k basis vectors used to index the columns of the metric matrix on the evaluation of the interior product.
				template<default_bitset_t ColumnBasisVectors>
				struct columns_summation;
				
				template<default_bitset_t ColumnBasisVectors>
				using columns_summation_t = typename columns_summation<ColumnBasisVectors>::type;

				template<default_bitset_t ColumnBasisVectors>
				struct columns_summation {
					typedef addition_t<
						product_t<
							component_t<std::conditional_t<(ones(ColumnBasisVectors & (default_bitset_t)0x5555555555555555ull) & 1) == 0, constant_value<1>, constant_value<-1> >, constant_basis_blade<default_bitset_t(0)> >,
							indirect_rows_summation_t<ColumnBasisVectors, first_combination(ones(ColumnBasisVectors))>,
							exterior_product_mapping<GeneralMetricSpace::vector_space_dimensions>
						>,
						columns_summation_t<next_combination(ColumnBasisVectors, GeneralMetricSpace::basis_vectors)>
					> type;
				};

				template<>
				struct columns_summation<default_bitset_t(0)> {
					typedef component_t<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > type;
				};

				// Summation indexed by the order of the generalized Grassmann product. It is actually the Clifford product of two scaled basis blades.
				template<default_integral_t Order>
				struct order_summation;

				template<default_integral_t Order>
				using order_summation_t = typename order_summation<Order>::type;

				template<default_integral_t Order>
				struct order_summation {
					typedef addition_t<
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
								constant_basis_blade<default_bitset_t(0)>
							>,
							columns_summation_t<first_combination(Order)>,
							exterior_product_mapping<GeneralMetricSpace::vector_space_dimensions>
						>
					> type;
				};

				template<>
				struct order_summation<0> {
					typedef result_component_t<
						product_t<
							product_t<
								component_t<constant_value<1>, LeftBasisBlade>,
								component_t<constant_value<1>, constant_basis_blade<GeneralMetricSpace::basis_vectors> >,
								regressive_product_mapping<GeneralMetricSpace::vector_space_dimensions>
							>,
							component_t<constant_value<1>, RightBasisBlade>,
							exterior_product_mapping<GeneralMetricSpace::vector_space_dimensions>
						>
					> type;
				};

			public:

				typedef order_summation_t<smaller(set_bit_index(leftmost_set_bit(possible_grades_v<LeftBasisBlade>)), set_bit_index(leftmost_set_bit(possible_grades_v<RightBasisBlade>)))> type;
			};
		};

	}

}

#endif // __GA_CORE_GENRAL_METRIC_MAPPING_HPP__
