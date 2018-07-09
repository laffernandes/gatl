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

#ifndef __GA_EXTRA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_EXTRA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define _GA_EXTRA_OVERLOAD(SPACE, BASIS_VECTORS_NAMES) \
	template<typename VersorType, typename Type> \
	constexpr decltype(auto) apply_even_versor(VersorType const &versor, Type const &arg) { \
		return apply_even_versor(versor, arg, SPACE); \
	} \
	\
	template<typename VersorType, typename Type> \
	constexpr decltype(auto) apply_odd_versor(VersorType const &versor, Type const &arg) { \
		return apply_odd_versor(versor, arg, SPACE); \
	} \
	\
	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
	constexpr decltype(auto) cp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
		return cp(lhs, rhs, SPACE); \
	} \
	\
	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename ToleranceType, typename = std::enable_if_t<!is_metric_space_v<ToleranceType> > > \
	constexpr decltype(auto) dp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol) noexcept { \
		return dp(lhs, rhs, tol, SPACE); \
	} \
	\
	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
	constexpr decltype(auto) dp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
		return dp(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), SPACE); \
	} \
	\
	template<typename Type, typename PseudoscalarCoefficientType, typename PseudoscalarExpression> \
	constexpr decltype(auto) dual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar) { \
		return dual(arg, pseudoscalar, SPACE); \
	} \
	\
	template<typename Type> \
	constexpr decltype(auto) dual(Type const &arg) { \
		return dual(arg, pseudoscalar(SPACE), SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression, typename ToleranceType, typename = std::enable_if_t<!is_metric_space_v<ToleranceType> > > \
	constexpr decltype(auto) exp(clifford_expression<CoefficientType, Expression> const &arg, ToleranceType const &tol) { \
		return exp(arg, tol, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) exp(clifford_expression<CoefficientType, Expression> const &arg) { \
		return exp(arg, default_tolerance<CoefficientType>(), SPACE); \
	} \
	\
	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename ToleranceType> \
	constexpr decltype(auto) fast_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol) { \
		return fast_join(lhs, rhs, tol, SPACE); \
	} \
	\
	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
	constexpr decltype(auto) fast_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return fast_join(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), SPACE); \
	} \
	\
	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename ToleranceType> \
	constexpr decltype(auto) fast_meet_and_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol) { \
		return fast_meet_and_join(lhs, rhs, tol, SPACE); \
	} \
	\
	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
	constexpr decltype(auto) fast_meet_and_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return fast_meet_and_join(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), SPACE); \
	} \
	\
	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
	constexpr decltype(auto) igp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return igp(lhs, rhs, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) inv(clifford_expression<CoefficientType, Expression> const &arg) { \
		return inv(arg, SPACE); \
	} \
	\
	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename ToleranceType> \
	constexpr decltype(auto) meet_and_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, ToleranceType const &tol) { \
		return meet_and_join(lhs, rhs, tol, SPACE); \
	} \
	\
	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
	constexpr decltype(auto) meet_and_join(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return meet_and_join(lhs, rhs, default_tolerance<std::common_type_t<LeftCoefficientType, RightCoefficientType> >(), SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) rnorm(clifford_expression<CoefficientType, Expression> const &arg) { \
		return rnorm(arg, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) rnorm_sqr(clifford_expression<CoefficientType, Expression> const &arg) noexcept { \
		return rnorm_sqr(arg, SPACE); \
	} \
	\
	template<typename Type, typename PseudoscalarCoefficientType, typename PseudoscalarExpression> \
	constexpr decltype(auto) undual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar) noexcept { \
		return undual(arg, pseudoscalar, SPACE); \
	} \
	\
	template<typename Type> \
	constexpr decltype(auto) undual(Type const &arg) noexcept { \
		return undual(arg, pseudoscalar(SPACE), SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) unit(clifford_expression<CoefficientType, Expression> const &arg) { \
		return unit(arg, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	std::ostream & operator <<(std::ostream &os, clifford_expression<CoefficientType, Expression> const &arg) noexcept { \
		return write(os, arg, BASIS_VECTORS_NAMES); \
	}

#endif // __GA_EXTRA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
