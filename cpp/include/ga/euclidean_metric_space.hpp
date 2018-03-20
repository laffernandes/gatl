#ifndef __GA_EUCLIDEAN_METRIC_SPACE_HPP__
#define __GA_EUCLIDEAN_METRIC_SPACE_HPP__

namespace ga {

	template<ndims_t N>
	class euclidean_metric_space : public signed_metric_space<N, 0> {
	private:

		typedef signed_metric_space<N, 0> super;

	public:

		using entry_type = typename super::entry_type;

		template<default_bitset_t BasisBlade>
		using cincludes_basis_blade = typename super::template cincludes_basis_blade<BasisBlade>;

		template<default_bitset_t PossibleGrades>
		using cincludes_grades = typename super::template cincludes_grades<PossibleGrades>;

		template<index_t Row, index_t Col>
		using cmetric_entry = typename super::template cmetric_entry<Row, Col>;

		template<default_bitset_t BasisBlade>
		using cmetric_factor = typename super::template cmetric_factor<BasisBlade>;
	};

}

#endif // __GA_EUCLIDEAN_METRIC_SPACE_HPP__
