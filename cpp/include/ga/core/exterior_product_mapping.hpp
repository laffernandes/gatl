#ifndef __GA_CORE_EXTERIOR_PRODUCT_MAPPING__
#define __GA_CORE_EXTERIOR_PRODUCT_MAPPING__

namespace ga {

	namespace detail {

		// The implementation of the mapping concept for the exterior product.
		template<ndims_t VectorSpaceDimensions>
		struct exterior_product_mapping {
		private:

			struct _iterate_end {
				constexpr static default_bitset_t value = default_bitset_t(0);
			};

			template<grade_t LeftGrade, default_bitset_t RightPossibleGrades, grade_t RightGrade>
			struct _iterate_right {
				constexpr static default_bitset_t value = _iterate_right<
					LeftGrade,
					((LeftGrade + RightGrade + 1) < std::numeric_limits<default_bitset_t>::digits ? (RightPossibleGrades >> 1) : default_bitset_t(0)),
					RightGrade + 1
				>::value | ((RightPossibleGrades & default_bitset_t(1)) != default_bitset_t(0) ? (default_bitset_t(1) << (LeftGrade + RightGrade)) : default_bitset_t(0));
			};

			template<grade_t LeftGrade, grade_t RightGrade>
			struct _iterate_right<LeftGrade, 0, RightGrade> : _iterate_end {
			};

			template<default_bitset_t LeftPossibleGrades, grade_t LeftGrade, default_bitset_t RightPossibleGrades>
			struct _iterate_left {
				constexpr static default_bitset_t value = _iterate_left<(LeftPossibleGrades >> 1), LeftGrade + 1, RightPossibleGrades>::value | std::conditional<(LeftPossibleGrades & default_bitset_t(1)) != default_bitset_t(0), _iterate_right<LeftGrade, RightPossibleGrades, 0>, _iterate_end>::type::value;
			};

			template<grade_t LeftGrade, default_bitset_t RightPossibleGrades>
			struct _iterate_left<0, LeftGrade, RightPossibleGrades> : _iterate_end {
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimensions>
			struct possible_grades_result {
				constexpr static default_bitset_t value = _iterate_left<LeftPossibleGrades, 0, RightPossibleGrades>::value & (default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (VectorSpaceDimensions + 1)));
			};

			constexpr static default_bitset_t basis_vectors = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - VectorSpaceDimensions));

		public:

			template<class LeftBasisBlade, class RightBasisBlade>
			struct multiply {
			private:

				constexpr static default_bitset_t result_possible_grades = possible_grades_result<possible_grades_v<LeftBasisBlade>, possible_grades_v<RightBasisBlade>, VectorSpaceDimensions>::value;

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
