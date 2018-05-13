#ifndef __FUTURE_GA_DUALIZATION_HPP__
#define __FUTURE_GA_DUALIZATION_HPP__

namespace ga {

	template<class CoefficientType, class Expression, class PseudoscalarType, class PseudoscalarCoefficientType, class PseudoscalarExpression, class MetricSpaceType>
	constexpr decltype(auto) dual(clifford_expression<CoefficientType, Expression> const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) {
		constexpr auto lazy = make_lazy_context(arg, pseudoscalar);
		return lazy.eval(lcont(lazy.argument<0>(), inv(lazy.argument<1>(), mtr), mtr));
	}

	template<class CoefficientType, class Expression, class PseudoscalarType, class PseudoscalarCoefficientType, class PseudoscalarExpression, class = std::enable_if_t<detail::is_scalar_expression_v<Expression> > >
	constexpr decltype(auto) dual(clifford_expression<CoefficientType, Expression> const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar) {
		constexpr auto lazy = make_lazy_context(arg, pseudoscalar);
		return lazy.eval(lcont(lazy.argument<0>(), inv(lazy.argument<1>())));
	}

	template<class Type, class PseudoscalarType, class PseudoscalarCoefficientType, class PseudoscalarExpression, class MetricSpaceType>
	constexpr decltype(auto) dual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &) {
		return dual(scalar(arg), pseudoscalar);
	}

	template<class Type, class PseudoscalarType, class PseudoscalarCoefficientType, class PseudoscalarExpression>
	constexpr decltype(auto) dual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar) {
		return dual(scalar(arg), pseudoscalar);
	}

	template<class CoefficientType, class Expression, class PseudoscalarType, class PseudoscalarCoefficientType, class PseudoscalarExpression, class MetricSpaceType>
	constexpr decltype(auto) undual(clifford_expression<CoefficientType, Expression> const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) {
		constexpr auto lazy = make_lazy_context(arg, pseudoscalar);
		return lazy.eval(lcont(lazy.argument<0>(), lazy.argument<1>(), mtr));
	}

	template<class CoefficientType, class Expression, class PseudoscalarType, class PseudoscalarCoefficientType, class PseudoscalarExpression, class = std::enable_if_t<detail::is_scalar_expression_v<Expression> > >
	constexpr decltype(auto) undual(clifford_expression<CoefficientType, Expression> const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar) {
		constexpr auto lazy = make_lazy_context(arg, pseudoscalar);
		return lazy.eval(lcont(lazy.argument<0>(), lazy.argument<1>()));
	}

	template<class Type, class PseudoscalarType, class PseudoscalarCoefficientType, class PseudoscalarExpression, class MetricSpaceType>
	constexpr decltype(auto) undual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &) {
		return undual(scalar(arg), pseudoscalar);
	}

	template<class Type, class PseudoscalarType, class PseudoscalarCoefficientType, class PseudoscalarExpression>
	constexpr decltype(auto) undual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar) {
		return undual(scalar(arg), pseudoscalar);
	}

}

#endif // __FUTURE_GA_DUALIZATION_HPP__
