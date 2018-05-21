#ifndef __FUTURE_GA_REVERSE_NORM_HPP__
#define __FUTURE_GA_REVERSE_NORM_HPP__

namespace ga {

	template<class CoefficientType, class Expression, class MetricSpaceType>
	constexpr decltype(auto) rnorm_sqr(clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scp(lazy.argument<0>(), reversion(lazy.argument<0>()), mtr));
	}

	template<class CoefficientType, class Expression, class = std::enable_if_t<detail::is_scalar_expression_v<Expression> > >
	constexpr decltype(auto) rnorm_sqr(clifford_expression<CoefficientType, Expression> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scp(lazy.argument<0>(), lazy.argument<0>()));
	}

	template<class Type, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) rnorm_sqr(Type const &arg, metric_space<MetricSpaceType> const &) {
		return rnorm_sqr(scalar(arg));
	}

	template<class Type, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) rnorm_sqr(Type const &arg) {
		return rnorm_sqr(scalar(arg));
	}

	template<class CoefficientType, class Expression, class MetricSpaceType>
	constexpr decltype(auto) rnorm(clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(sqrt(scp(lazy.argument<0>(), reversion(lazy.argument<0>()), mtr)));
	}

	template<class CoefficientType, class Expression, class = std::enable_if_t<detail::is_scalar_expression_v<Expression> > >
	constexpr decltype(auto) rnorm(clifford_expression<CoefficientType, Expression> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(sqrt(scp(lazy.argument<0>(), lazy.argument<0>())));
	}

	template<class Type, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) rnorm(Type const &arg, metric_space<MetricSpaceType> const &) {
		return rnorm(scalar(arg));
	}

	template<class Type, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) rnorm(Type const &arg) {
		return rnorm(scalar(arg));
	}

}

#endif // __FUTURE_GA_REVERSE_NORM_HPP__
