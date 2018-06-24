#ifndef __GA_REVERSE_NORM_HPP__
#define __GA_REVERSE_NORM_HPP__

namespace ga {

	template<class CoefficientType, class Expression, class MetricSpaceType>
	constexpr decltype(auto) rnorm_sqr(clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(sp(lazy.argument<0>(), reversion(lazy.argument<0>()), mtr));
	}

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) rnorm_sqr(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		return rnorm_sqr(arg, detail::real_metric_space());
	}

	template<class Type, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) rnorm_sqr(Type const &arg, metric_space<MetricSpaceType> const &) {
		return rnorm_sqr(scalar(arg), detail::real_metric_space());
	}

	template<class Type, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) rnorm_sqr(Type const &arg) {
		return rnorm_sqr(scalar(arg), detail::real_metric_space());
	}

	template<class CoefficientType, class Expression, class MetricSpaceType>
	constexpr decltype(auto) rnorm(clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(sqrt(sp(lazy.argument<0>(), reversion(lazy.argument<0>()), mtr)));
	}

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) rnorm(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		return rnorm(arg, detail::real_metric_space());
	}

	template<class Type, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) rnorm(Type const &arg, metric_space<MetricSpaceType> const &) {
		return rnorm(scalar(arg), detail::real_metric_space());
	}

	template<class Type, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) rnorm(Type const &arg) {
		return rnorm(scalar(arg), detail::real_metric_space());
	}

}

#endif // __GA_REVERSE_NORM_HPP__
