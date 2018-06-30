#ifndef __GA_EXTRA_APPLY_VERSOR_HPP__
#define __GA_EXTRA_APPLY_VERSOR_HPP__

namespace ga {

	// Apply an even versor (i.e., an orthogonal transformation) to a Clifford expression.
	template<class VersorCoefficientType, class VersorExpression, class CoefficientType, class Expression, class MetricSpaceType>
	constexpr decltype(auto) apply_even_versor(clifford_expression<VersorCoefficientType, VersorExpression> const &versor, clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(versor, arg);
		return lazy.eval(gp(gp(lazy.argument<0>(), lazy.argument<1>(), mtr), inv(lazy.argument<0>(), mtr), mtr));
	}

	template<class VersorCoefficientType, class VersorExpression, class Type, class MetricSpaceType>
	constexpr decltype(auto) apply_even_versor(clifford_expression<VersorCoefficientType, VersorExpression> const &versor, Type const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_even_versor(versor, scalar(arg), mtr);
	}

	template<class VersorType, class CoefficientType, class Expression, class MetricSpaceType>
	constexpr decltype(auto) apply_even_versor(VersorType const &versor, clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_even_versor(scalar(versor), arg, mtr);
	}

	template<class VersorType, class Type, class MetricSpaceType>
	constexpr decltype(auto) apply_even_versor(VersorType const &versor, Type const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_even_versor(scalar(versor), scalar(arg), mtr);
	}

	// Apply an odd versor (i.e., an orthogonal transformation) to a Clifford expression.
	template<class VersorCoefficientType, class VersorExpression, class CoefficientType, class Expression, class MetricSpaceType>
	constexpr decltype(auto) apply_odd_versor(clifford_expression<VersorCoefficientType, VersorExpression> const &versor, clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(versor, arg);
		return lazy.eval(gp(gp(lazy.argument<0>(), involution(lazy.argument<1>()), mtr), inv(lazy.argument<0>(), mtr), mtr));
	}

	template<class VersorCoefficientType, class VersorExpression, class Type, class MetricSpaceType>
	constexpr decltype(auto) apply_odd_versor(clifford_expression<VersorCoefficientType, VersorExpression> const &versor, Type const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_odd_versor(versor, scalar(arg), mtr);
	}

	template<class VersorType, class CoefficientType, class Expression, class MetricSpaceType>
	constexpr decltype(auto) apply_odd_versor(VersorType const &versor, clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_odd_versor(scalar(versor), arg, mtr);
	}

	template<class VersorType, class Type, class MetricSpaceType>
	constexpr decltype(auto) apply_odd_versor(VersorType const &versor, Type const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_odd_versor(scalar(versor), scalar(arg), mtr);
	}

}

#endif // __GA_EXTRA_APPLY_VERSOR_HPP__
