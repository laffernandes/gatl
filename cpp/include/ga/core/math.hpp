/**
Copyright (C) 2018 Leandro Augusto Frata Fernandes

author     : Fernandes, Leandro A. F.
e-mail     : laffernandes@ic.uff.br
home page  : http://www.ic.uff.br/~laffernandes
repository : https://github.com/laffernandes/gatl.git

This file is part of The Geometric Algebra Template Library (GATL).

GATL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GATL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GATL. If not, see <https://www.gnu.org/licenses/>.
/**/

#ifndef __GA_CORE_MATH_HPP__
#define __GA_CORE_MATH_HPP__

namespace ga {

	using std::pow;

	template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient>
	constexpr decltype(auto) pow(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		auto const lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::power_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> >, detail::coefficient_t<decltype(lazy)::argument_expression_t<1> > > >());
	}

	template<typename LeftCoefficientType, typename LeftCoefficient, typename RightType, typename = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) pow(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, RightType const &rhs) {
		return pow(lhs, scalar(rhs));
	}

	template<typename LeftType, typename RightCoefficientType, typename RightCoefficient, typename = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) pow(LeftType const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return pow(scalar(lhs), rhs);
	}

	using std::sqrt;

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) sqrt(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		return pow(arg, scalar_clifford_expression<CoefficientType, detail::power_t<detail::constant_value<2>, detail::constant_value<-1> > >());
	}

	using std::cbrt;

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) cbrt(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		return pow(arg, scalar_clifford_expression<CoefficientType, detail::power_t<detail::constant_value<3>, detail::constant_value<-1> > >());
	}

	using std::abs;

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) abs(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) noexcept {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::absolute_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::exp;

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) exp(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) noexcept {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::exponential_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::log;

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) log(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::logarithm_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::cos;

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) cos(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) noexcept {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::cosine_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::sin;

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) sin(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) noexcept {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::sine_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::tan;

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) tan(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) noexcept {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::tangent_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::cosh;

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) cosh(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) noexcept {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::hyperbolic_cosine_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::sinh;

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) sinh(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) noexcept {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::hyperbolic_sine_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

	using std::tanh;

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) tanh(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) noexcept {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(scalar_clifford_expression<default_integral_t, detail::hyperbolic_tangent_t<detail::coefficient_t<decltype(lazy)::argument_expression_t<0> > > >());
	}

}

#endif // __GA_CORE_MATH_HPP__