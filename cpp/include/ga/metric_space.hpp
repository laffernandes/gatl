#ifndef __GA_METRIC_SPACE_HPP__
#define __GA_METRIC_SPACE_HPP__

namespace ga {

	namespace detail {

		template<class MetricSpaceType>
		struct metric_space_traits;

	}

	template<class MetricSpaceType>
	class metric_space : public space<metric_space<MetricSpaceType> > {
	public:

		typedef typename detail::metric_space_traits<MetricSpaceType>::entry_type entry_type;

		template<default_bitset_t BasisBlade>
		struct cincludes_basis_blade : detail::space_traits<MetricSpaceType>::template cincludes_basis_blade<BasisBlade> {
		};

		template<default_bitset_t PossibleGrades>
		struct cincludes_grades : detail::space_traits<MetricSpaceType>::template cincludes_grades<PossibleGrades> {
		};

		template<index_t Row, index_t Col>
		struct cmetric_entry : detail::metric_space_traits<MetricSpaceType>::template cmetric_entry<Row, Col> {
		};

		template<default_bitset_t BasisBlade>
		struct cmetric_factor : detail::metric_space_traits<MetricSpaceType>::template cmetric_factor<BasisBlade> {
		};

		constexpr static ndims_t vector_space_dimension() {
			return detail::space_traits<MetricSpaceType>::call_vector_space_dimension(static_cast<MetricSpaceType const*>(this));
		}

		constexpr bool includes_basis_blade(default_bitset_t const arg) const {
			return detail::space_traits<MetricSpaceType>::call_includes_basis_blade(static_cast<MetricSpaceType const*>(this), arg);
		}

		constexpr decltype(auto) metric_entry(index_t const row, index_t const col) const {
			return detail::metric_space_traits<MetricSpaceType>::call_metric_entry(static_cast<MetricSpaceType const*>(this), row, col);
		}

		constexpr decltype(auto) metric_factor(default_bitset_t const arg) const {
			return detail::metric_space_traits<MetricSpaceType>::call_metric_factor(static_cast<MetricSpaceType const*>(this), arg);
		}
	};
	
	namespace detail {

		template<class MetricSpaceType>
		struct space_traits<metric_space<MetricSpaceType> > {
			template<default_bitset_t BasisBlade>
			struct cincludes_basis_blade : detail::space_traits<MetricSpaceType>::template cincludes_basis_blades<BasisBlade> {
			};

			template<default_bitset_t PossibleGrades>
			struct cincludes_grades : detail::space_traits<MetricSpaceType>::template cincludes_grades<PossibleGrades> {
			};

			constexpr static ndims_t call_vector_space_dimension(metric_space<MetricSpaceType> const *space) {
				return space->vector_space_dimension();
			}

			constexpr static bool call_includes_basis_blade(metric_space<MetricSpaceType> const *space, default_bitset_t const arg) {
				return space->includes_basis_blade(arg);
			}
		};

	}

}

#endif // __GA_METRIC_SPACE_HPP__
