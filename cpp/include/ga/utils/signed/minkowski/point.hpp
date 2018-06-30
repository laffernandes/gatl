#ifndef __GA_UTILS_CONFORMAL_POINT_HPP__
#define __GA_UTILS_CONFORMAL_POINT_HPP__

namespace ga {

	// Initializes a multivector representation of a point using the given coordinates expressed in the base space.
	template<ndims_t N, class... Types>
	constexpr decltype(auto) point(minkowski_metric_space<N> const &mtr, Types &&... coords) {
		auto aux = detail::sum(detail::square(std::move(coords))...);
		return vector(mtr, std::move(coords)..., (aux - c<1>) / c<2>, (aux + c<1>) / c<2>);
	}

}

#endif // __GA_UTILS_CONFORMAL_POINT_HPP__
