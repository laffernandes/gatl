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

        // Specialization of _addition_level5<LeftExpression, RightExpression> with simple bind or sort-and-bind patterns.
        template<typename LeftExpression, typename RightExpression>
        struct _addition_level5 {
            using type = std::conditional_t<
                lt_v<LeftExpression, RightExpression>,
                add_t<LeftExpression, RightExpression>, // bind
                add_t<RightExpression, LeftExpression> // sort and bind
            >;
        };
        
        // Specializations of _addition_level5<LeftExpression, RightExpression> with at least one constant argument (simplify).
        template<default_integral_t LeftValue, default_integral_t RightValue>
        struct _addition_level5<constant_value<LeftValue>, constant_value<RightValue> > {
            using type = constant_value<LeftValue + RightValue>; // A + B = C (simplify)
        };

        template<default_integral_t LeftValue, default_integral_t RightValue>
        struct _addition_level5<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> > > {
            using type = product_t<constant_value<LeftValue * RightValue + 1>, power_t<constant_value<RightValue>, constant_value<-1> >, value_mapping>; // A + 1 / B = (A * B + 1) / B (simplify)
        };

        template<default_integral_t LeftValue, default_integral_t RightValue>
        struct _addition_level5<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue> > {
            using type = product_t<constant_value<1 + RightValue * LeftValue>, power_t<constant_value<LeftValue>, constant_value<-1> >, value_mapping>; // 1 / A + B = (1 + B * A) / A (simplify)
        };

        template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightValue>
        struct _addition_level5<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, power<constant_value<RightValue>, constant_value<-1> > > {
            using type = product_t<constant_value<LeftLeftValue * RightValue + LeftRightValue>, power_t<constant_value<LeftRightValue * RightValue>, constant_value<-1> >, value_mapping>; // A / B + 1 / C = (A * C + B) / (B * C) (simplify)
        };

        template<default_integral_t LeftValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
        struct _addition_level5<power<constant_value<LeftValue>, constant_value<-1> >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
            using type = product_t<constant_value<RightRightValue + LeftValue * RightLeftValue>, power_t<constant_value<LeftValue * RightRightValue>, constant_value<-1> >, value_mapping>; // 1 / C + A / B = (B + C * A) / (C * B) (simplify)
        };

        template<default_integral_t LeftValue, default_integral_t RightValue>
        struct _addition_level5<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> > > {
            using type = product_t<constant_value<RightValue + LeftValue>, power_t<constant_value<LeftValue * RightValue>, constant_value<-1> >, value_mapping>; // 1 / B + 1 / C = (C + B) / (B * C) (simplify)
        };

        template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
        struct _addition_level5<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
            using type = product_t<constant_value<LeftLeftValue * RightRightValue + LeftRightValue * RightLeftValue>, power_t<constant_value<LeftRightValue * RightRightValue>, constant_value<-1> >, value_mapping>; // A / B + C / D = (A * D + B * C) / (B * D) (simplify)
        };

        // Specializations of _addition_level4<LeftExpression, RightExpression> with some patterns to simplify (simplify).
        template<typename LeftExpression, typename RightExpression, typename Enable = void>
        struct _addition_level4 {
            using type = typename _addition_level5<LeftExpression, RightExpression>::type;
        };

        template<typename LeftLeftArgument, typename CommonArgument>
        struct _addition_level4<mul<LeftLeftArgument, CommonArgument>, CommonArgument, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, constant_value<1> >, add_t<LeftLeftArgument, constant_value<1> >, add_t<constant_value<1>, LeftLeftArgument> > > > {
            using type = product_t<addition_t<LeftLeftArgument, constant_value<1> >, CommonArgument, value_mapping>; // (P * A) + A = (P + 1) * A (simplify)
        };

        template<typename LeftLeftArgument, typename... CommonArguments>
        struct _addition_level4<mul<LeftLeftArgument, CommonArguments...>, mul<CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, constant_value<1> >, add_t<LeftLeftArgument, constant_value<1> >, add_t<constant_value<1>, LeftLeftArgument > > > > {
            using type = product_t<addition_t<LeftLeftArgument, constant_value<1> >, mul_t<CommonArguments...>, value_mapping>; // (P * A * ...) + (A * ...) = (P + 1) * (A * ...) (simplify)
        };

        template<typename CommonArgument, typename RightLeftArgument>
        struct _addition_level4<CommonArgument, mul<RightLeftArgument, CommonArgument>, std::enable_if_t<!is_any_v<addition_t<constant_value<1>, RightLeftArgument>, add_t<constant_value<1>, RightLeftArgument>, add_t<RightLeftArgument, constant_value<1> > > > > {
            using type = product_t<addition_t<constant_value<1>, RightLeftArgument>, CommonArgument, value_mapping>; // A + (P * A) = (1 + P) * A (simplify)
        };

        template<typename... CommonArguments, typename RightLeftArgument>
        struct _addition_level4<mul<CommonArguments...>, mul<RightLeftArgument, CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<constant_value<1>, RightLeftArgument>, add_t<constant_value<1>, RightLeftArgument>, add_t<RightLeftArgument, constant_value<1> > > > > {
            using type = product_t<addition_t<constant_value<1>, RightLeftArgument>, mul_t<CommonArguments...>, value_mapping>; // A * ... + (P * A * ...) = (1 + P) * (A * ...) (simplify)
        };

        template<typename LeftLeftArgument, typename CommmonArgument, typename RightLeftArgument>
        struct _addition_level4<mul<LeftLeftArgument, CommmonArgument>, mul<RightLeftArgument, CommmonArgument>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, RightLeftArgument>, add_t<LeftLeftArgument, RightLeftArgument>, add_t<RightLeftArgument, LeftLeftArgument> > > > {
            using type = product_t<addition_t<LeftLeftArgument, RightLeftArgument>, CommmonArgument, value_mapping>; // (P * A) + (Q * A) = (P + Q) * A (simplify)
        };

        template<typename LeftLeftArgument, typename... CommonArguments, typename RightLeftArgument>
        struct _addition_level4<mul<LeftLeftArgument, CommonArguments...>, mul<RightLeftArgument, CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, RightLeftArgument>, add_t<LeftLeftArgument, RightLeftArgument>, add_t<RightLeftArgument, LeftLeftArgument> > > > {
            using type = product_t<addition_t<LeftLeftArgument, RightLeftArgument>, mul_t<CommonArguments...>, value_mapping>; // (P * A * ...) + (Q * A * ...) = (P + Q) * (A * ...) (simplify)
        };

        // Specialization of _addition_level3<LeftExpression, RightExpression>.
        template<typename LeftExpression, typename RightExpression>
        struct _addition_level3 {
            using type = typename _addition_level4<LeftExpression, RightExpression>::type;
        };

        template<typename CommonExpression>
        struct _addition_level3<CommonExpression, CommonExpression> {
            using type = product_t<constant_value<2>, CommonExpression, value_mapping>; // A + A = 2 * A (simplify)
        };

        // Specialization of _addition_level2<LeftExpression, RightExpression>.
        template<typename LeftExpression, typename RightExpression>
        struct _addition_level2 {
            using type = typename _addition_level3<LeftExpression, RightExpression>::type;
        };

        template<typename LeftArgument>
        struct _addition_level2<LeftArgument, constant_value<0> > {
            using type = LeftArgument; // simplify
        };

        template<typename RightExpression>
        struct _addition_level2<constant_value<0>, RightExpression> {
            using type = RightExpression; // simplify
        };

        template<>
        struct _addition_level2<constant_value<0>, constant_value<0> > {
            using type = constant_value<0>; // simplify
        };

        // Specialization of _addition_level1<LeftExpression, RightExpression> (merge add<...>).
        template<typename LeftExpression, typename RightExpression, typename Enable = void>
        struct _addition_level1;

        template<typename LeftExpression, typename RightExpression>
        struct _addition_level1<LeftExpression, RightExpression, std::enable_if_t<!(is_function_v<name_t::add, LeftExpression> || is_function_v<name_t::add, RightExpression>)> > {
            using type = typename _addition_level2<LeftExpression, RightExpression>::type;
        };

        template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
        struct _addition_level1<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<le_v<LeftArgument, RightArgument> > > {
            using type = addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, add<RightArgument, RightNextArguments...> > >; // merge
        };

        template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
        struct _addition_level1<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftArgument> > > {
            using type = addition_t<RightArgument, addition_t<add<LeftArgument, LeftNextArguments...>, add_t<RightNextArguments...> > >; // merge
        };

        template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
        struct _addition_level1<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::add, LeftExpression> && lt_v<RightArgument, LeftExpression> > > {
            using type = addition_t<RightArgument, addition_t<LeftExpression, add_t<RightNextArguments...> > >; // merge
        };

        template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
        struct _addition_level1<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::add, LeftExpression> && le_v<LeftExpression, RightArgument> && !std::is_same_v<addition_t<LeftExpression, RightArgument>, add<LeftExpression, RightArgument> > > > {
            using type = addition_t<addition_t<LeftExpression, RightArgument>, add_t<RightNextArguments...> >; // simplification found (simplify-and-merge)
        };

        template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
        struct _addition_level1<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::add, LeftExpression> && le_v<LeftExpression, RightArgument> && std::is_same_v<addition_t<LeftExpression, RightArgument>, add<LeftExpression, RightArgument> > > > {
            using type = add_t<LeftExpression, RightArgument, RightNextArguments...>; // no simplification found (bind)
        };

        template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
        struct _addition_level1<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!is_function_v<name_t::add, RightExpression> && le_v<LeftArgument, RightExpression> > > {
            using type = addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, RightExpression> >; // merge
        };

        template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
        struct _addition_level1<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!is_function_v<name_t::add, RightExpression> && lt_v<RightExpression, LeftArgument> > > {
            using type = addition_t<RightExpression, add<LeftArgument, LeftNextArguments...> >; // merge
        };

        // Specialization of _addition<LeftExpression, RightExpression> (add components).
        template<typename LeftExpression, typename RightExpression>
        struct _addition {
            using type = typename _addition_level1<LeftExpression, RightExpression>::type;
        };

        template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade>
        struct _addition<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > {
            using type = std::conditional_t<
                std::is_same_v<LeftCoefficient, constant_value<0> >,
                component<RightCoefficient, RightBasisBlade>, // 0 * 1 + A * Ej = A * Ej (simplify)
                std::conditional_t<
                    std::is_same_v<RightCoefficient, constant_value<0> >,
                    component<LeftCoefficient, LeftBasisBlade>, // A * Ei + 0 * 1 = A * Ei (simplify)
                    std::conditional_t<
                        is_constant_expression_v<LeftBasisBlade> && std::is_same_v<LeftBasisBlade, RightBasisBlade>,
                        component_t<addition_t<LeftCoefficient, RightCoefficient>, LeftBasisBlade>, // A * Ei + B * Ei = (A + B) * Ei (simplify)
                        std::conditional_t<
                            lt_v<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> >,
                            add_t<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> >, // bind
                            add_t<component<RightCoefficient, RightBasisBlade>, component<LeftCoefficient, LeftBasisBlade> > // sort and bind
                        >
                    >
                >
            >;
        };

    }

}

#endif // __GA_CORE_EXPRESSION_ADDITION_HPP__
