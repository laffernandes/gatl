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

#ifndef __GA_CORE_EXPRESSION_PRODUCT_HPP__
#define __GA_CORE_EXPRESSION_PRODUCT_HPP__

namespace ga {

    namespace detail {

        // Returns the simpler rational constant.
        template<default_integral_t Numerator, default_integral_t Denominator, default_integral_t GreatestCommonDivisor = gcd(iabs(Numerator), iabs(Denominator))>
        struct simpler_rational_constant {
            using type = product_t<constant_value<(sign(Numerator) * sign(Denominator)) * (iabs(Numerator) / GreatestCommonDivisor)>, power_t<constant_value<iabs(Denominator) / GreatestCommonDivisor>, constant_value<-1> >, value_mapping>;
        };

        template<default_integral_t Numerator, default_integral_t Denominator>
        struct simpler_rational_constant<Numerator, Denominator, 1> {
            using type = mul_t<constant_value<(sign(Numerator) * sign(Denominator)) * iabs(Numerator)>, power_t<constant_value<iabs(Denominator)>, constant_value<-1> > >;
        };

        template<default_integral_t Numerator, default_integral_t Denominator>
        using simpler_rational_constant_t = typename simpler_rational_constant<Numerator, Denominator>::type;

        // zero * something => zero (simplify)
        struct _product_rule_zero_left {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftBasisBlade, typename RightExpression, typename Mapping>
            struct condition<component<constant_value<0>, LeftBasisBlade>, RightExpression, Mapping> {
                constexpr static bool value = true;
            };

            template<typename RightExpression>
            struct condition<constant_value<0>, RightExpression, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftBasisBlade, typename RightExpression, typename Mapping>
            struct result<component<constant_value<0>, LeftBasisBlade>, RightExpression, Mapping> {
                using type = component<constant_value<0>, LeftBasisBlade>;
            };

            template<typename RightExpression>
            struct result<constant_value<0>, RightExpression, value_mapping> {
                using type = constant_value<0>;
            };
        };
        
        // something * zero => zero (simplify)
        struct _product_rule_zero_right {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftExpression, typename RightBasisBlade, typename Mapping>
            struct condition<LeftExpression, component<constant_value<0>, RightBasisBlade>, Mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression>
            struct condition<LeftExpression, constant_value<0>, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftExpression, typename RightBasisBlade, typename Mapping>
            struct result<LeftExpression, component<constant_value<0>, RightBasisBlade>, Mapping> {
                using type = component<constant_value<0>, RightBasisBlade>;
            };

            template<typename LeftExpression>
            struct result<LeftExpression, constant_value<0>, value_mapping> {
                using type = constant_value<0>;
            };
        };

        // one * something => something (simplify)
        struct _product_rule_one_left {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename RightExpression, typename Mapping>
            struct condition<component<constant_value<1>, constant_basis_blade<bitset_t(0)> >, RightExpression, Mapping> {
                constexpr static bool value = true;
            };

            template<typename RightExpression>
            struct condition<constant_value<1>, RightExpression, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename RightExpression, typename Mapping>
            struct result<component<constant_value<1>, constant_basis_blade<bitset_t(0)> >, RightExpression, Mapping> {
                using type = RightExpression;
            };

            template<typename RightExpression>
            struct result<constant_value<1>, RightExpression, value_mapping> {
                using type = RightExpression;
            };
        };
        
        // something * one => something (simplify)
        struct _product_rule_one_right {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftExpression, typename Mapping>
            struct condition<LeftExpression, component<constant_value<1>, constant_basis_blade<bitset_t(0)> >, Mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression>
            struct condition<LeftExpression, constant_value<1>, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftExpression, typename Mapping>
            struct result<LeftExpression, component<constant_value<1>, constant_basis_blade<bitset_t(0)> >, Mapping> {
                using type = LeftExpression;
            };

            template<typename LeftExpression>
            struct result<LeftExpression, constant_value<1>, value_mapping> {
                using type = LeftExpression;
            };
        };

        // (A + B) * (C + D) => A * C + A * D + B * C + B * D (distributive property over addition)
        struct _product_rule_distributivity {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = is_function_v<name_t::add, LeftExpression> || is_function_v<name_t::add, RightExpression>;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments, typename Mapping>
            struct result<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, Mapping> {
                using type = addition_t<addition_t<product_t<LeftArgument, RightArgument, Mapping>, product_t<add_t<LeftNextArguments...>, RightArgument, Mapping> >, addition_t<product_t<LeftArgument, add_t<RightNextArguments...>, Mapping>, product_t<add_t<LeftNextArguments...>, add_t<RightNextArguments...>, Mapping> > >;
            };

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments, typename Mapping>
            struct result<LeftExpression, add<RightArgument, RightNextArguments...>, Mapping> {
                using type = addition_t<product_t<LeftExpression, RightArgument, Mapping>, product_t<LeftExpression, add_t<RightNextArguments...>, Mapping> >;
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression, typename Mapping>
            struct result<add<LeftArgument, LeftNextArguments...>, RightExpression, Mapping> {
                using type = addition_t<product_t<LeftArgument, RightExpression, Mapping>, product_t<add_t<LeftNextArguments...>, RightExpression, Mapping> >;
            };
        };

