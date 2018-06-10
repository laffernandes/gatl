#ifndef __FUTURE_GA_CONFORMAL_METRIC_SPACE_HPP__
#define __FUTURE_GA_CONFORMAL_METRIC_SPACE_HPP__

namespace ga {

	// Conformal metric space.
	template<ndims_t N>
	class conformal_metric_space : public metric_space<conformal_metric_space<N> > {
	public:

		typedef conformal_metric_space metric_space_type;

		constexpr static default_bitset_t basis_vectors = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (N + 2)));
		constexpr static ndims_t vector_space_dimensions = N + 2;

		//TODO Not supported yet (conformal metric space).
	};

	// Specialization of is_general_metric_space<MetricSpaceType>.
	template<ndims_t N>
	struct is_general_metric_space<conformal_metric_space<N> > {
		constexpr static bool value = true;
	};

}

#endif // __FUTURE_GA_CONFORMAL_METRIC_SPACE_HPP__
