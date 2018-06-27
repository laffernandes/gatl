#ifndef __GA_CORE_REGRESSIVE_PRODUCT_MAPPING__
#define __GA_CORE_REGRESSIVE_PRODUCT_MAPPING__

namespace ga {

	namespace detail {

		//TODO É possível melhorar?

		// The implementation of the mapping concept for the regressive product.
		template<ndims_t VectorSpaceDimensions>
		struct regressive_product_mapping {
		private:

			template<grade_t LeftGrade, grade_t RightGrade>
			struct resulting_bitset {
			private:

				constexpr static grade_t result_grade = LeftGrade + RightGrade - (grade_t)VectorSpaceDimensions;

			public:

				constexpr static default_bitset_t value = (0 <= result_grade && result_grade <= VectorSpaceDimensions) ? (default_bitset_t(1) << result_grade) : default_bitset_t(0);
			};

			template<grade_t LeftGrade, default_bitset_t RightPossibleGrades>
			struct iterate_right {
			private:

				constexpr static default_bitset_t right_grade_bitset = rightmost_set_bit(RightPossibleGrades);

			public:

				constexpr static default_bitset_t value = iterate_right<LeftGrade, RightPossibleGrades ^ right_grade_bitset>::value | resulting_bitset<LeftGrade, set_bit_index(right_grade_bitset)>::value;
			};

			template<grade_t LeftGrade>
			struct iterate_right<LeftGrade, default_bitset_t(0)> {
				constexpr static default_bitset_t value = default_bitset_t(0);
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct possible_grades_result {
			private:

				constexpr static default_bitset_t left_grade_bitset = rightmost_set_bit(LeftPossibleGrades);
				constexpr static grade_t left_grade = set_bit_index(left_grade_bitset);
				constexpr static default_bitset_t right_possible_grades = (RightPossibleGrades >> (VectorSpaceDimensions - left_grade)) << (VectorSpaceDimensions - left_grade);

			public:

				constexpr static default_bitset_t value = possible_grades_result<LeftPossibleGrades ^ left_grade_bitset, RightPossibleGrades>::value | iterate_right<left_grade, right_possible_grades>::value;
			};

			template<default_bitset_t RightPossibleGrades>
			struct possible_grades_result<default_bitset_t(0), RightPossibleGrades> {
				constexpr static default_bitset_t value = default_bitset_t(0);
			};

			constexpr static default_bitset_t basis_vectors = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - VectorSpaceDimensions));

		public:

			template<class LeftBasisBlade, class RightBasisBlade>
			struct multiply {
			private:

#pragma warning( push )
#pragma warning( disable: 4293 )
				static_assert(((possible_grades_v<LeftBasisBlade> | possible_grades_v<RightBasisBlade>) >> (VectorSpaceDimensions + 1)) == default_bitset_t(0), "The possible grades exceed the number of dimensions of the vectors space.");
#pragma warning( pop )

				constexpr static default_bitset_t result_possible_grades = possible_grades_result<possible_grades_v<LeftBasisBlade>, possible_grades_v<RightBasisBlade> >::value;

				typedef basis_vectors_t<LeftBasisBlade> left_basis_vectors;
				typedef basis_vectors_t<RightBasisBlade> right_basis_vectors;
				typedef bitwise_and_t<left_basis_vectors, right_basis_vectors> result_basis_vectors;

				typedef std::conditional_t<
					result_possible_grades == (default_bitset_t(1) << VectorSpaceDimensions),
					constant_basis_blade<basis_vectors>, // pseudoscalar
					deduce_basis_blade_t<result_possible_grades, result_basis_vectors> // something else
				> candidate_basis_blade;

				typedef std::conditional_t<
					result_possible_grades != default_bitset_t(0),
					equal_t<addition_t<addition_t<count_one_bits_t<left_basis_vectors>, count_one_bits_t<right_basis_vectors> >, product_t<constant_value<-1>, count_one_bits_t<result_basis_vectors>, value_mapping> >, constant_value<VectorSpaceDimensions> >,
					std::false_type
				> test_type;

			public:

				typedef component_t<
					if_else_t<
						test_type,
						reordering_sign_t<bitwise_xor_t<left_basis_vectors, result_basis_vectors>, bitwise_xor_t<right_basis_vectors, result_basis_vectors> >,
						constant_value<0>
					>,
					candidate_basis_blade
				> type;
			};
		};

	}

}

#endif // __GA_CORE_REGRESSIVE_PRODUCT_MAPPING__
