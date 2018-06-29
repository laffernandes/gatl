#ifndef __GA_UTILS_SIGNED_HOMOGENEOUS_MAKE_EUCLIDEAN_VECTOR_HPP__
#define __GA_UTILS_SIGNED_HOMOGENEOUS_MAKE_EUCLIDEAN_VECTOR_HPP__

namespace ga {

	// Initializes a multivector representation of a Euclidean vector using the given coordinates expressed in the base space.
	template<ndims_t N, class... Types>
	constexpr decltype(auto) make_euclidean_vector(homogeneous_metric_space<N> const &mtr, Types &&... coords) {
		return vector(mtr, std::move(coords)..., c<0>);
	}

}

#endif // __GA_UTILS_SIGNED_HOMOGENEOUS_MAKE_EUCLIDEAN_VECTOR_HPP__
