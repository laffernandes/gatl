#ifndef __GA_EXTRA_DUALIZATION_HPP__
#define __GA_EXTRA_DUALIZATION_HPP__

namespace ga {

	template<class CoefficientType, class Expression, class PseudoscalarCoefficientType, class PseudoscalarExpression, class MetricSpaceType>
	constexpr decltype(auto) dual(clifford_expression<CoefficientType, Expression> const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(arg, pseudoscalar);
		return lazy.eval(lcont(lazy.argument<0>(), inv(lazy.argument<1>(), mtr), mtr));
	}

	template<class Type, class PseudoscalarCoefficientType, class PseudoscalarExpression, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) dual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) {
		return dual(scalar(arg), pseudoscalar, mtr);
	}

	template<class CoefficientType, class Expression, class PseudoscalarCoefficientType, class PseudoscalarExpression, class MetricSpaceType>
	constexpr decltype(auto) undual(clifford_expression<CoefficientType, Expression> const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(arg, pseudoscalar);
		return lazy.eval(lcont(lazy.argument<0>(), lazy.argument<1>(), mtr));
	}

	template<class Type, class PseudoscalarCoefficientType, class PseudoscalarExpression, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) undual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) {
		return undual(scalar(arg), pseudoscalar, mtr);
	}

}

#endif // __GA_EXTRA_DUALIZATION_HPP__
