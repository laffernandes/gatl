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

#ifndef __GA_CORE_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_CORE_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define _GA_CORE_OVERLOAD(SPACE) \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
    constexpr decltype(auto) dot(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return dot(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression > \
    constexpr decltype(auto) operator|(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return dot(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
    constexpr decltype(auto) gp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return gp(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression > \
    constexpr decltype(auto) operator*(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return gp(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
    constexpr decltype(auto) hip(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return hip(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
    constexpr decltype(auto) lcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return lcont(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression > \
    constexpr decltype(auto) operator<(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return lcont(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
    constexpr decltype(auto) op(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return op(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression > \
    constexpr decltype(auto) operator^(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return op(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
    constexpr decltype(auto) rcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return rcont(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression > \
    constexpr decltype(auto) operator>(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return rcont(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
    constexpr decltype(auto) rp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return rp(lhs, rhs, SPACE); \
    } \
    \
    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename = std::enable_if_t<!is_clifford_expression_v<RightType> > > \
    constexpr decltype(auto) rp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) noexcept { \
        return rp(lhs, scalar(rhs), SPACE); \
    } \
	\
    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename = std::enable_if_t<!is_clifford_expression_v<LeftType> > > \
    constexpr decltype(auto) rp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return rp(scalar(lhs), rhs, SPACE); \
    } \
	\
    template<typename LeftType, typename RightType, typename = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> > \
    constexpr decltype(auto) rp(LeftType const &lhs, RightType const &rhs) noexcept { \
        return rp(scalar(lhs), scalar(rhs), SPACE); \
    } \
	\
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression> \
    constexpr decltype(auto) sp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept { \
        return sp(lhs, rhs, SPACE); \
    }

#endif // __GA_CORE_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__