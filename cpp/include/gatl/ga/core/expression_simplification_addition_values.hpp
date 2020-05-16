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

#ifndef __GA_CORE_EXPRESSION_SIMPLIFICATION_ADDITION_VALUES_HPP__
#define __GA_CORE_EXPRESSION_SIMPLIFICATION_ADDITION_VALUES_HPP__

namespace ga {

    namespace detail {

        // A meta-structure to help writing simplification rules on expressions having values and add<value, ...> as arguments.
        template<typename Rule>
        struct _addition_values_rule_helper {

            // Default
            template<typename LeftExpression, typename RightExpression, typename Enable = void>
            struct result {
                using type = std::nullptr_t;
            };

            // A + B => simplify(A + B)
            template<typename LeftExpression, typename RightExpression>
            struct result<LeftExpression, RightExpression, std::enable_if_t<!(is_function_v<name_t::add, LeftExpression> || is_function_v<name_t::add, RightExpression> || std::is_same_v<typename Rule::template result<LeftExpression, RightExpression>::type, std::nullptr_t>)> > {
                using type = typename Rule::template result<LeftExpression, RightExpression>::type;
            };

            // A + add<B, ...> => simplify(A + B) + add<...>
            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<!(is_function_v<name_t::add, LeftExpression> || std::is_same_v<typename Rule::template result<LeftExpression, RightArgument>::type, std::nullptr_t>)> > {
                using type = addition_t<typename Rule::template result<LeftExpression, RightArgument>::type, add_t<RightNextArguments...> >;
            };

            // add<A, ...> + B => simplify(A + B) + add<...>
            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!(is_function_v<name_t::add, RightExpression> || std::is_same_v<typename Rule::template result<LeftArgument, RightExpression>::type, std::nullptr_t>)> > {
                using type = addition_t<typename Rule::template result<LeftArgument, RightExpression>::type, add_t<LeftNextArguments...> >;
            };

            // add<A, ...> + add<B, ...> => simplify(A + B) + (add<...> + add<...>)
            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct result<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<!std::is_same_v<typename Rule::template result<LeftArgument, RightArgument>::type, std::nullptr_t> >  > {
                using type = addition_t<typename Rule::template result<LeftArgument, RightArgument>::type, addition_t<add_t<LeftNextArguments...>, add_t<RightNextArguments...> > >;
            };
        };

        // Simplification rule to avoid sum to zero.
        struct _addition_values_rule_zero {

            // Default
            template<typename LeftExpression, typename RightExpression, typename _Dummy = void>
            struct result {
                using type = std::nullptr_t;
            };

            // 0 + something => something
            template<typename RightExpression, typename _Dummy>
            struct result<constant_value<0>, RightExpression, _Dummy> {
                using type = RightExpression;
            };

            // something + 0 => something
            template<typename LeftExpression, typename _Dummy>
            struct result<LeftExpression, constant_value<0>, _Dummy> {
                using type = LeftExpression;
            };

            // 0 + 0 => 0
            template<typename _Dummy>
            struct result<constant_value<0>, constant_value<0>, _Dummy> {
                using type = constant_value<0>;
            };
        };

        // Simplification rule to collect common terms (case 1).
        struct _addition_values_rule_collect_case_1 {
            
            // Default
            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = std::nullptr_t;
            };

            // A + A => 2 * A
            template<typename CommonExpression>
            struct result<CommonExpression, CommonExpression> {
                using type = product_t<constant_value<2>, CommonExpression, value_mapping>;
            };
        };

        // Simplification rule to collect common terms (case 2).
        struct _addition_values_rule_collect_case_2 {

            // Default
            template<typename LeftExpression, typename RightExpression, typename Enable = void>
            struct result {
                using type = std::nullptr_t;
            };

            // mul<P, A...> + A... => (P + 1) * A...
            template<typename LeftLeftArgument, typename CommonArgument>
            struct result<mul<LeftLeftArgument, CommonArgument>, CommonArgument, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, constant_value<1> >, add_t<LeftLeftArgument, constant_value<1> >, add_t<constant_value<1>, LeftLeftArgument> > > > {
                using type = product_t<addition_t<LeftLeftArgument, constant_value<1> >, CommonArgument, value_mapping>;
            };

            template<typename LeftLeftArgument, typename... CommonArguments>
            struct result<mul<LeftLeftArgument, CommonArguments...>, mul<CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, constant_value<1> >, add_t<LeftLeftArgument, constant_value<1> >, add_t<constant_value<1>, LeftLeftArgument > > > > {
                using type = product_t<addition_t<LeftLeftArgument, constant_value<1> >, mul_t<CommonArguments...>, value_mapping>;
            };
        };

