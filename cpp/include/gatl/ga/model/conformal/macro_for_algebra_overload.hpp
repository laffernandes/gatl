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

#ifndef __GA_MODEL_CONFORMAL_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_MODEL_CONFORMAL_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define _GA_CONFORMAL_ALGEBRA_OVERLOAD(SPACE) \
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
    constexpr decltype(auto) dual_flat_direction(clifford_expression<CoefficientType, Expression> const &dual_flat) GA_NOEXCEPT { \
        return dual_flat_direction(dual_flat, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) dual_flat_location(clifford_expression<CoefficientType, Expression> const &dual_flat) { \
        return dual_flat_location(dual_flat, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) dual_round_direction(clifford_expression<CoefficientType, Expression> const &dual_round) GA_NOEXCEPT { \
        return dual_round_direction(dual_round, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) dual_round_location(clifford_expression<CoefficientType, Expression> const &dual_round) { \
        return dual_round_location(dual_round, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) dual_round_size_sqr(clifford_expression<CoefficientType, Expression> const &dual_round) { \
        return dual_round_size_sqr(dual_round, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) dual_tangent_direction(clifford_expression<CoefficientType, Expression> const &dual_tangent) GA_NOEXCEPT { \
        return dual_tangent_direction(dual_tangent, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) dual_tangent_location(clifford_expression<CoefficientType, Expression> const &dual_tangent) { \
        return dual_tangent_location(dual_tangent, SPACE); \
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
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) primal_flat_direction(clifford_expression<CoefficientType, Expression> const &primal_flat) GA_NOEXCEPT { \
        return primal_flat_direction(primal_flat, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) primal_flat_location(clifford_expression<CoefficientType, Expression> const &primal_flat) { \
        return primal_flat_location(primal_flat, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) primal_round_direction(clifford_expression<CoefficientType, Expression> const &primal_round) GA_NOEXCEPT { \
        return primal_round_direction(primal_round, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) primal_round_location(clifford_expression<CoefficientType, Expression> const &primal_round) { \
        return primal_round_location(primal_round, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) primal_round_size_sqr(clifford_expression<CoefficientType, Expression> const &primal_round) { \
        return primal_round_size_sqr(primal_round, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) primal_tangent_direction(clifford_expression<CoefficientType, Expression> const &primal_tangent) GA_NOEXCEPT { \
        return primal_tangent_direction(primal_tangent, SPACE); \
    } \
    \
    template<typename CoefficientType, typename Expression> \
    constexpr decltype(auto) primal_tangent_location(clifford_expression<CoefficientType, Expression> const &primal_tangent) { \
        return primal_tangent_location(primal_tangent, SPACE); \
    }

#endif // __GA_MODEL_CONFORMAL_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
