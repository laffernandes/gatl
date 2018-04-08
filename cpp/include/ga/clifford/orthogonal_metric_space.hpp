#ifndef __GA_CLIFFORD_ORTHOGONAL_METRIC_SPACE_HPP__
#define __GA_CLIFFORD_ORTHOGONAL_METRIC_SPACE_HPP__

namespace ga {

	namespace clifford {

		template<class OrthogonalMetricSpaceType>
		class orthogonal_metric_space : public metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > {
		public:

			typedef typename detail::metric_space_traits<OrthogonalMetricSpaceType>::entry_type entry_type;

			template<default_bitset_t BasisBlade>
			struct cincludes_basis_blade : detail::space_traits<OrthogonalMetricSpaceType>::template cincludes_basis_blade<BasisBlade> {
			};

			template<default_bitset_t PossibleGrades>
			struct cincludes_grades : detail::space_traits<OrthogonalMetricSpaceType>::template cincludes_grades<PossibleGrades> {
			};

			template<index_t Row, index_t Col>
			struct cmetric_entry : detail::metric_space_traits<OrthogonalMetricSpaceType>::template cmetric_entry<Row, Col> {
			};

			template<default_bitset_t BasisBlade>
			struct cmetric_factor : detail::metric_space_traits<OrthogonalMetricSpaceType>::template cmetric_factor<BasisBlade> {
			};

			constexpr decltype(auto) basis_vectors() const {
				return detail::space_traits<OrthogonalMetricSpaceType>::call_basis_vectors(static_cast<OrthogonalMetricSpaceType const*>(this));
			}

			constexpr static ndims_t vector_space_dimension() {
				return detail::space_traits<OrthogonalMetricSpaceType>::call_vector_space_dimension(static_cast<OrthogonalMetricSpaceType const*>(this));
			}

			constexpr bool includes_basis_blade(default_bitset_t const arg) const {
				return detail::space_traits<OrthogonalMetricSpaceType>::call_includes_basis_blade(static_cast<OrthogonalMetricSpaceType const*>(this), arg);
			}

			constexpr decltype(auto) metric_entry(index_t const row, index_t const col) const {
				return detail::metric_space_traits<OrthogonalMetricSpaceType>::call_metric_entry(static_cast<OrthogonalMetricSpaceType const*>(this), row, col);
			}

			constexpr decltype(auto) metric_factor(default_bitset_t const arg) const {
				return detail::metric_space_traits<OrthogonalMetricSpaceType>::call_metric_factor(static_cast<OrthogonalMetricSpaceType const*>(this), arg);
			}
		};

		namespace detail {

			template<class OrthogonalMetricSpaceType>
			struct space_traits<orthogonal_metric_space<OrthogonalMetricSpaceType> > {
				template<default_bitset_t BasisBlade>
				struct cincludes_basis_blade : detail::space_traits<OrthogonalMetricSpaceType>::template cincludes_basis_blades<BasisBlade> {
				};

				template<default_bitset_t PossibleGrades>
				struct cincludes_grades : detail::space_traits<OrthogonalMetricSpaceType>::template cincludes_grades<PossibleGrades> {
				};

				constexpr static decltype(auto) call_basis_vectors(orthogonal_metric_space<OrthogonalMetricSpaceType> const *space) {
					return space->basis_vectors();
				}

				constexpr static ndims_t call_vector_space_dimension(orthogonal_metric_space<OrthogonalMetricSpaceType> const *space) {
					return space->vector_space_dimension();
				}

				constexpr static bool call_includes_basis_blade(orthogonal_metric_space<OrthogonalMetricSpaceType> const *space, default_bitset_t const arg) {
					return space->includes_basis_blade(arg);
				}
			};

			template<class OrthogonalMetricSpaceType>
			struct metric_space_traits<orthogonal_metric_space<OrthogonalMetricSpaceType> > {
				typedef typename detail::metric_space_traits<OrthogonalMetricSpaceType>::entry_type entry_type;

				template<index_t Row, index_t Col>
				struct cmetric_entry : detail::metric_space_traits<OrthogonalMetricSpaceType>::template cmetric_entry<Row, Col> {
				};

				template<default_bitset_t BasisBlade>
				struct cmetric_factor : detail::metric_space_traits<OrthogonalMetricSpaceType>::template cmetric_factor<BasisBlade> {
				};

				constexpr static decltype(auto) call_metric_entry(orthogonal_metric_space<OrthogonalMetricSpaceType> const *metric_space, index_t const row, index_t const col) {
					return metric_space->metric_entry(row, col);
				}

				constexpr static decltype(auto) call_metric_factor(orthogonal_metric_space<OrthogonalMetricSpaceType> const *metric_space, default_bitset_t const arg) {
					return metric_space->metric_factor(arg);
				}
			};

		}

	}

}

#endif // __GA_CLIFFORD_ORTHOGONAL_METRIC_SPACE_HPP__
