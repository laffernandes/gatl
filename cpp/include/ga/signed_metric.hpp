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

		template<default_integral_t Index>
		struct cdiagonal_entry : detail::metric_traits<signed_metric>::template cdiagonal_entry<Index> {
		};

		template<default_bitset_t BasisBlade>
		struct cmetric_factor : detail::metric_traits<signed_metric>::template cmetric_factor<BasisBlade> {
		};

		constexpr static entry_type entry(index_t const row, index_t const col) {
			return static_cast<entry_type>(row == col ? diagonal_entry(row) : 0);
		}

		constexpr static entry_type diagonal_entry(index_t const index) {
			return static_cast<entry_type>(index <= (P + Q) ? (index <= P ? (index > 0 ? +1 : 0) : -1) : 0);
		}

		template<default_bitset_t BasisBlade>
		constexpr static decltype(auto) metric_factor(detail::cbasis_blade<BasisBlade> const &) {
			return cmetric_factor<BasisBlade>::value;
		}

		template<default_bitset_t PossibleGrades>
		constexpr static decltype(auto) metric_factor(detail::dbasis_blade<PossibleGrades> const &arg) {
			index_t index = 0;
			default_bitset_t mask = arg.value();
			default_integral_t result = static_cast<default_integral_t>(1);
			while (mask != default_bitset_t(0)) {
				if ((mask & default_bitset_t(1)) != default_bitset_t(0)) {
					result *= diagonal_entry(index);
				}
				mask >>= 1;
				index++;
			}
			return static_cast<entry_type>(result);
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
				constexpr static auto value = cvalue<Row == Col ? cdiagonal_entry<Row>::value : 0>();
			};

			template<default_integral_t Index>
			struct cdiagonal_entry {
				static_assert(Index > 0, "Positive index expected.");
				constexpr static auto value = cvalue<Index <= (P + Q) ? (Index <= P ? +1 : -1) : 0>();
			};

			template<default_bitset_t BasisBlade>
			struct cmetric_factor {
			private:

				constexpr static default_bitset_t zero = ~(((default_bitset_t(1) << (P + Q + 1)) - 1) & ~default_bitset_t(1));
				constexpr static default_bitset_t minus = (((default_bitset_t(1) << (P + 1)) - 1) ^ ((default_bitset_t(1) << (P + Q + 1)) - 1)) & ~default_bitset_t(1);

			public:

				static_assert((BasisBlade & default_bitset_t(1)) == 0, "Positive indices expected.");
				constexpr static auto value = cvalue<(BasisBlade & zero) != default_bitset_t(0) ? 0 : ((_basis_blade_grade<cbasis_blade<BasisBlade & minus> >::value & 1) == 0 ? 1: -1)>();
			};

			constexpr static decltype(auto) call_entry(signed_metric<P, Q, EntryType> const *, index_t const row, index_t const col) {
				return signed_metric<P, Q, EntryType>::entry(row, col);
			}

			constexpr static decltype(auto) call_diagonal_entry(signed_metric<P, Q, EntryType> const *, index_t const index) {
				return signed_metric<P, Q, EntryType>::diagonal_entry(index);
			}

			template<class BasisBladeType>
			constexpr static decltype(auto) call_metric_factor(signed_metric<P, Q, EntryType> const *, BasisBladeType const &arg) {
				return signed_metric<P, Q, EntryType>::metric_factor(arg);
			}
		};

	}

	template<ndims_t P, ndims_t Q>
	using signed_metric_t = signed_metric<P, Q, default_integral_t>;

}

#endif // __GA_SIGNED_METRIC_HPP__
