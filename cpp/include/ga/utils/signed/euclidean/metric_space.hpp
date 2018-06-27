#ifndef __GA_UTILS_SIGNED_EUCLIDEAN_METRIC_SPACE_HPP__
#define __GA_UTILS_SIGNED_EUCLIDEAN_METRIC_SPACE_HPP__

namespace ga {

	// Euclidean metric space.
	template<ndims_t N>
	using euclidean_metric_space = signed_metric_space<N, 0>;

}

#endif // __GA_UTILS_SIGNED_EUCLIDEAN_METRIC_SPACE_HPP__