        // Simplification rule to collect common terms (case 3).
        struct _addition_values_rule_collect_case_3 {

            // Default
            template<typename LeftExpression, typename RightExpression, typename Enable = void>
            struct result {
                using type = std::nullptr_t;
            };

            // A... + mul<P, A...> => (1 + P) * A...
            template<typename CommonArgument, typename RightLeftArgument>
            struct result<CommonArgument, mul<RightLeftArgument, CommonArgument>, std::enable_if_t<!is_any_v<addition_t<constant_value<1>, RightLeftArgument>, add_t<constant_value<1>, RightLeftArgument>, add_t<RightLeftArgument, constant_value<1> > > > > {
                using type = product_t<addition_t<constant_value<1>, RightLeftArgument>, CommonArgument, value_mapping>;
            };

            template<typename... CommonArguments, typename RightLeftArgument>
            struct result<mul<CommonArguments...>, mul<RightLeftArgument, CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<constant_value<1>, RightLeftArgument>, add_t<constant_value<1>, RightLeftArgument>, add_t<RightLeftArgument, constant_value<1> > > > > {
                using type = product_t<addition_t<constant_value<1>, RightLeftArgument>, mul_t<CommonArguments...>, value_mapping>;
            };
        };

        // Simplification rule to collect common terms (case 4).
        struct _addition_values_rule_collect_case_4 {

            // Default
            template<typename LeftExpression, typename RightExpression, typename Enable = void>
            struct result {
                using type = std::nullptr_t;
            };

            // mul<P, A...> + mul<Q, A...> => (P + Q) * A...
            template<typename LeftLeftArgument, typename CommonArgument, typename RightLeftArgument>
            struct result<mul<LeftLeftArgument, CommonArgument>, mul<RightLeftArgument, CommonArgument>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, RightLeftArgument>, add_t<LeftLeftArgument, RightLeftArgument>, add_t<RightLeftArgument, LeftLeftArgument> > > > {
                using type = product_t<addition_t<LeftLeftArgument, RightLeftArgument>, CommonArgument, value_mapping>;
            };

            template<typename LeftLeftArgument, typename... CommonArguments, typename RightLeftArgument>
            struct result<mul<LeftLeftArgument, CommonArguments...>, mul<RightLeftArgument, CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, RightLeftArgument>, add_t<LeftLeftArgument, RightLeftArgument>, add_t<RightLeftArgument, LeftLeftArgument> > > > {
                using type = product_t<addition_t<LeftLeftArgument, RightLeftArgument>, mul_t<CommonArguments...>, value_mapping>;
            };
        };

        // Simplification rule to collect common terms (case 5).
        struct _addition_values_rule_collect_case_5 {

            // Default
            template<typename LeftExpression, typename RightExpression, typename Enable = void>
            struct result {
                using type = std::nullptr_t;
            };

            // mul<A, ...> + A => A * (mul<...> + 1)
            template<typename CommonArgument, typename... LeftNextArguments>
            struct result<mul<CommonArgument, LeftNextArguments...>, CommonArgument, std::enable_if_t<!is_any_v<addition_t<mul_t<LeftNextArguments...>, constant_value<1> >, add_t<mul_t<LeftNextArguments...>, constant_value<1> >, add_t<constant_value<1>, mul_t<LeftNextArguments...> > > > > {
                using type = product_t<CommonArgument, addition_t<mul_t<LeftNextArguments...>, constant_value<1> >, value_mapping>;
            };
        };

        // Simplification rule to collect common terms (case 6).
        struct _addition_values_rule_collect_case_6 {

            // Default
            template<typename LeftExpression, typename RightExpression, typename Enable = void>
            struct result {
                using type = std::nullptr_t;
            };

            // A + mul<A, ...> => A * (1 + mul<...>)
            template<typename CommonArgument, typename... RightNextArguments>
            struct result<CommonArgument, mul<CommonArgument, RightNextArguments...>, std::enable_if_t<!is_any_v<addition_t<constant_value<1>, mul_t<RightNextArguments...> >, add_t<constant_value<1>, mul_t<RightNextArguments...> >, add_t<mul_t<RightNextArguments...>, constant_value<1> > > > > {
                using type = product_t<CommonArgument, addition_t<constant_value<1>, mul_t<RightNextArguments...> >, value_mapping>;
            };
        };

        // Simplification rule to collect common terms (case 7).
        struct _addition_values_rule_collect_case_7 {

            // Default
            template<typename LeftExpression, typename RightExpression, typename Enable = void>
            struct result {
                using type = std::nullptr_t;
            };

