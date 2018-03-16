#ifndef __GA_METRIC_HPP__
#define __GA_METRIC_HPP__

namespace ga {

	namespace detail {

		template <class MetricType>
		struct metric_traits;

	}

	template <class MetricType>
	class metric {
	public:

		typedef typename detail::metric_traits<MetricType>::entry_type entry_type;

		template<default_integral_t Row, default_integral_t Col>
		struct centry : detail::metric_traits<MetricType>::template centry<Row, Col> {
		};

		template<default_integral_t Index>
		struct cdiagonal_entry : detail::metric_traits<MetricType>::template cdiagonal_entry<Index> {
		};

		template<default_bitset_t BasisBlade>
		struct cmetric_factor : detail::metric_traits<MetricType>::template cmetric_factor<BasisBlade> {
		};

		constexpr decltype(auto) entry(index_t const row, index_t const col) const {
			return detail::metric_traits<MetricType>::call_entry(static_cast<MetricType const*>(this), row, col);
		}

		constexpr decltype(auto) diagonal_entry(index_t const index) const {
			return detail::metric_traits<MetricType>::call_diagonal_entry(static_cast<MetricType const*>(this), index);
		}

		constexpr decltype(auto) metric_factor(default_bitset_t const arg) const {
			return detail::metric_traits<MetricType>::call_metric_factor(static_cast<MetricType const*>(this), arg);
		}
	};
	
	template <class MetricType>
	class orthogonal_metric : public metric<orthogonal_metric<MetricType> > {
	public:

		typedef typename detail::metric_traits<MetricType>::entry_type entry_type;

		template<default_integral_t Row, default_integral_t Col>
		struct centry : detail::metric_traits<MetricType>::template centry<Row, Col> {
		};

		template<default_integral_t Index>
		struct cdiagonal_entry : detail::metric_traits<MetricType>::template cdiagonal_entry<Index> {
		};

		template<default_bitset_t BasisBlade>
		struct cmetric_factor : detail::metric_traits<MetricType>::template cmetric_factor<BasisBlade> {
		};

		constexpr decltype(auto) entry(index_t const row, index_t const col) const {
			return detail::metric_traits<MetricType>::call_entry(static_cast<MetricType const*>(this), row, col);
		}

		constexpr decltype(auto) diagonal_entry(index_t const index) const {
			return detail::metric_traits<MetricType>::call_diagonal_entry(static_cast<MetricType const*>(this), index);
		}

		constexpr decltype(auto) metric_factor(default_bitset_t const arg) const {
			return detail::metric_traits<MetricType>::call_metric_factor(static_cast<MetricType const*>(this), arg);
		}
	};

	namespace detail {

		template<class MetricType>
		struct metric_traits<orthogonal_metric<MetricType> > {
			typedef typename detail::metric_traits<MetricType>::entry_type entry_type;

			template<default_integral_t Row, default_integral_t Col>
			struct centry : detail::metric_traits<MetricType>::template centry<Row, Col> {
			};

			template<default_integral_t Index>
			struct cdiagonal_entry : detail::metric_traits<MetricType>::template cdiagonal_entry<Index> {
			};

			template<default_bitset_t BasisBlade>
			struct cmetric_factor : detail::metric_traits<MetricType>::template cmetric_factor<BasisBlade> {
			};

			constexpr static decltype(auto) call_entry(orthogonal_metric<MetricType> const *metric, index_t const row, index_t const col) {
				return metric->entry(row, col);
			}

			constexpr static decltype(auto) call_diagonal_entry(orthogonal_metric<MetricType> const *metric, index_t const index) {
				return metric->diagonal_entry(index);
			}

			constexpr static decltype(auto) call_metric_factor(orthogonal_metric<MetricType> const *metric, default_bitset_t const arg) {
				return metric->metric_factor(arg);
			}
		};

	}

}

#endif // __GA_METRIC_HPP__
