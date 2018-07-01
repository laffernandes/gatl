#ifndef __GA_UTILS_SIGNED_HOMOGENEOUS_FLAT_DIRECTION_HPP__
#define __GA_UTILS_SIGNED_HOMOGENEOUS_FLAT_DIRECTION_HPP__

namespace ga {

	// Returns the direction parameter of a given k-flat.
	template<typename CoefficientType, typename Expression, ndims_t N>
	constexpr decltype(auto) flat_direction(clifford_expression<CoefficientType, Expression> const &flat, homogeneous_metric_space<N> const &mtr) {
		return lcont(e(c<N + 1>), flat, mtr);
	}

}

#endif // __GA_UTILS_SIGNED_HOMOGENEOUS_FLAT_DIRECTION_HPP__
