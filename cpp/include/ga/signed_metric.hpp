#ifndef __GA_SIGNED_METRIC_HPP__
#define __GA_SIGNED_METRIC_HPP__

namespace ga {
	
	template<ndims_t P, ndims_t Q, class EntryType>
	class signed_metric : public orthogonal_metric<signed_metric<P, Q, EntryType> > {
	public:

		typedef typename detail::metric_traits<signed_metric>::entry_type entry_type;

		template<default_integral_t Row, default_integral_t Col>
		struct centry : detail::metric_traits<signed_metric>::template centry<Row, Col> {
		};

		template<default_bitset_t BasisBlade>
		struct cmetric_factor : detail::metric_traits<signed_metric>::template cmetric_factor<BasisBlade> {
		};

		constexpr static entry_type entry(index_t const row, index_t const col) {
			return static_cast<entry_type>(row == col && 0 < row && row <= (P + Q) ? (row <= P ? 1 : -1) : 0);
		}

		constexpr static decltype(auto) metric_factor(default_bitset_t arg) {
			constexpr static default_bitset_t zero = ~(((default_bitset_t(1) << (P + Q + 1)) - 1) & ~default_bitset_t(1));
			constexpr static default_bitset_t minus = (((default_bitset_t(1) << (P + 1)) - 1) ^ ((default_bitset_t(1) << (P + Q + 1)) - 1)) & ~default_bitset_t(1);
			return static_cast<entry_type>((arg & zero) != default_bitset_t(0) ? 0 : ((detail::ones(arg & minus) & default_bitset_t(1)) == 0 ? 1 : -1));
		}
	};

	namespace detail {

		template<ndims_t P, ndims_t Q, class EntryType>
		struct metric_traits<signed_metric<P, Q, EntryType> > {
			static_assert(std::is_convertible<EntryType, default_integral_t>::value, "The EntryType of the ga::signed_metric<P, Q, EntryType> class mst be convertible to ga::default_integral_t.");

			typedef EntryType entry_type;

			template<default_integral_t Row, default_integral_t Col>
			struct centry {
				static_assert(Row > 0 && Col > 0, "Positive indices expected.");
				constexpr static auto value = cvalue<(Row == Col && 0 < Row && Row <= (P + Q) ? (Row <= P ? 1 : -1) : 0)>();
			};

			template<default_bitset_t BasisBlade>
			struct cmetric_factor {
			private:

				constexpr static default_bitset_t zero = ~(((default_bitset_t(1) << (P + Q + 1)) - 1) & ~default_bitset_t(1));
				constexpr static default_bitset_t minus = (((default_bitset_t(1) << (P + 1)) - 1) ^ ((default_bitset_t(1) << (P + Q + 1)) - 1)) & ~default_bitset_t(1);

			public:

				static_assert((BasisBlade & default_bitset_t(1)) == 0, "Positive indices expected.");
				constexpr static auto value = cvalue<(BasisBlade & zero) != default_bitset_t(0) ? 0 : ((_ones<BasisBlade & minus>::value & default_bitset_t(1)) == 0 ? 1: -1)>();
			};

			constexpr static decltype(auto) call_entry(signed_metric<P, Q, EntryType> const *, index_t const row, index_t const col) {
				return signed_metric<P, Q, EntryType>::entry(row, col);
			}

			constexpr static decltype(auto) call_metric_factor(signed_metric<P, Q, EntryType> const *, default_bitset_t const arg) {
				return signed_metric<P, Q, EntryType>::metric_factor(arg);
			}
		};

	}

	template<ndims_t P, ndims_t Q>
	using signed_metric_t = signed_metric<P, Q, default_integral_t>;

}

#endif // __GA_SIGNED_METRIC_HPP__
