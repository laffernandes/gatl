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

#ifndef __GA_MODEL_CONFORMAL_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_MODEL_CONFORMAL_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define _GA_MODEL_CONFORMAL_ALGEBRA_OVERLOAD(SPACE) \
	template <typename... Types> \
	constexpr decltype(auto) euclidean_vector(Types &&... coords) { \
		return euclidean_vector(SPACE, std::move(coords)...); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) flat_direction(clifford_expression<CoefficientType, Expression> const &flat) { \
		return flat_direction(flat, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) flat_location(clifford_expression<CoefficientType, Expression> const &flat) { \
		return flat_location(flat, SPACE); \
	} \
	\
	template <typename... Types> \
	constexpr decltype(auto) point(Types &&... coords) { \
		return point(SPACE, std::move(coords)...); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) round_direction(clifford_expression<CoefficientType, Expression> const &round) { \
		return round_direction(round, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) round_location(clifford_expression<CoefficientType, Expression> const &round) { \
		return round_location(round, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) round_size_sqr(clifford_expression<CoefficientType, Expression> const &round) { \
		return round_size_sqr(round, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) tangent_direction(clifford_expression<CoefficientType, Expression> const &tangent) { \
		return tangent_direction(tangent, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) tangent_location(clifford_expression<CoefficientType, Expression> const &tangent) { \
		return tangent_location(tangent, SPACE); \
	}

#endif // __GA_MODEL_CONFORMAL_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
