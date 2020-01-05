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

#ifndef __GA_CORE_EXPRESSION_SIMPLIFICATION_ADDITION_COMPONENTS_HPP__
#define __GA_CORE_EXPRESSION_SIMPLIFICATION_ADDITION_COMPONENTS_HPP__

namespace ga {

    namespace detail {

        // Simplification rule to avoid sum to zero.
        struct _addition_components_rule_zero {
            
            // Default
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                std::false_type {
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            // 0 + something => something
            template<typename LeftBasisBlade, typename RightExpression>
            struct condition<component<constant_value<0>, LeftBasisBlade>, RightExpression> :
                std::true_type {
            };

            template<typename LeftBasisBlade, typename RightExpression>
            struct result<component<constant_value<0>, LeftBasisBlade>, RightExpression> {
                using type = RightExpression;
            };

            // something + 0 => something
            template<typename LeftExpression, typename RightBasisBlade>
            struct condition<LeftExpression, component<constant_value<0>, RightBasisBlade> > :
                std::true_type {
            };

            template<typename LeftExpression, typename RightBasisBlade>
            struct result<LeftExpression, component<constant_value<0>, RightBasisBlade> > {
                using type = LeftExpression;
            };

            // 0 + 0 => 0
            template<typename LeftBasisBlade, typename RightBasisBlade>
            struct condition<component<constant_value<0>, LeftBasisBlade>, component<constant_value<0>, RightBasisBlade> > :
                std::true_type {
            };

            template<typename LeftBasisBlade, typename RightBasisBlade>
            struct result<component<constant_value<0>, LeftBasisBlade>, component<constant_value<0>, RightBasisBlade> > {
                using type = component<constant_value<0>, LeftBasisBlade>;
            };
        };

        // Simplification rule to collect the common basis blade.
        struct _addition_components_rule_collect {
            
            // Default
            template<typename LeftExpression, typename RightExpression>
            struct condition :
                std::false_type {
            };

            template<typename LeftExpression, typename RightExpression>
            struct result;

            // A Ei + B Ei => (A + B) Ei
            template<typename LeftCoefficient, typename BasisBlade, typename RightCoefficient>
            struct condition<component<LeftCoefficient, BasisBlade>, component<RightCoefficient, BasisBlade> > :
                std::true_type {
            };

            template<typename LeftCoefficient, typename BasisBlade, typename RightCoefficient>
            struct result<component<LeftCoefficient, BasisBlade>, component<RightCoefficient, BasisBlade> > {
                using type = component_t<addition_t<LeftCoefficient, RightCoefficient>, BasisBlade>;
            };

            // A Ei + add<B Ei, ...> => (A + B) Ei + add<...>
            template<typename LeftCoefficient, typename BasisBlade, typename RightCoefficient, typename... RightNextArguments>
            struct condition<component<LeftCoefficient, BasisBlade>, add<component<RightCoefficient, BasisBlade>, RightNextArguments...> > :
                std::true_type {
            };

            template<typename LeftCoefficient, typename BasisBlade, typename RightCoefficient, typename... RightNextArguments>
            struct result<component<LeftCoefficient, BasisBlade>, add<component<RightCoefficient, BasisBlade>, RightNextArguments...> > {
                using type = addition_t<component_t<addition_t<LeftCoefficient, RightCoefficient>, BasisBlade>, add_t<RightNextArguments...> >;
            };

            // add<A Ei, ...> + B Ei => (A + B) Ei + add<...>
            template<typename LeftCoefficient, typename BasisBlade, typename... LeftNextArguments, typename RightCoefficient>
            struct condition<add<component<LeftCoefficient, BasisBlade>, LeftNextArguments...>, component<RightCoefficient, BasisBlade> > :
                std::true_type {
            };

            template<typename LeftCoefficient, typename BasisBlade, typename... LeftNextArguments, typename RightCoefficient>
            struct result<add<component<LeftCoefficient, BasisBlade>, LeftNextArguments...>, component<RightCoefficient, BasisBlade> > {
                using type = addition_t<component_t<addition_t<LeftCoefficient, RightCoefficient>, BasisBlade>, add_t<LeftNextArguments...> >;
            };

            // add<A Ei, ...> + add<B Ei, ...> => (A + B) Ei + (add<...> + add<...>)
            template<typename LeftCoefficient, typename BasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename... RightNextArguments>
            struct condition<add<component<LeftCoefficient, BasisBlade>, LeftNextArguments...>, add<component<RightCoefficient, BasisBlade>, RightNextArguments...> > :
                std::true_type {
            };

            template<typename LeftCoefficient, typename BasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename... RightNextArguments>
            struct result<add<component<LeftCoefficient, BasisBlade>, LeftNextArguments...>, add<component<RightCoefficient, BasisBlade>, RightNextArguments...> > {
                using type = addition_t<component_t<addition_t<LeftCoefficient, RightCoefficient>, BasisBlade>, addition_t<add_t<LeftNextArguments...>, add_t<RightNextArguments...> > >;
            };
        };

        // Simplification rule to merge the addition of components when the left-hand side argument is smaller than the right-hand side argument.
        struct _addition_components_rule_merge_less_than {
            
            // Default
            template<typename LeftExpression, typename RightExpression>
            struct condition;

