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

#ifndef __GA_CORE_EXPRESSION_ADDITION_HPP__
#define __GA_CORE_EXPRESSION_ADDITION_HPP__

namespace ga {

    namespace detail {

        // zero + something => something (simplify)
        struct _addition_rule_zero_left {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftBasisBlade, typename RightExpression>
            struct condition<component<constant_value<0>, LeftBasisBlade>, RightExpression> {
                constexpr static bool value = true;
            };

            template<typename RightExpression>
            struct condition<constant_value<0>, RightExpression> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = RightExpression;
            };
        };

        // something + zero => something (simplify)
        struct _addition_rule_zero_right {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftExpression, typename RightBasisBlade>
            struct condition<LeftExpression, component<constant_value<0>, RightBasisBlade> > {
                constexpr static bool value = true;
            };

            template<typename LeftExpression>
            struct condition<LeftExpression, constant_value<0> > {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = LeftExpression;
            };
        };

        // A * Ei + B * Ei => (A + B) * Ei (simplify)
        struct _addition_rule_collect_constant_basis_blade {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftCoefficient, typename BasisBlade, typename RightCoefficient>
            struct condition<component<LeftCoefficient, BasisBlade>, component<RightCoefficient, BasisBlade> > {
                constexpr static bool value = is_constant_expression_v<BasisBlade>;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;
            
            template<typename LeftCoefficient, typename BasisBlade, typename RightCoefficient>
            struct result<component<LeftCoefficient, BasisBlade>, component<RightCoefficient, BasisBlade> > {
                using type = component_t<addition_t<LeftCoefficient, RightCoefficient>, BasisBlade>;
            };
        };

        // A * Ei + B * Ej => add<A * Ei, B * Ej> (no simplification found, bind)
        struct _addition_rule_bind_components {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade>
            struct condition<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > {
                constexpr static bool value = lt_v<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> >;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = add_t<LeftExpression, RightExpression>;
            };
        };

        // B * Ej + A * Ei => add<A * Ei, B * Ej> (no simplification found, sort and bind)
        struct _addition_rule_sort_and_bind_components {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade>
            struct condition<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > {
                constexpr static bool value = true; // Because the condition of previous rule is false
            };

            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = add_t<RightExpression, LeftExpression>;
            };
        };

        // add<...> + something => add<...> (merge)
        struct _addition_rule_merge_case_1 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct condition<add<LeftArgument, LeftNextArguments...>, RightExpression> {
                constexpr static bool value = lt_v<RightExpression, LeftArgument>;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<add<LeftArgument, LeftNextArguments...>, RightExpression> {
                using type = addition_t<RightExpression, add<LeftArgument, LeftNextArguments...> >;
            };
        };

        // add<...> + something => add<...> (merge)
        struct _addition_rule_merge_case_2 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct condition<add<LeftArgument, LeftNextArguments...>, RightExpression> {
                constexpr static bool value = true; // Because the condition of previous rule is false
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<add<LeftArgument, LeftNextArguments...>, RightExpression> {
                using type = addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, RightExpression> >;
            };
        };

        // something + add<...> => add<...> (merge)
        struct _addition_rule_merge_case_3 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct condition<LeftExpression, add<RightArgument, RightNextArguments...> > {
                constexpr static bool value = lt_v<RightArgument, LeftExpression>;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, add<RightArgument, RightNextArguments...> > {
                using type = addition_t<RightArgument, addition_t<LeftExpression, add_t<RightNextArguments...> > >;
            };
        };

        // something + add<...> => add<...> (no simplification found, bind)
        struct _addition_rule_merge_case_4 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct condition<LeftExpression, add<RightArgument, RightNextArguments...> > {
                constexpr static bool value = std::is_same_v<addition_t<LeftExpression, RightArgument>, add<LeftExpression, RightArgument> >; // Because the condition of previous rule is false
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, add<RightArgument, RightNextArguments...> > {
                using type = add_t<LeftExpression, RightArgument, RightNextArguments...>;
            };
        };

        // something + add<...> => add<...> (simplify-and-merge)
        struct _addition_rule_merge_case_5 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct condition<LeftExpression, add<RightArgument, RightNextArguments...> > {
                constexpr static bool value = true; // Because the condition of previous rule is false
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, add<RightArgument, RightNextArguments...> > {
                using type = addition_t<addition_t<LeftExpression, RightArgument>, add_t<RightNextArguments...> >;
            };
        };

        // A + A => 2 * A (simplify)
        struct _addition_rule_collect_value_case_1 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename CommonExpression>
            struct condition<CommonExpression, CommonExpression> {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<typename CommonExpression>
            struct result<CommonExpression, CommonExpression> {
                using type = product_t<constant_value<2>, CommonExpression, value_mapping>;
            };
        };

