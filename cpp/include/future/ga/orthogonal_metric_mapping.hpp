#ifndef __FUTURE_GA_ORTHOGONAL_METRIC_MAPPING_HPP__
#define __FUTURE_GA_ORTHOGONAL_METRIC_MAPPING_HPP__

namespace ga {

	namespace detail {

		// The implementation of mapping for products assuming spaces with orthogonal metric.
		template<default_bitset_t PossibleGrades, class BasisVectors>
		struct _orthogonal_metric_deduce_basis_blade {
			typedef dynamic_basis_blade_t<PossibleGrades, BasisVectors> type;
		};
		
		template<default_bitset_t PossibleGrades, default_bitset_t BasisVectors>
		struct _orthogonal_metric_deduce_basis_blade<PossibleGrades, constant_bitset<BasisVectors> > {
			typedef constant_basis_blade<BasisVectors> type;
		};

		template<class OrthogonalMetricSpace, class GradedProduct>
		struct orthogonal_metric_space_mapping {

			template<class LeftBasisBlade, class RightBasisBlade>
			struct multiply {
			private:

				constexpr static default_bitset_t result_possible_grades = GradedProduct::template possible_grades_result<possible_grades_v<LeftBasisBlade>, possible_grades_v<RightBasisBlade>, OrthogonalMetricSpace::vector_space_dimensions>::value;

				typedef basis_vectors_t<LeftBasisBlade> left_basis_vectors;
				typedef basis_vectors_t<RightBasisBlade> right_basis_vectors;

				typedef bitwise_and_t<left_basis_vectors, right_basis_vectors> common_basis_vectors;
				typedef bitwise_xor_t<left_basis_vectors, right_basis_vectors> result_basis_vectors;

				typedef std::conditional_t<
					result_possible_grades == (default_bitset_t(1) << OrthogonalMetricSpace::vector_space_dimensions),
					constant_basis_blade<OrthogonalMetricSpace::basis_vectors>, // pseudoscalar
					typename _orthogonal_metric_deduce_basis_blade<result_possible_grades, result_basis_vectors>::type // something else
				> candidate_basis_blade;

				typedef std::conditional_t<
					result_possible_grades != default_bitset_t(0),
					typename GradedProduct::template are_valid_grades<count_one_bits_t<left_basis_vectors>, count_one_bits_t<right_basis_vectors>, count_one_bits_t<result_basis_vectors> >::type,
					std::false_type
				> test_type;

				//TODO reordering_sign_t poderia ser otimizado em função do possible_grades_t caso left_basis_vectors == right_basis_vectors

			public:

				typedef if_else_t<
					test_type,
					product_t<reordering_sign_t<left_basis_vectors, right_basis_vectors>, typename OrthogonalMetricSpace::template metric_factor<common_basis_vectors>::type, real_mapping>,
					constant_value<0>
				> coefficient_type;

				typedef candidate_basis_blade basis_blade_type;
			};
		};

	}

}

#endif // __FUTURE_GA_ORTHOGONAL_METRIC_MAPPING_HPP__
