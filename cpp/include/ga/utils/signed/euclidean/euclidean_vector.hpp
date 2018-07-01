#ifndef __GA_UTILS_SIGNED_EUCLIDEAN_EUCLIDEAN_VECTOR_HPP__
#define __GA_UTILS_SIGNED_EUCLIDEAN_EUCLIDEAN_VECTOR_HPP__

namespace ga {

	// Initializes a multivector representation of a Euclidean vector using the given coordinates expressed in the base space.
	template<ndims_t N, typename... Types>
	constexpr decltype(auto) euclidean_vector(euclidean_metric_space<N> const &mtr, Types &&... coords) {
		return vector(mtr, std::move(coords)...);
	}

}

#endif // __GA_UTILS_SIGNED_EUCLIDEAN_EUCLIDEAN_VECTOR_HPP__
