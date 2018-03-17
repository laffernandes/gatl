#ifndef __GA_EUCLIDEAN_METRIC_HPP__
#define __GA_EUCLIDEAN_METRIC_HPP__

namespace ga {

	template<class EntryType>
	class euclidean_metric : public orthogonal_metric<euclidean_metric<EntryType> > {
	public:

		typedef typename detail::metric_traits<euclidean_metric>::entry_type entry_type;

		template<default_integral_t Row, default_integral_t Col>
		struct centry : detail::metric_traits<euclidean_metric>::template centry<Row, Col> {
		};

		template<default_integral_t Index>
		struct cdiagonal_entry : detail::metric_traits<euclidean_metric>::template cdiagonal_entry<Index> {
		};

		template<default_bitset_t BasisBlade>
		struct cmetric_factor : detail::metric_traits<euclidean_metric>::template cmetric_factor<BasisBlade> {
		};

		constexpr static entry_type entry(index_t const row, index_t const col) {
			return static_cast<entry_type>(row == col ? 1 : 0);
		}

		constexpr static detail::cvalue<1> diagonal_entry(index_t const) {
			return detail::cvalue<1>();
		}

		constexpr static detail::cvalue<1> metric_factor(default_bitset_t const) {
			return detail::cvalue<1>();
		}
	};

	namespace detail {

		template<class EntryType>
		struct metric_traits<euclidean_metric<EntryType> > {
			static_assert(std::is_convertible<EntryType, default_integral_t>::value, "The EntryType of the ga::euclidean_metric<EntryType> class mst be convertible to ga::default_integral_t.");

			typedef EntryType entry_type;

			template<default_integral_t Row, default_integral_t Col>
			struct centry {
				static_assert(Row >= 0 && Col >= 0, "Non-negative indices expected.");
				constexpr static auto value = cvalue<Row == Col ? 1 : 0>();
			};

			template<default_integral_t Index>
			struct cdiagonal_entry {
				static_assert(Index >= 0, "Non-negative index expected.");
				constexpr static auto value = cvalue<1>();
			};

			template<default_bitset_t BasisBlade>
			struct cmetric_factor {
				constexpr static auto value = cvalue<1>();
			};

			constexpr static decltype(auto) call_entry(euclidean_metric<EntryType> const *, index_t const row, index_t const col) {
				return euclidean_metric<EntryType>::entry(row, col);
			}

			constexpr static decltype(auto) call_diagonal_entry(euclidean_metric<EntryType> const *, index_t const index) {
				return euclidean_metric<EntryType>::diagonal_entry(index);
			}

			constexpr static decltype(auto) call_metric_factor(euclidean_metric<EntryType> const *, default_bitset_t const bitset) {
				return euclidean_metric<EntryType>::metric_factor(bitset);
			}
		};

	}

	using euclidean_metric_t = euclidean_metric<default_integral_t>;

}

#endif // __GA_EUCLIDEAN_METRIC_HPP__
