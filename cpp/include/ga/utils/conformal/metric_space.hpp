#ifndef __GA_UTILS_CONFORMAL_METRIC_SPACE_HPP__
#define __GA_UTILS_CONFORMAL_METRIC_SPACE_HPP__

namespace ga {

	// Conformal metric space.
	template<ndims_t N>
	class conformal_metric_space : public metric_space<conformal_metric_space<N> > {
	public:

		typedef conformal_metric_space metric_space_type;

		constexpr static default_bitset_t basis_vectors = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (N + 2)));
		constexpr static ndims_t vector_space_dimensions = N + 2;

		template<class RowIndex, class ColIndex>
		struct entry {
			typedef detail::if_else_t<
				detail::equal_t<RowIndex, ColIndex>,
				detail::if_else_t<detail::less_or_equal_t<RowIndex, detail::constant_value<N> >, detail::constant_value<1>, detail::constant_value<0> >,
				detail::if_else_t<detail::logical_or_t<detail::less_or_equal_t<RowIndex, detail::constant_value<N> >, detail::less_or_equal_t<ColIndex, detail::constant_value<N> > >, detail::constant_value<0>, detail::constant_value<-1> >
			> type;
		};
	};

	// Specialization of is_general_metric_space<MetricSpaceType>.
	template<ndims_t N>
	struct is_general_metric_space<conformal_metric_space<N> > {
		constexpr static bool value = true;
	};

}

#endif // __GA_UTILS_CONFORMAL_METRIC_SPACE_HPP__