            template<typename LeftExpression, typename RightExpression>
            struct result;            

            // A Ei + A Ej => add<A Ei, B Ej>
            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade>
            struct condition<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > :
                lt_t<LeftBasisBlade, RightBasisBlade> {
            };

            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade>
            struct result<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > {
                using type = add_t<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> >;
            };

            // A Ei + add<B Ej, ...> => add<A Ei, B Ej, ...>
            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments>
            struct condition<component<LeftCoefficient, LeftBasisBlade>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...> > :
                lt_t<LeftBasisBlade, RightBasisBlade> {
            };

            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments>
            struct result<component<LeftCoefficient, LeftBasisBlade>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...> > {
                using type = add_t<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, RightNextArguments...>;
            };

            // add<A Ei, ...> + B Ej => A Ei + (add<...> + B Ej)
            template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade>
            struct condition<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, component<RightCoefficient, RightBasisBlade> > :
                lt_t<LeftBasisBlade, RightBasisBlade> {
            };

            template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade>
            struct result<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, component<RightCoefficient, RightBasisBlade> > {
                using type = addition_t<component<LeftCoefficient, LeftBasisBlade>, addition_t<add_t<LeftNextArguments...>, component<RightCoefficient, RightBasisBlade> > >;
            };

            // add<A Ei, ...> + add<B Ej, ...> => A Ei + (add<...> + add<B Ej, ...>)
            template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments>
            struct condition<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...> > :
                lt_t<LeftBasisBlade, RightBasisBlade> {
            };

            template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments>
            struct result<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...> > {
                using type = addition_t<component<LeftCoefficient, LeftBasisBlade>, addition_t<add_t<LeftNextArguments...>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...> > >;
            };
        };

        // Simplification rule to merge the addition of components when the right-hand side argument is smaller than the left-hand side argument.
        struct _addition_components_rule_merge_greater_than {
            
            // Default
            template<typename LeftExpression, typename RightExpression>
            struct condition;

            template<typename LeftExpression, typename RightExpression>
            struct result;            

            // B Ej + A Ei => add<A Ei, B Ej>
            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade>
            struct condition<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > :
                lt_t<RightBasisBlade, LeftBasisBlade> {
            };

            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade>
            struct result<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > {
                using type = add_t<component<RightCoefficient, RightBasisBlade>, component<LeftCoefficient, LeftBasisBlade> >;
            };

            // B Ej + add<A Ei, ...> => A Ei + (B Ej + add<...>)
            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments>
            struct condition<component<LeftCoefficient, LeftBasisBlade>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...> > :
                lt_t<RightBasisBlade, LeftBasisBlade> {
            };

            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments>
            struct result<component<LeftCoefficient, LeftBasisBlade>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...> > {
                using type = addition_t<component<RightCoefficient, RightBasisBlade>, addition_t<component<LeftCoefficient, LeftBasisBlade>, add_t<RightNextArguments...> > >;
            };

            // add<B Ej, ...> + A Ei => add<A Ei, B Ej, ...>
            template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade>
            struct condition<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, component<RightCoefficient, RightBasisBlade> > :
                lt_t<RightBasisBlade, LeftBasisBlade> {
            };

            template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade>
            struct result<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, component<RightCoefficient, RightBasisBlade> > {
                using type = add_t<component<RightCoefficient, RightBasisBlade>, component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>;
            };

            // add<B Ej, ...> + add<A Ei, ...> => A Ei + (add<B Ej, ...> + add<...>)
            template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments>
            struct condition<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...> > :
                lt_t<RightBasisBlade, LeftBasisBlade> {
            };
            
            template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments>
            struct result<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...> > {
                using type = addition_t<component<RightCoefficient, RightBasisBlade>, addition_t<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, add_t<RightNextArguments...> > >;
            };
        };

        // The set of simplification rules applied to the addition of components.
        using _addition_components_rules = rules<
            _addition_components_rule_zero,
            _addition_components_rule_collect,
            _addition_components_rule_merge_less_than,
            _addition_components_rule_merge_greater_than
        >;

        // Implementation of _addition<LeftExpression, RightExpression> with component<...> and add<component<...>, ...> as arguments.
        template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade>
        struct _addition<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > :
            apply_rule_for_t<
                _addition_components_rules,
                component<LeftCoefficient, LeftBasisBlade>,
                component<RightCoefficient, RightBasisBlade>
            > {
        };

        template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments>
        struct _addition<component<LeftCoefficient, LeftBasisBlade>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...> > :
            apply_rule_for_t<
                _addition_components_rules,
                component<LeftCoefficient, LeftBasisBlade>,
                add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...>
            > {
        };

        template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade>
        struct _addition<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, component<RightCoefficient, RightBasisBlade> > :
            apply_rule_for_t<
                _addition_components_rules,
                add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>,
                component<RightCoefficient, RightBasisBlade>
            > {
        };

        template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments>
        struct _addition<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...> > :
            apply_rule_for_t<
                _addition_components_rules,
                add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>,
                add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...>
            > {
        };

    }

}

#endif // __GA_CORE_EXPRESSION_SIMPLIFICATION_ADDITION_HPP__
