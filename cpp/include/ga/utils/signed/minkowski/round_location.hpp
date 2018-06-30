#ifndef __GA_UTILS_SIGNED_MINKOWSKI_ROUND_LOCATION_HPP__
#define __GA_UTILS_SIGNED_MINKOWSKI_ROUND_LOCATION_HPP__

namespace ga {

	// Returns the location parameter of a given round.
	template<class CoefficientType, class Expression, ndims_t N>
	constexpr decltype(auto) round_location(clifford_expression<CoefficientType, Expression> const &round, minkowski_metric_space<N> const &mtr) {
		auto const lazy = make_lazy_context(round);
		return lazy.eval(gp(lazy.argument<0>(), inv(lcont(-(e(c<N + 1>) + e(c<N + 2>)), lazy.argument<0>(), mtr), mtr), mtr));
	}

}

#endif // __GA_UTILS_SIGNED_MINKOWSKI_ROUND_LOCATION_HPP__
