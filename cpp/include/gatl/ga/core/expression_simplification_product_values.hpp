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

#ifndef __GA_CORE_EXPRESSION_SIMPLIFICATION_PRODUCT_VALUES_HPP__
#define __GA_CORE_EXPRESSION_SIMPLIFICATION_PRODUCT_VALUES_HPP__

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

        // A meta-structure to help writing simplification rules on expressions having values and mul<value, ...> as arguments.
        template<typename Rule>
        struct _product_values_rule_helper {

            // A * B => simplify(A * B)
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                Rule::template condition<LeftExpression, RightExpression> {
            };

            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = typename Rule::template result<LeftExpression, RightExpression>::type;
            };

            // A * mul<B, ...> => simplify(A * B) * mul<...>
            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct condition<LeftExpression, mul<RightArgument, RightNextArguments...> > :
                Rule::template condition<LeftExpression, RightArgument> {
            };

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, mul<RightArgument, RightNextArguments...> > {
                using type = product_t<typename Rule::template result<LeftExpression, RightArgument>::type, mul_t<RightNextArguments...>, value_mapping>;
            };

            // mul<A, ...> * B => simplify(A * B) * mul<...>
            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct condition<mul<LeftArgument, LeftNextArguments...>, RightExpression> :
                Rule::template condition<LeftArgument, RightExpression> {
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<mul<LeftArgument, LeftNextArguments...>, RightExpression> {
                using type = product_t<typename Rule::template result<LeftArgument, RightExpression>::type, mul_t<LeftNextArguments...>, value_mapping>;
            };

            // mul<A, ...> * mul<B, ...> => simplify(A * B) * (mul<...> * mul<...>)
            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct condition<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...> > :
                Rule::template condition<LeftArgument, RightArgument> {
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct result<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...> > {
                using type = product_t<typename Rule::template result<LeftArgument, RightArgument>::type, product_t<mul_t<LeftNextArguments...>, mul_t<RightNextArguments...>, value_mapping>, value_mapping>;
            };
        };
        
        // Simplification rule to avoid multiply by zero.
        struct _product_values_rule_zero {

            // Default
            template<typename LeftExpression, typename RightExpression, typename _Dummy = void>
            struct condition :
                std::false_type {
            };

            template<typename LeftExpression, typename RightExpression, typename _Dummy = void>
            struct result;

            // 0 * something => 0
            template<typename RightExpression, typename _Dummy>
            struct condition<constant_value<0>, RightExpression, _Dummy> :
                std::true_type {
            };

            template<typename RightExpression, typename _Dummy>
            struct result<constant_value<0>, RightExpression, _Dummy> {
                using type = constant_value<0>;
            };

            // something * 0 => 0
            template<typename LeftExpression, typename _Dummy>
            struct condition<LeftExpression, constant_value<0>, _Dummy> :
                std::true_type {
            };

            template<typename LeftExpression, typename _Dummy>
            struct result<LeftExpression, constant_value<0>, _Dummy> {
                using type = constant_value<0>;
            };

            // 0 * 0 => 0
            template<typename _Dummy>
            struct condition<constant_value<0>, constant_value<0>, _Dummy> :
                std::true_type {
            };

            template<typename _Dummy>
            struct result<constant_value<0>, constant_value<0>, _Dummy> {
                using type = constant_value<0>;
            };
        };
        
        // Simplification rule to avoid multiply by one.
        struct _product_values_rule_one {
            
            // Default
            template<typename LeftExpression, typename RightExpression, typename _Dummy = void>
            struct condition :
                std::false_type {
            };

            template<typename LeftExpression, typename RightExpression, typename _Dummy = void>
            struct result;

            // 1 * something => something
            template<typename RightExpression, typename _Dummy>
            struct condition<constant_value<1>, RightExpression, _Dummy> :
                std::true_type {
            };

            template<typename RightExpression, typename _Dummy>
            struct result<constant_value<1>, RightExpression, _Dummy> {
                using type = RightExpression;
            };

            // something * 1 => something
            template<typename LeftExpression, typename _Dummy>
            struct condition<LeftExpression, constant_value<1>, _Dummy> :
                std::true_type {
            };

            template<typename LeftExpression, typename _Dummy>
            struct result<LeftExpression, constant_value<1>, _Dummy> {
                using type = LeftExpression;
            };

            // 1 * 1 => 1
            template<typename _Dummy>
            struct condition<constant_value<1>, constant_value<1>, _Dummy> :
                std::true_type {
            };

            template<typename _Dummy>
            struct result<constant_value<1>, constant_value<1>, _Dummy> {
                using type = constant_value<1>;
            };
        };
        
        // Simplification rule to apply the distributivity property of products over addition.
        struct _product_values_rule_distributivity {

            // Default
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                std::false_type {
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            // A * add<B, ...> => (A * B) + (A * add<...>)
            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct condition<LeftExpression, add<RightArgument, RightNextArguments...> > :
                std::true_type {
            };

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, add<RightArgument, RightNextArguments...> > {
                using type = addition_t<product_t<LeftExpression, RightArgument, value_mapping>, product_t<LeftExpression, add_t<RightNextArguments...>, value_mapping> >;
            };

            // add<A, ...> * B => (A * B) + (add<...> * B)
            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct condition<add<LeftArgument, LeftNextArguments...>, RightExpression> :
                std::true_type {
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<add<LeftArgument, LeftNextArguments...>, RightExpression> {
                using type = addition_t<product_t<LeftArgument, RightExpression, value_mapping>, product_t<add_t<LeftNextArguments...>, RightExpression, value_mapping> >;
            };

            // add<A, ...> * add<B, ...> => ((A * B) + (add<...> * B)) + ((A * add<...>) + (add<...> * add<...>))
            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct condition<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...> > :
                std::true_type {
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct result<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...> > {
                using type = addition_t<addition_t<product_t<LeftArgument, RightArgument, value_mapping>, product_t<add_t<LeftNextArguments...>, RightArgument, value_mapping> >, addition_t<product_t<LeftArgument, add_t<RightNextArguments...>, value_mapping>, product_t<add_t<LeftNextArguments...>, add_t<RightNextArguments...>, value_mapping> > >;
            };
        };

        // Simplification rule to collect common terms (case 1).
        struct _product_values_rule_collect_value_case_1 {
            
            // Default
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                std::false_type {
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            // A * A => A^{2}
            template<typename CommonExpression>
            struct condition<CommonExpression, CommonExpression> :
                std::true_type {
            };

            template<typename CommonExpression>
            struct result<CommonExpression, CommonExpression> {
                using type = power_t<CommonExpression, constant_value<2> >;
            };
        };

        // Simplification rule to collect common terms (case 2).
        struct _product_values_rule_collect_value_case_2 {
            
            // Default
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                std::false_type {
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            // A^{P} * A => A^{P + 1}
            template<typename CommonArgument, typename LeftRightArgument>
            struct condition<power<CommonArgument, LeftRightArgument>, CommonArgument> :
                std::true_type {
            };

            template<typename CommonArgument, typename LeftRightArgument>
            struct result<power<CommonArgument, LeftRightArgument>, CommonArgument> {
                using type = power_t<CommonArgument, addition_t<LeftRightArgument, constant_value<1> > >;
            };

            // A * A^{P} => A^{1 + P}
            template<typename CommonArgument, typename RightRightArgument>
            struct condition<CommonArgument, power<CommonArgument, RightRightArgument> > :
                std::true_type {
            };

            template<typename CommonArgument, typename RightRightArgument>
            struct result<CommonArgument, power<CommonArgument, RightRightArgument> > {
                using type = power_t<CommonArgument, addition_t<constant_value<1>, RightRightArgument> >;
            };
        };

        // Simplification rule to collect common terms (case 3).
        struct _product_values_rule_collect_value_case_3 {
            
            // Default
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                std::false_type {
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            // A^{P} * A^{Q} => A^{P + Q}
            template<typename CommonArgument, typename LeftRightArgument, typename RightRightArgument>
            struct condition<power<CommonArgument, LeftRightArgument>, power<CommonArgument, RightRightArgument> > :
                std::true_type {
            };

            template<typename CommonArgument, typename LeftRightArgument, typename RightRightArgument>
            struct result<power<CommonArgument, LeftRightArgument>, power<CommonArgument, RightRightArgument> > {
                using type = power_t<CommonArgument, addition_t<LeftRightArgument, RightRightArgument> >;
            };
        };

        // Simplification rule to produce a new constant value (case 1).
        struct _product_values_rule_constants_case_1 {
            
            // Default
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                std::false_type {
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            // A * B => C
            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<constant_value<LeftValue>, constant_value<RightValue> > :
                std::true_type {
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<constant_value<LeftValue>, constant_value<RightValue> > {
                using type = constant_value<LeftValue * RightValue>;
            };

            // A^{-1} * B^{-1} => (A * B)^{-1}
            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> > > :
                std::true_type {
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> > > {
                using type = power_t<constant_value<LeftValue * RightValue>, constant_value<-1> >;
            };
        };

        // Simplification rule to produce a new constant value (case 2).
        struct _product_values_rule_constants_case_2 {
            
            // Default
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                std::false_type {
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            // A * B^{-1} => simpler or mul<A, B^{-1}>
            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> > > :
                std::true_type {
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> > > {
                using type = simpler_rational_constant_t<LeftValue, RightValue>;
            };

            // A^{-1} * B => simpler or mul<B, A^{-1}>
            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct condition<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue> > :
                std::true_type {
            };

            template<default_integral_t LeftValue, default_integral_t RightValue>
            struct result<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue> > {
                using type = simpler_rational_constant_t<RightValue, LeftValue>;
            };
        };

        // Simplification rule to merge the product of values when the left-hand side argument is smaller than the right-hand side argument.
        struct _product_values_rule_merge_less_than {

            // A * B => mul<A, B>
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                lt_t<LeftExpression, RightExpression> {
            };

            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = mul_t<LeftExpression, RightExpression>;
            };

            // A * mul<B, ...> => mul<A, B, ...>
            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct condition<LeftExpression, mul<RightArgument, RightNextArguments...> > :
                lt_t<LeftExpression, RightArgument> {
            };

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, mul<RightArgument, RightNextArguments...> > {
                using type = mul_t<LeftExpression, RightArgument, RightNextArguments...>;
            };

            // mul<A, ...> * B => A * (mul<...> * B)
            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct condition<mul<LeftArgument, LeftNextArguments...>, RightExpression> :
                lt_t<LeftArgument, RightExpression> {
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<mul<LeftArgument, LeftNextArguments...>, RightExpression> {
                using type = product_t<LeftArgument, product_t<mul_t<LeftNextArguments...>, RightExpression, value_mapping>, value_mapping>;
            };

            // mul<A, ...> * mul<B, ...> => A * (mul<...> * mul<B, ...>)
            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct condition<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...> > :
                lt_t<LeftArgument, RightArgument> {
            };
            
            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct result<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...> > {
                using type = product_t<LeftArgument, product_t<mul_t<LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, value_mapping>, value_mapping>;
            };
        };

        // Simplification rule to merge the product of values when the right-hand side argument is smaller than the left-hand side argument.
        struct _product_values_rule_merge_greater_than {

            // B * A => mul<A, B> 
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                lt_t<RightExpression, LeftExpression> {
            };

            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = mul_t<RightExpression, LeftExpression>;
            };

            // B * mul<A, ...> => A * (B * mul<...>)
            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct condition<LeftExpression, mul<RightArgument, RightNextArguments...> > :
                lt_t<RightArgument, LeftExpression> {
            };

            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, mul<RightArgument, RightNextArguments...> > {
                using type = product_t<RightArgument, product_t<LeftExpression, mul_t<RightNextArguments...>, value_mapping>, value_mapping>;
            };

            // mul<B, ...> * A => mul<A, B, ...>
            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct condition<mul<LeftArgument, LeftNextArguments...>, RightExpression> :
                lt_t<RightExpression, LeftArgument> {
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<mul<LeftArgument, LeftNextArguments...>, RightExpression> {
                using type = mul_t<RightExpression, LeftArgument, LeftNextArguments...>;
            };

            // mul<B, ...> * mul<A, ...> => A * (mul<B, ...> * mul<...>)
            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct condition<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...> > :
                lt_t<RightArgument, LeftArgument> {
            };

            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct result<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...> > {
                using type = product_t<RightArgument, product_t<mul<LeftArgument, LeftNextArguments...>, mul_t<RightNextArguments...>, value_mapping>, value_mapping>;
            };
        };

        // Simplification rule to merge the product of values when the left-hand side argument is equivalent to the rght-hand side argument.
        struct _product_values_rule_merge_equal_to {

            // All cases must be accepted
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                std::true_type {
            };

            // A * B => mul<A, B>
            template<typename LeftExpression, typename RightExpression>
            struct result {
                using type = mul_t<LeftExpression, RightExpression>;
            };

            // A * mul<B, ...> => mul<A, B, ...>
            template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
            struct result<LeftExpression, mul<RightArgument, RightNextArguments...> > {
                using type = mul_t<LeftExpression, RightArgument, RightNextArguments...>;
            };

            // mul<A, ...> * B => mul<A, B, ...>
            template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
            struct result<mul<LeftArgument, LeftNextArguments...>, RightExpression> {
                using type = mul_t<LeftArgument, RightExpression, LeftNextArguments...>;
            };

            // mul<A, ...> * mul<B, ...> => mul<A, B> * (mul<...> * mul<...>)
            template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
            struct result<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...> > {
                using type = product_t<mul_t<LeftArgument, RightArgument>, product_t<mul_t<LeftNextArguments...>, mul_t<RightNextArguments...>, value_mapping>, value_mapping>;
            };
        };

        // Implementation of _product<LeftExpression, RightExpression, Mapping> with values as arguments.
        template<typename LeftExpression, typename RightExpression>
        struct _product<LeftExpression, RightExpression, value_mapping> :
            apply_rule_for_t<
                rules<
                    _product_values_rule_zero,
                    _product_values_rule_one,
                    _product_values_rule_distributivity,
                    _product_values_rule_helper<_product_values_rule_collect_value_case_1>,
                    _product_values_rule_helper<_product_values_rule_collect_value_case_2>,
                    _product_values_rule_helper<_product_values_rule_collect_value_case_3>,
                    _product_values_rule_helper<_product_values_rule_constants_case_1>,
                    _product_values_rule_constants_case_2, //TODO How to use _product_values_rule_helper<> here without getting in a loop?
                    _product_values_rule_merge_less_than,
                    _product_values_rule_merge_greater_than,
                    _product_values_rule_merge_equal_to
                >,
                LeftExpression,
                RightExpression
            > {
        };

    }

}

#endif // __GA_CORE_EXPRESSION_SIMPLIFICATION_PRODUCT_VALUES_HPP__