        // (P * A * ...) + (A * ...) => (P + 1) * (A * ...) (simplify)
        struct _addition_rule_collect_value_case_2 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftLeftArgument, typename CommonArgument>
            struct condition<mul<LeftLeftArgument, CommonArgument>, CommonArgument> {
                constexpr static bool value = !is_any_v<addition_t<LeftLeftArgument, constant_value<1> >, add_t<LeftLeftArgument, constant_value<1> >, add_t<constant_value<1>, LeftLeftArgument> >;
            };

            template<typename LeftLeftArgument, typename... CommonArguments>
            struct condition<mul<LeftLeftArgument, CommonArguments...>, mul<CommonArguments...> > {
                constexpr static bool value = !is_any_v<addition_t<LeftLeftArgument, constant_value<1> >, add_t<LeftLeftArgument, constant_value<1> >, add_t<constant_value<1>, LeftLeftArgument > >;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<typename LeftLeftArgument, typename CommonArgument>
            struct result<mul<LeftLeftArgument, CommonArgument>, CommonArgument> {
                using type = product_t<addition_t<LeftLeftArgument, constant_value<1> >, CommonArgument, value_mapping>;
            };

            template<typename LeftLeftArgument, typename... CommonArguments>
            struct result<mul<LeftLeftArgument, CommonArguments...>, mul<CommonArguments...> > {
                using type = product_t<addition_t<LeftLeftArgument, constant_value<1> >, mul_t<CommonArguments...>, value_mapping>;
            };
        };

        // A * ... + (P * A * ...) => (1 + P) * (A * ...) (simplify)
        struct _addition_rule_collect_value_case_3 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename CommonArgument, typename RightLeftArgument>
            struct condition<CommonArgument, mul<RightLeftArgument, CommonArgument> > {
                constexpr static bool value = !is_any_v<addition_t<constant_value<1>, RightLeftArgument>, add_t<constant_value<1>, RightLeftArgument>, add_t<RightLeftArgument, constant_value<1> > >;
            };

            template<typename... CommonArguments, typename RightLeftArgument>
            struct condition<mul<CommonArguments...>, mul<RightLeftArgument, CommonArguments...> > {
                constexpr static bool value = !is_any_v<addition_t<constant_value<1>, RightLeftArgument>, add_t<constant_value<1>, RightLeftArgument>, add_t<RightLeftArgument, constant_value<1> > >;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<typename CommonArgument, typename RightLeftArgument>
            struct result<CommonArgument, mul<RightLeftArgument, CommonArgument> > {
                using type = product_t<addition_t<constant_value<1>, RightLeftArgument>, CommonArgument, value_mapping>;
            };

            template<typename... CommonArguments, typename RightLeftArgument>
            struct result<mul<CommonArguments...>, mul<RightLeftArgument, CommonArguments...> > {
                using type = product_t<addition_t<constant_value<1>, RightLeftArgument>, mul_t<CommonArguments...>, value_mapping>;
            };
        };

        // (P * A * ...) + (Q * A * ...) => (P + Q) * (A * ...) (simplify)
        struct _addition_rule_collect_value_case_4 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<typename LeftLeftArgument, typename CommmonArgument, typename RightLeftArgument>
            struct condition<mul<LeftLeftArgument, CommmonArgument>, mul<RightLeftArgument, CommmonArgument> > {
                constexpr static bool value = !is_any_v<addition_t<LeftLeftArgument, RightLeftArgument>, add_t<LeftLeftArgument, RightLeftArgument>, add_t<RightLeftArgument, LeftLeftArgument> >;
            };

            template<typename LeftLeftArgument, typename... CommonArguments, typename RightLeftArgument>
            struct condition<mul<LeftLeftArgument, CommonArguments...>, mul<RightLeftArgument, CommonArguments...> > {
                constexpr static bool value = !is_any_v<addition_t<LeftLeftArgument, RightLeftArgument>, add_t<LeftLeftArgument, RightLeftArgument>, add_t<RightLeftArgument, LeftLeftArgument> >;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<typename LeftLeftArgument, typename CommmonArgument, typename RightLeftArgument>
            struct result<mul<LeftLeftArgument, CommmonArgument>, mul<RightLeftArgument, CommmonArgument> > {
                using type = product_t<addition_t<LeftLeftArgument, RightLeftArgument>, CommmonArgument, value_mapping>;
            };

            template<typename LeftLeftArgument, typename... CommonArguments, typename RightLeftArgument>
            struct result<mul<LeftLeftArgument, CommonArguments...>, mul<RightLeftArgument, CommonArguments...> > {
                using type = product_t<addition_t<LeftLeftArgument, RightLeftArgument>, mul_t<CommonArguments...>, value_mapping>;
            };
        };

