#ifndef __GA_UTILS_SIGNED_HOMOGENEOUS_POINT_HPP__
#define __GA_UTILS_SIGNED_HOMOGENEOUS_POINT_HPP__

namespace ga {

	// Initializes a multivector representation of a point using the given coordinates expressed in the base space.
	template<ndims_t N, class... Types>
	constexpr decltype(auto) point(homogeneous_metric_space<N> const &mtr, Types &&... coords) {
		return vector(mtr, std::move(coords)..., c<1>);
	}

}

#endif // __GA_UTILS_SIGNED_HOMOGENEOUS_POINT_HPP__
