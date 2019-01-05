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

#ifndef __GA_CORE_ARITHMETIC_OPERATORS_HPP__
#define __GA_CORE_ARITHMETIC_OPERATORS_HPP__

namespace ga {

    template<typename RightCoefficientType, typename RightExpression>
    constexpr clifford_expression<RightCoefficientType, RightExpression> operator+(clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return rhs;
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) operator+(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        auto lazy = make_lazy_context(lhs, rhs);
        return lazy.eval(clifford_expression<default_integral_t, detail::addition_t<typename decltype(lazy)::template argument_expression_t<0>, typename decltype(lazy)::template argument_expression_t<1> > >());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType>
    constexpr decltype(auto) operator+(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) noexcept {
        return lhs + scalar(rhs);
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) operator+(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return scalar(lhs) + rhs;
    }

    template<typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) operator-(clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return gp(c<-1>, rhs);
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) operator-(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        auto const lazy = make_lazy_context(lhs, rhs);
        return lazy.eval(lazy.template argument<0>() + gp(c<-1>, lazy.template argument<1>()));
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType>
    constexpr decltype(auto) operator-(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) noexcept {
        return lhs - scalar(rhs);
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) operator-(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return scalar(lhs) - rhs;
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) operator*(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return gp(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) operator*(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) noexcept {
        return gp(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) operator*(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) noexcept {
        return gp(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename = std::enable_if_t<!is_clifford_expression_v<RightType> > >
    constexpr decltype(auto) operator*(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) noexcept {
        return gp(lhs, scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
    constexpr decltype(auto) operator*(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return gp(scalar(lhs), rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) operator^(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return op(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) operator^(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) noexcept {
        return op(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) operator^(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) noexcept {
        return op(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename = std::enable_if_t<!is_clifford_expression_v<RightType> > >
    constexpr decltype(auto) operator^(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) noexcept {
        return op(lhs, scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
    constexpr decltype(auto) operator^(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return op(scalar(lhs), rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) operator<(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return lcont(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) operator<(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) noexcept {
        return lcont(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) operator<(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) noexcept {
        return lcont(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename = std::enable_if_t<!is_clifford_expression_v<RightType> > >
    constexpr decltype(auto) operator<(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) noexcept {
        return lcont(lhs, scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
    constexpr decltype(auto) operator<(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return lcont(scalar(lhs), rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) operator>(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return rcont(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) operator>(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) noexcept {
        return rcont(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) operator>(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) noexcept {
        return rcont(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename = std::enable_if_t<!is_clifford_expression_v<RightType> > >
    constexpr decltype(auto) operator>(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) noexcept {
        return rcont(lhs, scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
    constexpr decltype(auto) operator>(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return rcont(scalar(lhs), rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightExpression>
    constexpr decltype(auto) operator|(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return dot(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) operator|(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) noexcept {
        return dot(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient>
    constexpr decltype(auto) operator|(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) noexcept {
        return dot(lhs, rhs, detail::real_metric_space());
    }

    template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename = std::enable_if_t<!is_clifford_expression_v<RightType> > >
    constexpr decltype(auto) operator|(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) noexcept {
        return dot(lhs, scalar(rhs), detail::real_metric_space());
    }

    template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
    constexpr decltype(auto) operator|(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) noexcept {
        return dot(scalar(lhs), rhs, detail::real_metric_space());
    }

}

#endif // __GA_CORE_ARITHMETIC_OPERATORS_HPP__
