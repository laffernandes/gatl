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

#ifndef __GA_EXTRA_APPLY_VERSOR_HPP__
#define __GA_EXTRA_APPLY_VERSOR_HPP__

namespace ga {

	// Apply an even versor (i.e., an orthogonal transformation) to a Clifford expression.
	template<typename VersorCoefficientType, typename VersorExpression, typename CoefficientType, typename Expression, typename MetricSpaceType>
	constexpr decltype(auto) apply_even_versor(clifford_expression<VersorCoefficientType, VersorExpression> const &versor, clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(versor, arg);
		return lazy.eval(gp(gp(lazy.argument<0>(), lazy.argument<1>(), mtr), inv(lazy.argument<0>(), mtr), mtr));
	}

	template<typename VersorCoefficientType, typename VersorExpression, typename Type, typename MetricSpaceType>
	constexpr decltype(auto) apply_even_versor(clifford_expression<VersorCoefficientType, VersorExpression> const &versor, Type const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_even_versor(versor, scalar(arg), mtr);
	}

	template<typename VersorType, typename CoefficientType, typename Expression, typename MetricSpaceType>
	constexpr decltype(auto) apply_even_versor(VersorType const &versor, clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_even_versor(scalar(versor), arg, mtr);
	}

	template<typename VersorType, typename Type, typename MetricSpaceType>
	constexpr decltype(auto) apply_even_versor(VersorType const &versor, Type const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_even_versor(scalar(versor), scalar(arg), mtr);
	}

	// Apply an odd versor (i.e., an orthogonal transformation) to a Clifford expression.
	template<typename VersorCoefficientType, typename VersorExpression, typename CoefficientType, typename Expression, typename MetricSpaceType>
	constexpr decltype(auto) apply_odd_versor(clifford_expression<VersorCoefficientType, VersorExpression> const &versor, clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(versor, arg);
		return lazy.eval(gp(gp(lazy.argument<0>(), involution(lazy.argument<1>()), mtr), inv(lazy.argument<0>(), mtr), mtr));
	}

	template<typename VersorCoefficientType, typename VersorExpression, typename Type, typename MetricSpaceType>
	constexpr decltype(auto) apply_odd_versor(clifford_expression<VersorCoefficientType, VersorExpression> const &versor, Type const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_odd_versor(versor, scalar(arg), mtr);
	}

	template<typename VersorType, typename CoefficientType, typename Expression, typename MetricSpaceType>
	constexpr decltype(auto) apply_odd_versor(VersorType const &versor, clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_odd_versor(scalar(versor), arg, mtr);
	}

	template<typename VersorType, typename Type, typename MetricSpaceType>
	constexpr decltype(auto) apply_odd_versor(VersorType const &versor, Type const &arg, metric_space<MetricSpaceType> const &mtr) {
		return apply_odd_versor(scalar(versor), scalar(arg), mtr);
	}

}

#endif // __GA_EXTRA_APPLY_VERSOR_HPP__