            // mul<A, P...> + mul<A, Q...> => A * (mul<P...> + mul<Q...>)
            template<typename CommonArgument, typename... LeftNextArguments, typename... RightNextArguments>
            struct result<mul<CommonArgument, LeftNextArguments...>, mul<CommonArgument, RightNextArguments...>, std::enable_if_t<!is_any_v<addition_t<mul_t<LeftNextArguments...>, mul_t<RightNextArguments...> >, add_t<mul_t<LeftNextArguments...>, mul_t<RightNextArguments...> >, add_t<mul_t<RightNextArguments...>, mul_t<LeftNextArguments...> > > > > {
                using type = product_t<CommonArgument, addition_t<mul_t<LeftNextArguments...>, mul_t<RightNextArguments...> >, value_mapping>;
            };
        };
        
        // Simplification rule to produce a new constant value (case 1).
        struct _addition_values_rule_constants_case_1 {

            // Default
            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = std::nullptr_t;
            };

            // A + B => C
            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<constant_value<LeftValue>, constant_value<RightValue> > {
                using type = constant_value<LeftValue + RightValue>;
            };
        };

        // Simplification rule to produce a new constant value (case 2).
        struct _addition_values_rule_constants_case_2 {

            // Default
            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = std::nullptr_t;
            };

            // A + 1 / B => (A * B + 1) / B
            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> > > {
                using type = product_t<constant_value<LeftValue * RightValue + 1>, power_t<constant_value<RightValue>, constant_value<-1> >, value_mapping>;
            };

            // 1 / A + B => (1 + B * A) / A
            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue> > {
                using type = product_t<constant_value<1 + RightValue * LeftValue>, power_t<constant_value<LeftValue>, constant_value<-1> >, value_mapping>;
            };
        };

        // Simplification rule to produce a new constant value (case 3).
        struct _addition_values_rule_constants_case_3 {

            // Default
            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = std::nullptr_t;
            };

            // A / B + 1 / C => (A * C + B) / (B * C)
            template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightValue>
            struct result<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, power<constant_value<RightValue>, constant_value<-1> > > {
                using type = product_t<constant_value<LeftLeftValue * RightValue + LeftRightValue>, power_t<constant_value<LeftRightValue * RightValue>, constant_value<-1> >, value_mapping>;
            };

            // 1 / C + A / B => (B + C * A) / (C * B)
            template<default_integral_t LeftValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
            struct result<power<constant_value<LeftValue>, constant_value<-1> >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
                using type = product_t<constant_value<RightRightValue + LeftValue * RightLeftValue>, power_t<constant_value<LeftValue * RightRightValue>, constant_value<-1> >, value_mapping>;
            };
        };

        // Simplification rule to produce a new constant value (case 4).
        struct _addition_values_rule_constants_case_4 {

            // Default
            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = std::nullptr_t;
            };

            // 1 / B + 1 / C => (C + B) / (B * C)
            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> > > {
                using type = product_t<constant_value<RightValue + LeftValue>, power_t<constant_value<LeftValue * RightValue>, constant_value<-1> >, value_mapping>;
            };
        };

        // Simplification rule to produce a new constant value (case 5).
        struct _addition_values_rule_constants_case_5 {

            // Default
            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = std::nullptr_t;
            };

            // A / B + C / D => (A * D + B * C) / (B * D)
            template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
            struct result<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
                using type = product_t<constant_value<LeftLeftValue * RightRightValue + LeftRightValue * RightLeftValue>, power_t<constant_value<LeftRightValue * RightRightValue>, constant_value<-1> >, value_mapping>;
            };
        };

        // Simplification rule to merge the addition of values when the left-hand side argument is smaller than the right-hand side argument.
        struct _addition_values_rule_merge_less_than {

            // A + B => add<A, B> (Default)
            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = add_t<LeftExpression, RightExpression>;
            };

            // A + add<B, ...> => add<A, B, ...>
            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, add<RightArgument, RightNextArguments...> > {
                using type = add_t<LeftExpression, RightArgument, RightNextArguments...>;
            };

            // add<A, ...> + B => A + (add<...> + B)
            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<add<LeftArgument, LeftNextArguments...>, RightExpression > {
                using type = addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, RightExpression> >;
            };

            // add<A, ...> + add<B, ...> => A + (add<...> + add<B, ...>)
            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct result<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...> > {
                using type = addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, add<RightArgument, RightNextArguments...> > >;
            };
        };

        // Simplification rule to merge the addition of values when the right-hand side argument is smaller than the left-hand side argument.
        struct _addition_values_rule_merge_greater_than {

            // B + A => add<A, B> (Default)
            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = add_t<RightExpression, LeftExpression>;
            };

            // B + add<A, ...> => A + (B + add<...>)
            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, add<RightArgument, RightNextArguments...> > {
                using type = addition_t<RightArgument, addition_t<LeftExpression, add_t<RightNextArguments...> > >;
            };

            // add<B, ...> + A => add<A, B, ...>
            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<add<LeftArgument, LeftNextArguments...>, RightExpression> {
                using type = add_t<RightExpression, LeftArgument, LeftNextArguments...>;
            };

            // add<B, ...> + add<A, ...> => A + (add<B, ...> + add<...>)
            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct result<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...> > {
                using type = addition_t<RightArgument, addition_t<add<LeftArgument, LeftNextArguments...>, add_t<RightNextArguments...> > >;
            };
        };

        // Simplification rule to merge the addition of values when the left-hand side argument is equivalent to the rght-hand side argument.
        struct _addition_values_rule_merge_equal_to {

            // A + B => add<A, B> (Default)
            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = add_t<LeftExpression, RightExpression>;
            };

            // A + add<B, ...> => add<A, B, ...>
            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, add<RightArgument, RightNextArguments...> > {
                using type = add_t<LeftExpression, RightArgument, RightNextArguments...>;
            };

            // add<A, ...> + B => add<A, B, ...>
            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<add<LeftArgument, LeftNextArguments...>, RightExpression> {
                using type = add_t<LeftArgument, RightExpression, LeftNextArguments...>;
            };

            // add<A, ...> + add<B, ...> => add<A, B> + (add<...> + add<...>)
            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct result<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...> > {
                using type = addition_t<add_t<LeftArgument, RightArgument>, addition_t<add_t<LeftNextArguments...>, add_t<RightNextArguments...> > >;
            };
        };

        // The list of simplification rules used by the implementation of _addition<LeftExpression, RightExpression> with values.
        template<typename LeftArgument, typename RigthArgument>
        using _addition_values_rules_t = rules<
            _addition_values_rule_zero,
            _addition_values_rule_helper<_addition_values_rule_collect_case_1>,
            _addition_values_rule_helper<_addition_values_rule_collect_case_2>,
            _addition_values_rule_helper<_addition_values_rule_collect_case_3>,
            _addition_values_rule_helper<_addition_values_rule_collect_case_4>,
            _addition_values_rule_helper<_addition_values_rule_collect_case_5>,
            _addition_values_rule_helper<_addition_values_rule_collect_case_6>,
            _addition_values_rule_helper<_addition_values_rule_collect_case_7>,
            _addition_values_rule_helper<_addition_values_rule_constants_case_1>,
            _addition_values_rule_helper<_addition_values_rule_constants_case_2>,
            _addition_values_rule_helper<_addition_values_rule_constants_case_3>,
            _addition_values_rule_helper<_addition_values_rule_constants_case_4>,
            _addition_values_rule_helper<_addition_values_rule_constants_case_5>,
            std::conditional_t<
                lt_v<LeftArgument, RigthArgument>,
                _addition_values_rule_merge_less_than,
                std::conditional_t<
                    lt_v<RigthArgument, LeftArgument>,
                    _addition_values_rule_merge_greater_than,
                    _addition_values_rule_merge_equal_to
                >
            >
        >;

        // Implementation of _addition<LeftExpression, RightExpression> with values as argument.
        template<typename LeftArgument, typename RigthArgument>
        struct _addition :
            apply_rule_for_t<
                _addition_values_rules_t<LeftArgument, RigthArgument>,
                LeftArgument,
                RigthArgument
            > {
        };

        template<typename LeftArgument, typename RigthArgument, typename... RightNextArguments>
        struct _addition<LeftArgument, add<RigthArgument, RightNextArguments...> > :
            apply_rule_for_t<
                _addition_values_rules_t<LeftArgument, RigthArgument>,
                LeftArgument,
                add<RigthArgument, RightNextArguments...>
            > {
        };

        template<typename LeftArgument, typename... LeftNextArguments, typename RigthArgument>
        struct _addition<add<LeftArgument, LeftNextArguments...>, RigthArgument> :
            apply_rule_for_t<
                _addition_values_rules_t<LeftArgument, RigthArgument>,
                add<LeftArgument, LeftNextArguments...>,
                RigthArgument
            > {
        };

        template<typename LeftArgument, typename... LeftNextArguments, typename RigthArgument, typename... RightNextArguments>
        struct _addition<add<LeftArgument, LeftNextArguments...>, add<RigthArgument, RightNextArguments...> > :
            apply_rule_for_t<
                _addition_values_rules_t<LeftArgument, RigthArgument>,
                add<LeftArgument, LeftNextArguments...>,
                add<RigthArgument, RightNextArguments...>
            > {
        };
        
    }

}

#endif // __GA_CORE_EXPRESSION_SIMPLIFICATION_ADDITION_VALUES_HPP__
