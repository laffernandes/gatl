#ifndef __GA_EXTRA_UNIT_HPP__
#define __GA_EXTRA_UNIT_HPP__

namespace ga {

	// Computes the unit multivector under reverse norm.
	template<typename CoefficientType, typename Expression, typename MetricSpaceType>
	constexpr decltype(auto) unit(clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(gp(lazy.argument<0>(), inv(sqrt(abs(sp(lazy.argument<0>(), reverse(lazy.argument<0>()), mtr))), mtr), mtr));
	}

}

#endif // __GA_EXTRA_UNIT_HPP__