        // (A * Ei) * (B * Ej) => some multivector (multiply components)
        template<typename Scalar, typename Components>
        struct __product_rule_distribute_while_multiplying_components;

        struct _product_rule_multiply_components {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename Mapping>
            struct condition<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename Mapping>
            struct result<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping> :
                __product_rule_distribute_while_multiplying_components<product_t<LeftCoefficient, RightCoefficient, value_mapping>, typename Mapping::template multiply<LeftBasisBlade, RightBasisBlade>::type> {
            };
        };

        template<typename Scalar, typename Coefficient, typename BasisBlade, typename... NextComponents>
        struct __product_rule_distribute_while_multiplying_components<Scalar, add<component<Coefficient, BasisBlade>, NextComponents...> > {
            using type = addition_t<component_t<product_t<Scalar, Coefficient, value_mapping>, BasisBlade>, typename __product_rule_distribute_while_multiplying_components<Scalar, add_t<NextComponents...> >::type>;
        };

        template<typename Scalar, typename Coefficient, typename BasisBlade>
        struct __product_rule_distribute_while_multiplying_components<Scalar, component<Coefficient, BasisBlade> > {
            using type = component_t<product_t<Scalar, Coefficient, value_mapping>, BasisBlade>;
        };

        // mul<...> * something => mul<...>, with scalar values (merge)
        struct _product_rule_merge_case_1 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct condition<mul<LeftArgument, LeftNextArguments...>, RightExpression, value_mapping> {
                constexpr static bool value = lt_v<RightExpression, LeftArgument>;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<mul<LeftArgument, LeftNextArguments...>, RightExpression, value_mapping> {
                using type = product_t<RightExpression, mul<LeftArgument, LeftNextArguments...>, value_mapping>;
            };
        };

        // mul<...> * something => mul<...>, with scalar values (merge)
        struct _product_rule_merge_case_2 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct condition<mul<LeftArgument, LeftNextArguments...>, RightExpression, value_mapping> {
                constexpr static bool value = true; // Because the condition of previous rule is false
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<mul<LeftArgument, LeftNextArguments...>, RightExpression, value_mapping> {
                using type = product_t<LeftArgument, product_t<mul_t<LeftNextArguments...>, RightExpression, value_mapping>, value_mapping>;
            };
        };

        // something * mul<...> => mul<...>, with scalar values (merge)
        struct _product_rule_merge_case_3 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct condition<LeftExpression, mul<RightArgument, RightNextArguments...>, value_mapping> {
                constexpr static bool value = lt_v<RightArgument, LeftExpression>;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, mul<RightArgument, RightNextArguments...>, value_mapping> {
                using type = product_t<RightArgument, product_t<LeftExpression, mul_t<RightNextArguments...>, value_mapping>, value_mapping>;
            };
        };

        // something * mul<...> => mul<...>, with scalar values (no simplification found, bind)
        struct _product_rule_merge_case_4 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct condition<LeftExpression, mul<RightArgument, RightNextArguments...>, value_mapping> {
                constexpr static bool value = std::is_same_v<product_t<LeftExpression, RightArgument, value_mapping>, mul<LeftExpression, RightArgument> >; // Because the condition of previous rule is false
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, mul<RightArgument, RightNextArguments...>, value_mapping> {
                using type = mul_t<LeftExpression, RightArgument, RightNextArguments...>;
            };
        };

        // something * mul<...> => mul<...>, with scalar values (simplify-and-merge)
        struct _product_rule_merge_case_5 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct condition<LeftExpression, mul<RightArgument, RightNextArguments...>, value_mapping> {
                constexpr static bool value = true; // Because the condition of previous rule is false
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, mul<RightArgument, RightNextArguments...>, value_mapping> {
                using type = product_t<product_t<LeftExpression, RightArgument, value_mapping>, mul_t<RightNextArguments...>, value_mapping>;
            };
        };

        // A * A => A^{2}, with scalar values (simplify)
        struct _product_rule_collect_value_case_1 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename CommonExpression>
            struct condition<CommonExpression, CommonExpression, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename CommonExpression>
            struct result<CommonExpression, CommonExpression, value_mapping> {
                using type = power_t<CommonExpression, constant_value<2> >;
            };
        };

        // A^{P} * A => A^{P + 1}, with scalar values (simplify)
        struct _product_rule_collect_value_case_2 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename CommonArgument, typename LeftRightArgument>
            struct condition<power<CommonArgument, LeftRightArgument>, CommonArgument, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename CommonArgument, typename LeftRightArgument>
            struct result<power<CommonArgument, LeftRightArgument>, CommonArgument, value_mapping> {
                using type = power_t<CommonArgument, addition_t<LeftRightArgument, constant_value<1> > >;
            };
        };

