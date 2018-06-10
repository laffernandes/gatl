#ifndef __FUTURE_GA_MATH_HPP__
#define __FUTURE_GA_MATH_HPP__

namespace ga {

	using std::pow;

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) pow(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		auto const lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::power_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> >, detail::coefficient_t<decltype(lazy)::argument_expression_t<1> > > >());
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) pow(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, RightType const &rhs) {
		return pow(lhs, scalar(rhs));
	}

	template<class LeftType, class RightCoefficientType, class RightCoefficient, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) pow(LeftType const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return pow(scalar(lhs), rhs);
	}

	using std::sqrt;

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) sqrt(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		return pow(arg, scalar_clifford_expression<CoefficientType, detail::power_t<detail::constant_value<2>, detail::constant_value<-1> > >());
	}

	using std::cbrt;

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) cbrt(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		return pow(arg, scalar_clifford_expression<CoefficientType, detail::power_t<detail::constant_value<3>, detail::constant_value<-1> > >());
	}

	using std::abs;

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) abs(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::absolute_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::exp;

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) exp(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::exponential_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::log;

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) log(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::logarithm_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::cos;

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) cos(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::cosine_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::sin;

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) sin(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::sine_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::tan;

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) tan(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::tangent_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::cosh;

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) cosh(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::hyperbolic_cosine_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::sinh;

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) sinh(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::hyperbolic_sine_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::tanh;

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) tanh(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::hyperbolic_tangent_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

}

#endif // __FUTURE_GA_MATH_HPP__