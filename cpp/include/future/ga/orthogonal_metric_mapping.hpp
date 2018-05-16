#ifndef __FUTURE_GA_ORTHOGONAL_METRIC_MAPPING_HPP__
#define __FUTURE_GA_ORTHOGONAL_METRIC_MAPPING_HPP__

namespace ga {

	namespace detail {

		// The implementation of mapping for spaces with orthogonal metric (it is used with basis blades).
		template<class LeftBasisBlade, class RightBasisBlade, default_bitset_t PossibleGradesResult>
		struct _orthogonal_metric_deduce_basis_blade {
			typedef dynamic_basis_blade<PossibleGradesResult, lazy_bitwise_xor_t<basis_vectors_t<LeftBasisBlade>, basis_vectors_t<RightBasisBlade> > > type;
		};
		
		template<default_bitset_t LeftBasisVectors, default_bitset_t RightBasisVectors, default_bitset_t PossibleGradesResult>
		struct _orthogonal_metric_deduce_basis_blade<constant_basis_blade<LeftBasisVectors>, constant_basis_blade<RightBasisVectors>, PossibleGradesResult> {
			typedef constant_basis_blade<LeftBasisVectors ^ RightBasisVectors> type;
		};

		template<class LeftBasisBlade, class RightBasisBlade>
		struct _orthogonal_metric_deduce_basis_blade<LeftBasisBlade, RightBasisBlade, default_bitset_t(0)> {
			typedef constant_basis_blade<default_bitset_t(0)> type;
		};

		template<default_bitset_t LeftBasisVectors, default_bitset_t RightBasisVectors>
		struct _orthogonal_metric_deduce_basis_blade<constant_basis_blade<LeftBasisVectors>, constant_basis_blade<RightBasisVectors>, default_bitset_t(0)> {
			typedef constant_basis_blade<default_bitset_t(0)> type;
		};

		template<class OrthogonalMetricSpace, class GradedProduct>
		struct orthogonal_metric_space_mapping {

			template<class LeftBasisBlade, class RightBasisBlade>
			struct multiply {
			private:

				typedef typename _orthogonal_metric_deduce_basis_blade<LeftBasisBlade, RightBasisBlade, GradedProduct::template possible_grades_result<possible_grades_v<LeftBasisBlade>, possible_grades_v<RightBasisBlade>, OrthogonalMetricSpace::vector_space_dimensions>::value>::type result_basis_blade;

				typedef basis_vectors_t<LeftBasisBlade> left_basis_vectors;
				typedef basis_vectors_t<RightBasisBlade> right_basis_vectors;

				typedef basis_vectors_t<result_basis_blade> result_basis_vectors;
				typedef lazy_bitwise_and_t<left_basis_vectors, right_basis_vectors> common_basis_vectors;

				typedef typename GradedProduct::template lazy_are_valid_grades<lazy_ones_t<left_basis_vectors>, lazy_ones_t<right_basis_vectors>, lazy_ones_t<result_basis_vectors> >::type test_type;

			public:

				typedef lazy_if_else_t<
					test_type,
					product_t<lazy_reordering_sign_t<left_basis_vectors, right_basis_vectors>, typename OrthogonalMetricSpace::template lazy_metric_factor<common_basis_vectors>::type, real_mapping>,
					constant_value<0>
				> coefficient_type;

				typedef lazy_if_else_t<
					test_type,
					result_basis_blade,
					constant_basis_blade<default_bitset_t(0)>
				> basis_blade_type;
			};
		};

	}

}

#endif // __FUTURE_GA_ORTHOGONAL_METRIC_MAPPING_HPP__
