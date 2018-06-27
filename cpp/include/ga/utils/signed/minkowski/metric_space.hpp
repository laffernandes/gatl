#ifndef __GA_UTILS_SIGNED_MINKOWSKI_METRIC_SPACE_HPP__
#define __GA_UTILS_SIGNED_MINKOWSKI_METRIC_SPACE_HPP__

namespace ga {

	// Minkowski metric space.
	template<ndims_t N>
	using minkowski_metric_space = signed_metric_space<N + 1, 1>;

}

#endif // __GA_UTILS_SIGNED_MINKOWSKI_METRIC_SPACE_HPP__
