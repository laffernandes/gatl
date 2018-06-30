#ifndef __GA_UTILS_SIGNED_MINKOWSKI_FLAT_LOCATION_HPP__
#define __GA_UTILS_SIGNED_MINKOWSKI_FLAT_LOCATION_HPP__

namespace ga {

	// Returns the location parameter of a given flat.
	template<class CoefficientType, class Expression, ndims_t N>
	constexpr decltype(auto) flat_location(clifford_expression<CoefficientType, Expression> const &flat, minkowski_metric_space<N> const &mtr) {
		auto const lazy = make_lazy_context(flat);
		return lazy.eval(gp(lcont(e(c<N + 1>) + e(c<N + 2>), lazy.argument<0>(), mtr), inv(lazy.argument<0>(), mtr), mtr));
	}

}

#endif // __GA_UTILS_SIGNED_MINKOWSKI_FLAT_LOCATION_HPP__
