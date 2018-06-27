#ifndef __GA_CORE_ORTHOGONAL_METRIC_MAPPING_HPP__
#define __GA_CORE_ORTHOGONAL_METRIC_MAPPING_HPP__

namespace ga {

	namespace detail {

		// The implementation of mapping for products assuming spaces with orthogonal metric.
		template<class OrthogonalMetricSpace, class GradedProduct>
		struct orthogonal_metric_mapping {

			template<class LeftBasisBlade, class RightBasisBlade>
			struct multiply {
			private:

#pragma warning( push )
#pragma warning( disable: 4293 )
				static_assert(((possible_grades_v<LeftBasisBlade> | possible_grades_v<RightBasisBlade>) >> (OrthogonalMetricSpace::vector_space_dimensions + 1)) == default_bitset_t(0), "The possible grades exceed the number of dimensions of the vectors space.");
#pragma warning( pop )

				constexpr static default_bitset_t result_possible_grades = GradedProduct::template possible_grades_result<possible_grades_v<LeftBasisBlade>, possible_grades_v<RightBasisBlade>, OrthogonalMetricSpace::vector_space_dimensions>::value;

				typedef basis_vectors_t<LeftBasisBlade> left_basis_vectors;
				typedef basis_vectors_t<RightBasisBlade> right_basis_vectors;

				typedef bitwise_and_t<left_basis_vectors, right_basis_vectors> common_basis_vectors;
				typedef bitwise_xor_t<left_basis_vectors, right_basis_vectors> result_basis_vectors;

				typedef std::conditional_t<
					result_possible_grades == (default_bitset_t(1) << OrthogonalMetricSpace::vector_space_dimensions),
					constant_basis_blade<OrthogonalMetricSpace::basis_vectors>, // pseudoscalar
					deduce_basis_blade_t<result_possible_grades, result_basis_vectors> // something else
				> candidate_basis_blade;

				typedef std::conditional_t<
					result_possible_grades != default_bitset_t(0),
					typename GradedProduct::template are_valid_grades<count_one_bits_t<left_basis_vectors>, count_one_bits_t<right_basis_vectors>, count_one_bits_t<result_basis_vectors> >::type,
					std::false_type
				> test_type;

			public:

				typedef component_t<
					if_else_t<
						test_type,
						product_t<reordering_sign_t<left_basis_vectors, right_basis_vectors>, typename OrthogonalMetricSpace::template metric_factor<common_basis_vectors>::type, value_mapping>,
						constant_value<0>
					>,
					candidate_basis_blade
				> type;
			};
		};

	}

}

#endif // __GA_CORE_ORTHOGONAL_METRIC_MAPPING_HPP__
