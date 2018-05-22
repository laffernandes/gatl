#ifndef __FUTURE_GA_VERSOR_INVERSE_HPP__
#define __FUTURE_GA_VERSOR_INVERSE_HPP__

namespace ga {

	template<class CoefficientType, class Expression, class MetricSpaceType>
	constexpr decltype(auto) inv(clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		constexpr auto lazy = make_lazy_context(arg);
		return lazy.eval(gp(reversion(lazy.argument<0>()), inv(rnorm_sqr(lazy.argument<0>(), mtr))));
	}

	template<class CoefficientType, class Expression, class = std::enable_if_t<detail::is_scalar_expression_v<Expression> > >
	constexpr decltype(auto) inv(clifford_expression<CoefficientType, Expression> const &arg) {
		typedef detail::lazy_arguments<Expression> lazy;
		return detail::eval<detail::component_t<detail::power_t<detail::coefficient_t<lazy::argument_expression_t<0> >, detail::constant_value<-1> >, detail::constant_basis_blade<default_bitset_t(0)> > >(arg);
	}

	template<class Type, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) inv(Type const &arg, metric_space<MetricSpaceType> const &) {
		return inv(scalar(arg));
	}

	template<class Type, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) inv(Type const &arg) {
		return inv(scalar(arg));
	}

}

#endif // __FUTURE_GA_VERSOR_INVERSE_HPP__

