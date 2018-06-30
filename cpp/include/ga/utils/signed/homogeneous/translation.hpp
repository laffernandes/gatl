#ifndef __GA_UTILS_SIGNED_HOMOGENEOUS_TRANSLATION_HPP__
#define __GA_UTILS_SIGNED_HOMOGENEOUS_TRANSLATION_HPP__

namespace ga {

	// Translate the given k-flat to a given direction.
	template<class DirectionCoefficientType, class DirectionExpression, class CoefficientType, class Expresion, ndims_t N>
	constexpr decltype(auto) translate(clifford_expression<DirectionCoefficientType, DirectionExpression> const &direction, clifford_expression<CoefficientType, Expresion> const &flat, homogeneous_metric_space<N> const &mtr) {
		auto const lazy = make_lazy_context(direction, flat);
		return lazy.eval(lazy.argument<1>() + op(lazy.argument<0>(), lcont(e(c<N + 1>), lazy.argument<1>(), mtr), mtr));
	}

}

#endif // __GA_UTILS_SIGNED_HOMOGENEOUS_TRANSLATION_HPP__
