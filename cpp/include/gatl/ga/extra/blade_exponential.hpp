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

#ifndef __GA_EXTRA_BLADE_EXPONENTIATION_HPP__
#define __GA_EXTRA_BLADE_EXPONENTIATION_HPP__

namespace ga {

    template<typename CoefficientType, typename Expression, typename ToleranceType, typename MetricSpaceType>
    constexpr decltype(auto) exp(clifford_expression<CoefficientType, Expression> const &arg, ToleranceType const &tol, metric_space<MetricSpaceType> const &) {
        using lazy_context_type = decltype(make_lazy_context(arg, scalar(tol)));

        using blade_expression = typename lazy_context_type::template argument_expression_t<0>;
        using tolerance_value = detail::coefficient_t<typename lazy_context_type::template argument_expression_t<1> >;

        using signed_squared_alpha_value = detail::coefficient_t<detail::product_t<blade_expression, blade_expression, detail::metric_space_mapping_t<MetricSpaceType, detail::sp_mapping> > >;
        using squared_alpha_value = detail::absolute_t<signed_squared_alpha_value>;
        using alpha_value = detail::power_t<squared_alpha_value, detail::power_t<detail::constant_value<2>, detail::constant_value<-1> > >;

        using scalar_coefficient_value = detail::if_else_t<
            detail::less_or_equal_t<squared_alpha_value, tolerance_value>,
            detail::constant_value<1>,
            detail::if_else_t<
                detail::less_or_equal_t<signed_squared_alpha_value, detail::constant_value<0> >,
                detail::cosine_t<alpha_value>,
                detail::hyperbolic_cosine_t<alpha_value>
            >
        >;

        using blade_weight_value = detail::if_else_t<
            detail::less_or_equal_t<squared_alpha_value, tolerance_value>,
            detail::constant_value<1>,
            detail::if_else_t<
                detail::less_or_equal_t<signed_squared_alpha_value, detail::constant_value<0> >,
                detail::product_t<detail::sine_t<alpha_value>, detail::power_t<alpha_value, detail::constant_value<-1> >, detail::value_mapping>,
                detail::product_t<detail::hyperbolic_sine_t<alpha_value>, detail::power_t<alpha_value, detail::constant_value<-1> >, detail::value_mapping>
            >
        >;

        using result_expression = detail::addition_t<
            detail::component_t<scalar_coefficient_value, detail::constant_basis_blade<bitset_t(0)> >,
            detail::product_t<
                detail::component_t<blade_weight_value, detail::constant_basis_blade<bitset_t(0)> >,
                blade_expression,
                detail::exterior_product_mapping<MetricSpaceType::vector_space_dimensions>
            >
        >;

        lazy_context_type const lazy = make_lazy_context(arg, scalar(tol));
        return lazy.eval(clifford_expression<default_integral_t, result_expression>());
    }

    template<typename CoefficientType, typename Expression, typename MetricSpaceType>
    constexpr decltype(auto) exp(clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
        return exp(arg, default_tolerance<CoefficientType>(), mtr);
    }

    template<typename CoefficientType, typename Coefficient, typename ToleranceType, typename MetricSpaceType>
    constexpr decltype(auto) exp(scalar_clifford_expression<CoefficientType, Coefficient> const &arg, ToleranceType const &, metric_space<MetricSpaceType> const &) {
        return exp(arg);
    }

    template<typename CoefficientType, typename Coefficient, typename MetricSpaceType>
    constexpr decltype(auto) exp(scalar_clifford_expression<CoefficientType, Coefficient> const &arg, metric_space<MetricSpaceType> const &) {
        return exp(arg);
    }

    template<typename Type, typename ToleranceType, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<Type>, int> = 0>
    constexpr decltype(auto) exp(Type const &arg, ToleranceType const &, metric_space<MetricSpaceType> const &) {
        return exp(arg);
    }

    template<typename Type, typename MetricSpaceType, std::enable_if_t<!is_clifford_expression_v<Type>, int> = 0>
    constexpr decltype(auto) exp(Type const &arg, metric_space<MetricSpaceType> const &) {
        return exp(arg);
    }

    template<typename Type, typename ToleranceType, std::enable_if_t<!(is_clifford_expression_v<Type> || is_metric_space_v<ToleranceType>), int> = 0>
    constexpr decltype(auto) exp(Type const &arg, ToleranceType const &) {
        return exp(arg);
    }

}

#endif // __GA_EXTRA_BLADE_EXPONENTIATION_HPP__
