#ifndef __GA_UTILS_SIGNED_MINKOWSKI_FLAT_DIRECTION_HPP__
#define __GA_UTILS_SIGNED_MINKOWSKI_FLAT_DIRECTION_HPP__

namespace ga {

	// Returns the direction parameter of a given flat.
	template<class CoefficientType, class Expression, ndims_t N>
	constexpr decltype(auto) flat_direction(clifford_expression<CoefficientType, Expression> const &flat, minkowski_metric_space<N> const &mtr) {
		return lcont(-(e(c<N + 1>) + e(c<N + 2>)), flat, mtr);
	}

}

#endif // __GA_UTILS_SIGNED_MINKOWSKI_FLAT_DIRECTION_HPP__
