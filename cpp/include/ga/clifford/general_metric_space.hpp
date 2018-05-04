#ifndef __GA_CLIFFORD_GENERAL_METRIC_SPACE_HPP__
#define __GA_CLIFFORD_GENERAL_METRIC_SPACE_HPP__

namespace ga {

	namespace clifford {

		template<class GeneralMetricSpaceType>
		class general_metric_space : public metric_space<general_metric_space<GeneralMetricSpaceType> > {
		public:

			typedef typename detail::metric_space_traits<GeneralMetricSpaceType>::entry_type entry_type;

			template<default_bitset_t BasisBlade>
			struct cincludes_basis_blade : detail::space_traits<GeneralMetricSpaceType>::template cincludes_basis_blade<BasisBlade> {
			};

			template<default_bitset_t PossibleGrades>
			struct cincludes_grades : detail::space_traits<GeneralMetricSpaceType>::template cincludes_grades<PossibleGrades> {
			};

			template<index_t Row, index_t Col>
			struct cmetric_entry : detail::metric_space_traits<GeneralMetricSpaceType>::template cmetric_entry<Row, Col> {
			};

			template<default_bitset_t BasisBlade>
			struct cmetric_factor : detail::metric_space_traits<GeneralMetricSpaceType>::template cmetric_factor<BasisBlade> {
			};

			constexpr decltype(auto) basis_vectors() const {
				return detail::space_traits<GeneralMetricSpaceType>::call_basis_vectors(static_cast<GeneralMetricSpaceType const*>(this));
			}

			constexpr static ndims_t vector_space_dimension() {
				return detail::space_traits<GeneralMetricSpaceType>::call_vector_space_dimension(static_cast<GeneralMetricSpaceType const*>(this));
			}

			constexpr bool includes_basis_blade(default_bitset_t const arg) const {
				return detail::space_traits<GeneralMetricSpaceType>::call_includes_basis_blade(static_cast<GeneralMetricSpaceType const*>(this), arg);
			}

			constexpr decltype(auto) metric_entry(index_t const row, index_t const col) const {
				return detail::metric_space_traits<GeneralMetricSpaceType>::call_metric_entry(static_cast<GeneralMetricSpaceType const*>(this), row, col);
			}

			constexpr decltype(auto) metric_factor(default_bitset_t const arg) const {
				return detail::metric_space_traits<GeneralMetricSpaceType>::call_metric_factor(static_cast<GeneralMetricSpaceType const*>(this), arg);
			}
		};

		namespace detail {

			template<class GeneralMetricSpaceType>
			struct space_traits<general_metric_space<GeneralMetricSpaceType> > {
				template<default_bitset_t BasisBlade>
				struct cincludes_basis_blade : detail::space_traits<GeneralMetricSpaceType>::template cincludes_basis_blades<BasisBlade> {
				};

				template<default_bitset_t PossibleGrades>
				struct cincludes_grades : detail::space_traits<GeneralMetricSpaceType>::template cincludes_grades<PossibleGrades> {
				};

				constexpr static decltype(auto) call_basis_vectors(general_metric_space<GeneralMetricSpaceType> const *space) {
					return space->basis_vectors();
				}

				constexpr static ndims_t call_vector_space_dimension(general_metric_space<GeneralMetricSpaceType> const *space) {
					return space->vector_space_dimension();
				}

				constexpr static bool call_includes_basis_blade(general_metric_space<GeneralMetricSpaceType> const *space, default_bitset_t const arg) {
					return space->includes_basis_blade(arg);
				}
			};

			template<class GeneralMetricSpaceType>
			struct metric_space_traits<general_metric_space<GeneralMetricSpaceType> > {
				typedef typename detail::metric_space_traits<GeneralMetricSpaceType>::entry_type entry_type;

				template<index_t Row, index_t Col>
				struct cmetric_entry : detail::metric_space_traits<GeneralMetricSpaceType>::template cmetric_entry<Row, Col> {
				};

				template<default_bitset_t BasisBlade>
				struct cmetric_factor : detail::metric_space_traits<GeneralMetricSpaceType>::template cmetric_factor<BasisBlade> {
				};

				constexpr static decltype(auto) call_metric_entry(general_metric_space<GeneralMetricSpaceType> const *metric_space, index_t const row, index_t const col) {
					return metric_space->metric_entry(row, col);
				}

				constexpr static decltype(auto) call_metric_factor(general_metric_space<GeneralMetricSpaceType> const *metric_space, default_bitset_t const arg) {
					return metric_space->metric_factor(arg);
				}
			};

		}

	}

}

#endif // __GA_CLIFFORD_GENERAL_METRIC_SPACE_HPP__
