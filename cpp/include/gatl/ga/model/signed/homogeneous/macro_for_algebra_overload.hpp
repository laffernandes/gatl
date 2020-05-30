/* Copyright (C) Leandro Augusto Frata Fernandes
 * 
 * author     : Fernandes, Leandro A. F.
 * e-mail     : laffernandes@ic.uff.br
 * home page  : http://www.ic.uff.br/~laffernandes
 * repository : https://github.com/laffernandes/gatl.git
 * 
 * This file is part of The Geometric Algebra Template Library (GATL).
 * 
 * GATL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * GATL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GATL. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __GA_MODEL_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_MODEL_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define _GA_HOMOGENEOUS_ALGEBRA_OVERLOAD(SPACE) \
    template <typename... Types, std::enable_if_t<std::disjunction_v<std::bool_constant<!detail::is_iterator_v<Types> >...>, int> = 0> \
    constexpr decltype(auto) euclidean_vector(Types &&... coords) GA_NOEXCEPT { \
        return euclidean_vector(SPACE, std::move(coords)...); \
    } \
    \
    template <typename IteratorType, std::enable_if_t<detail::is_iterator_v<IteratorType>, int> = 0> \
    constexpr decltype(auto) euclidean_vector(IteratorType begin, IteratorType end) GA_NOEXCEPT { \
        return euclidean_vector(SPACE, begin, end); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) flat_direction(clifford_expression<CoefficientType, Expression> const &flat) GA_NOEXCEPT { \
        return flat_direction(flat, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) flat_support_vector(clifford_expression<CoefficientType, Expression> const &flat) { \
        return flat_support_vector(flat, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) flat_moment(clifford_expression<CoefficientType, Expression> const &flat) GA_NOEXCEPT { \
        return flat_moment(flat, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) flat_unit_support_point(clifford_expression<CoefficientType, Expression> const &flat) { \
        return flat_unit_support_point(flat, SPACE); \
    } \
    \
    template <typename... Types, std::enable_if_t<std::disjunction_v<std::bool_constant<!detail::is_iterator_v<Types> >...>, int> = 0> \
    constexpr decltype(auto) point(Types &&... coords) GA_NOEXCEPT { \
        return point(SPACE, std::move(coords)...); \
    } \
    \
    template <typename IteratorType, std::enable_if_t<detail::is_iterator_v<IteratorType>, int> = 0> \
    constexpr decltype(auto) point(IteratorType begin, IteratorType end) GA_NOEXCEPT { \
        return point(SPACE, begin, end); \
    } \
    \
    template<typename DirectionCoefficientType, typename DirectionExpression, typename CoefficientType, typename Expression> \
    constexpr decltype(auto) translate(clifford_expression<DirectionCoefficientType, DirectionExpression> const &direction, clifford_expression<CoefficientType, Expression> const &flat) GA_NOEXCEPT { \
        return translate(direction, flat, SPACE); \
    }

#endif // __GA_MODEL_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
