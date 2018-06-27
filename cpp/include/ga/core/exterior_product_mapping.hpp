#ifndef __GA_CORE_EXTERIOR_PRODUCT_MAPPING__
#define __GA_CORE_EXTERIOR_PRODUCT_MAPPING__

namespace ga {

	namespace detail {

		// The implementation of the mapping concept for the exterior product.
		template<ndims_t VectorSpaceDimensions>
		struct exterior_product_mapping {
		private:

			constexpr static default_bitset_t all_possible_grades = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (VectorSpaceDimensions + 1)));
			constexpr static default_bitset_t basis_vectors = all_possible_grades >> 1;

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct possible_grades_result {
			private:

				constexpr static default_bitset_t left_grade_bitset = rightmost_set_bit(LeftPossibleGrades);
				constexpr static default_bitset_t possible_grades = (left_grade_bitset * RightPossibleGrades) & all_possible_grades;

			public:

				constexpr static default_bitset_t value = possible_grades_result<possible_grades != default_bitset_t(0) ? (LeftPossibleGrades ^ left_grade_bitset) : default_bitset_t(0), RightPossibleGrades>::value | possible_grades;
			};

			template<default_bitset_t RightPossibleGrades>
			struct possible_grades_result<default_bitset_t(0), RightPossibleGrades> {
				constexpr static default_bitset_t value = default_bitset_t(0);
			};

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
				typedef bitwise_or_t<left_basis_vectors, right_basis_vectors> result_basis_vectors;

				typedef std::conditional_t<
					result_possible_grades == (default_bitset_t(1) << VectorSpaceDimensions),
					constant_basis_blade<basis_vectors>, // pseudoscalar
					deduce_basis_blade_t<result_possible_grades, result_basis_vectors> // something else
				> candidate_basis_blade;

				typedef std::conditional_t<
					result_possible_grades != default_bitset_t(0),
					equal_t<addition_t<count_one_bits_t<left_basis_vectors>, count_one_bits_t<right_basis_vectors> >, count_one_bits_t<result_basis_vectors> >,
					std::false_type
				> test_type;

			public:

				typedef component_t<
					if_else_t<
						test_type,
						reordering_sign_t<left_basis_vectors, right_basis_vectors>,
						constant_value<0>
					>,
					candidate_basis_blade
				> type;
			};
		};

	}

}

#endif // __GA_CORE_EXTERIOR_PRODUCT_MAPPING__
