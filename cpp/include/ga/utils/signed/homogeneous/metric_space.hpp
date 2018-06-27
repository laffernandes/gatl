#ifndef __GA_UTILS_SIGNED_HOMOGENEOUS_METRIC_SPACE_HPP__
#define __GA_UTILS_SIGNED_HOMOGENEOUS_METRIC_SPACE_HPP__

namespace ga {

	// Homogeneous metric space.
	template<ndims_t N>
	using homogeneous_metric_space = signed_metric_space<N + 1, 0>;

}

#endif // __GA_UTILS_SIGNED_HOMOGENEOUS_METRIC_SPACE_HPP__
