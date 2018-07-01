#ifndef __GA_UTILS_SIGNED_MINKOWSKI_ROUND_DIRECTION_HPP__
#define __GA_UTILS_SIGNED_MINKOWSKI_ROUND_DIRECTION_HPP__

namespace ga {

	// Returns the direction parameter of a given round.
	template<typename CoefficientType, typename Expression, ndims_t N>
	constexpr decltype(auto) round_direction(clifford_expression<CoefficientType, Expression> const &round, minkowski_metric_space<N> const &mtr) {
		auto const lazy = make_lazy_context(round);
		return lazy.eval(op(lcont(-(e(c<N + 1>) + e(c<N + 2>)), lazy.argument<0>(), mtr), e(c<N + 1>) + e(c<N + 2>), mtr));
	}

}

#endif // __GA_UTILS_SIGNED_MINKOWSKI_ROUND_DIRECTION_HPP__
