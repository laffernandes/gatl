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

#ifndef __GA_EXTRA_UNIT_HPP__
#define __GA_EXTRA_UNIT_HPP__

namespace ga {

	// Computes the unit multivector under reverse norm.
	template<typename CoefficientType, typename Expression, typename MetricSpaceType>
	constexpr decltype(auto) unit(clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(gp(lazy.argument<0>(), inv(sqrt(abs(sp(lazy.argument<0>(), reversion(lazy.argument<0>()), mtr))), mtr), mtr));
	}

}

#endif // __GA_EXTRA_UNIT_HPP__