        // A * A^{Q} => A^{1 + Q}, with scalar values (simplify)
        struct _product_rule_collect_value_case_3 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename CommonArgument, typename RightRightArgument>
            struct condition<CommonArgument, power<CommonArgument, RightRightArgument>, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename CommonArgument, typename RightRightArgument>
            struct result<CommonArgument, power<CommonArgument, RightRightArgument>, value_mapping> {
                using type = power_t<CommonArgument, addition_t<constant_value<1>, RightRightArgument> >;
            };
        };

        // A^{P} * A^{Q} => A^{P + Q}, with scalar values (simplify)
        struct _product_rule_collect_value_case_4 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename CommonArgument, typename LeftRightArgument, typename RightRightArgument>
            struct condition<power<CommonArgument, LeftRightArgument>, power<CommonArgument, RightRightArgument>, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename CommonArgument, typename LeftRightArgument, typename RightRightArgument>
            struct result<power<CommonArgument, LeftRightArgument>, power<CommonArgument, RightRightArgument>, value_mapping> {
                using type = power_t<CommonArgument, addition_t<LeftRightArgument, RightRightArgument> >;
            };
        };

        // A^{P} * A^{P} => A^{2 * P}, with scalar values (simplify)
        struct _product_rule_collect_value_case_5 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename CommonLeftArgument, typename CommonRightArgument>
            struct condition<power<CommonLeftArgument, CommonRightArgument>, power<CommonLeftArgument, CommonRightArgument>, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename CommonLeftArgument, typename CommonRightArgument>
            struct result<power<CommonLeftArgument, CommonRightArgument>, power<CommonLeftArgument, CommonRightArgument>, value_mapping> {
                using type = power_t<CommonLeftArgument, product_t<constant_value<2>, CommonRightArgument, value_mapping> >;
            };
        };

        // A * B => C, with constant scalar values (simplify)
        struct _product_rule_constants_case_1 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<constant_value<LeftValue>, constant_value<RightValue>, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<constant_value<LeftValue>, constant_value<RightValue>, value_mapping> {
                using type = constant_value<LeftValue * RightValue>;
            };
        };

        // A * B^{-1} => simpler, with constant scalar values (simplify)
        struct _product_rule_constants_case_2 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> >, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> >, value_mapping> {
                using type = simpler_rational_constant_t<LeftValue, RightValue>;
            };
        };

        // A^{-1} * B => simpler, with constant scalar values (simplify)
        struct _product_rule_constants_case_3 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue>, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue>, value_mapping> {
                using type = simpler_rational_constant_t<RightValue, LeftValue>;
            };
        };

        // A^{-1} * B^{-1} => (A * B)^{-1}, with constant scalar values (simplify)
        struct _product_rule_constants_case_4 {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> >, value_mapping> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> >, value_mapping> {
                using type = power_t<constant_value<LeftValue * RightValue>, constant_value<-1> >;
            };
        };

        // A * B => mul<A, B> (no simplification found, bind)
        struct _product_rule_bind_expressions {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftExpression, typename RightExpression>
            struct condition<LeftExpression, RightExpression, value_mapping> {
                constexpr static bool value = lt_v<LeftExpression, RightExpression>;
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftExpression, typename RightExpression>
            struct result<LeftExpression, RightExpression, value_mapping> {
                using type = mul_t<LeftExpression, RightExpression>;
            };
        };

        // B * A => mul<A, B> (no simplification found, sort and bind)
        struct _product_rule_sort_and_bind_expressions {
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftExpression, typename RightExpression>
            struct condition<LeftExpression, RightExpression, value_mapping> {
                constexpr static bool value = true; // Because the condition of previous rule is false
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            template<typename LeftExpression, typename RightExpression>
            struct result<LeftExpression, RightExpression, value_mapping> {
                using type = mul_t<RightExpression, LeftExpression>;
            };            
        };

        // Implementation of _product<LeftExpression, RightExpression, Mapping>.
        template<typename LeftExpression, typename RightExpression, typename Mapping>
        struct _product :
            apply_rule_for_t<
                rules<
                    _product_rule_zero_left,
                    _product_rule_zero_right,
                    _product_rule_one_left,
                    _product_rule_one_right,
                    _product_rule_distributivity,
                    _product_rule_multiply_components,
                    _product_rule_merge_case_1,
                    _product_rule_merge_case_2,
                    _product_rule_merge_case_3,
                    _product_rule_merge_case_4,
                    _product_rule_merge_case_5,
                    _product_rule_collect_value_case_1,
                    _product_rule_collect_value_case_2,
                    _product_rule_collect_value_case_3,
                    _product_rule_collect_value_case_4,
                    _product_rule_collect_value_case_5,
                    _product_rule_constants_case_1,
                    _product_rule_constants_case_2,
                    _product_rule_constants_case_3,
                    _product_rule_constants_case_4,
                    _product_rule_bind_expressions,
                    _product_rule_sort_and_bind_expressions
                >,
                LeftExpression, RightExpression, Mapping
            > {
        };

    }

}

#endif // __GA_CORE_EXPRESSION_PRODUCT_HPP__