        // A + B => C, with constant arguments (simplify)
        struct _addition_rule_constants_case_1 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<constant_value<LeftValue>, constant_value<RightValue> > {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<constant_value<LeftValue>, constant_value<RightValue> > {
                using type = constant_value<LeftValue + RightValue>;
            };
        };

        // A + 1 / B => (A * B + 1) / B, with constant arguments (simplify)
        struct _addition_rule_constants_case_2 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> > > {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> > > {
                using type = product_t<constant_value<LeftValue * RightValue + 1>, power_t<constant_value<RightValue>, constant_value<-1> >, value_mapping>;
            };
        };

        // 1 / A + B => (1 + B * A) / A, with constant arguments (simplify)
        struct _addition_rule_constants_case_3 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue> > {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue> > {
                using type = product_t<constant_value<1 + RightValue * LeftValue>, power_t<constant_value<LeftValue>, constant_value<-1> >, value_mapping>;
            };
        };

        // A / B + 1 / C => (A * C + B) / (B * C), with constant arguments (simplify)
        struct _addition_rule_constants_case_4 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightValue>
            struct condition<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, power<constant_value<RightValue>, constant_value<-1> > > {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightValue>
            struct result<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, power<constant_value<RightValue>, constant_value<-1> > > {
                using type = product_t<constant_value<LeftLeftValue * RightValue + LeftRightValue>, power_t<constant_value<LeftRightValue * RightValue>, constant_value<-1> >, value_mapping>;
            };
        };

        // 1 / C + A / B => (B + C * A) / (C * B), with constant arguments (simplify)
        struct _addition_rule_constants_case_5 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<default_integral_t LeftValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
            struct condition<power<constant_value<LeftValue>, constant_value<-1> >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<default_integral_t LeftValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
            struct result<power<constant_value<LeftValue>, constant_value<-1> >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
                using type = product_t<constant_value<RightRightValue + LeftValue * RightLeftValue>, power_t<constant_value<LeftValue * RightRightValue>, constant_value<-1> >, value_mapping>;
            };
        };

        // 1 / B + 1 / C => (C + B) / (B * C), with constant arguments (simplify)
        struct _addition_rule_constants_case_6 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> > > {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> > > {
                using type = product_t<constant_value<RightValue + LeftValue>, power_t<constant_value<LeftValue * RightValue>, constant_value<-1> >, value_mapping>;
            };
        };

        // A / B + C / D => (A * D + B * C) / (B * D), with constant arguments (simplify)
        struct _addition_rule_constants_case_7 {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = false;
            };

            template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
            struct condition<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
                constexpr static bool value = true;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
            struct result<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
                using type = product_t<constant_value<LeftLeftValue * RightRightValue + LeftRightValue * RightLeftValue>, power_t<constant_value<LeftRightValue * RightRightValue>, constant_value<-1> >, value_mapping>;
            };
        };

        // A + B => add<A, B> (no simplification found, bind)
        struct _addition_rule_bind_expressions {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = lt_v<LeftExpression, RightExpression>;
            };

            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = add_t<LeftExpression, RightExpression>;
            };
        };

        // B + A => add<A, B> (no simplification found, sort and bind)
        struct _addition_rule_sort_and_bind_expressions {
            template<typename LeftExpression, typename RightExpression>
            struct condition {
                constexpr static bool value = true; // Because the condition of previous rule is false
            };

            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = add_t<RightExpression, LeftExpression>;
            };            
        };

        // Implementation of _addition<LeftExpression, RightExpression>.
        template<typename LeftExpression, typename RightExpression>
        struct _addition :
            apply_rule_for_t<
                rules<
                    _addition_rule_zero_left,
                    _addition_rule_zero_right,
                    _addition_rule_collect_constant_basis_blade,
                    _addition_rule_bind_components,
                    _addition_rule_sort_and_bind_components,
                    _addition_rule_merge_case_1,
                    _addition_rule_merge_case_2,
                    _addition_rule_merge_case_3,
                    _addition_rule_merge_case_4,
                    _addition_rule_merge_case_5,
                    _addition_rule_collect_value_case_1,
                    _addition_rule_collect_value_case_2,
                    _addition_rule_collect_value_case_3,
                    _addition_rule_collect_value_case_4,
                    _addition_rule_constants_case_1,
                    _addition_rule_constants_case_2,
                    _addition_rule_constants_case_3,
                    _addition_rule_constants_case_4,
                    _addition_rule_constants_case_5,
                    _addition_rule_constants_case_6,
                    _addition_rule_constants_case_7,
                    _addition_rule_bind_expressions,
                    _addition_rule_sort_and_bind_expressions
                >,
                LeftExpression, RightExpression
            > {
        };
        
    }

}

#endif // __GA_CORE_EXPRESSION_ADDITION_HPP__
