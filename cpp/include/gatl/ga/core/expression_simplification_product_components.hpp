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

#ifndef __GA_CORE_EXPRESSION_SIMPLIFICATION_PRODUCT_COMPONENTS_HPP__
#define __GA_CORE_EXPRESSION_SIMPLIFICATION_PRODUCT_COMPONENTS_HPP__

namespace ga {

    namespace detail {

        // Simplification rule to avoid multiply by zero.
        struct _product_components_rule_zero {

            // Default
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition :
                std::false_type {
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            // 0 * something => 0
            template<typename LeftBasisBlade, typename RightExpression, typename Mapping>
            struct condition<component<constant_value<0>, LeftBasisBlade>, RightExpression, Mapping> :
                std::true_type {
            };

            template<typename LeftBasisBlade, typename RightExpression, typename Mapping>
            struct result<component<constant_value<0>, LeftBasisBlade>, RightExpression, Mapping> {
                using type = component<constant_value<0>, LeftBasisBlade>;
            };

            // something * 0 => 0
            template<typename LeftExpression, typename RightBasisBlade, typename Mapping>
            struct condition<LeftExpression, component<constant_value<0>, RightBasisBlade>, Mapping> :
                std::true_type {
            };

            template<typename LeftExpression, typename RightBasisBlade, typename Mapping>
            struct result<LeftExpression, component<constant_value<0>, RightBasisBlade>, Mapping> {
                using type = component<constant_value<0>, RightBasisBlade>;
            };

            // 0 * 0 => 0
            template<typename LeftBasisBlade, typename RightBasisBlade, typename Mapping>
            struct condition<component<constant_value<0>, LeftBasisBlade>, component<constant_value<0>, RightBasisBlade>, Mapping> :
                std::true_type {
            };

            template<typename LeftBasisBlade, typename RightBasisBlade, typename Mapping>
            struct result<component<constant_value<0>, LeftBasisBlade>, component<constant_value<0>, RightBasisBlade>, Mapping> {
                using type = component<constant_value<0>, LeftBasisBlade>;
            };
        };

        // Simplification rule to multiply the given components or to distribute the product of components over addition.
        struct _product_components_rule_multiply_or_distribute {
        private:

            template<typename Scalar, typename Components>
            struct _distribute_while_multiplying_components;
            
            template<typename Scalar, typename Coefficient, typename BasisBlade, typename... NextComponents>
            struct _distribute_while_multiplying_components<Scalar, add<component<Coefficient, BasisBlade>, NextComponents...> > {
                using type = addition_t<component_t<product_t<Scalar, Coefficient, value_mapping>, BasisBlade>, typename _distribute_while_multiplying_components<Scalar, add_t<NextComponents...> >::type>;
            };

            template<typename Scalar, typename Coefficient, typename BasisBlade>
            struct _distribute_while_multiplying_components<Scalar, component<Coefficient, BasisBlade> > {
                using type = component_t<product_t<Scalar, Coefficient, value_mapping>, BasisBlade>;
            };

        public:

            // Default (it is always true)
            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct condition :
                std::true_type {
            };

            template<typename LeftExpression, typename RightExpression, typename Mapping>
            struct result;

            // A Ei * B Ej => (A * B) (Ei * Ej)
            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename Mapping>
            struct result<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping> :
                _distribute_while_multiplying_components<product_t<LeftCoefficient, RightCoefficient, value_mapping>, typename Mapping::template multiply<LeftBasisBlade, RightBasisBlade>::type> {
            };

            // A Ei * add<B Ej, ...> => (A Ei * B Ej) + (A Ei * add<...>)
            template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments, typename Mapping>
            struct result<component<LeftCoefficient, LeftBasisBlade>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...>, Mapping> {
                using type = addition_t<product_t<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping>, product_t<component<LeftCoefficient, LeftBasisBlade>, add_t<RightNextArguments...>, Mapping> >;
            };

            // add<A Ei, ...> * B Ej => (A Ei * B Ej) + (add<...> * B Ej)
            template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade, typename Mapping>
            struct result<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, component<RightCoefficient, RightBasisBlade>, Mapping> {
                using type = addition_t<product_t<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping>, product_t<add_t<LeftNextArguments...>, component<RightCoefficient, RightBasisBlade>, Mapping> >;
            };

            // add<A Ei, ...> * add<B Ej, ...> => ((A Ei * B Ej) + (add<...> * B Ej)) + ((A Ei * add<...>) + (add<...> * add<...>))
            template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments, typename Mapping>
            struct result<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...>, Mapping> {
                using type = addition_t<addition_t<product_t<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping>, product_t<add_t<LeftNextArguments...>, component<RightCoefficient, RightBasisBlade>, Mapping> >, addition_t<product_t<component<LeftCoefficient, LeftBasisBlade>, add_t<RightNextArguments...>, Mapping>, product_t<add_t<LeftNextArguments...>, add_t<RightNextArguments...>, Mapping> > >;
            };
        };

        // The set of simplification rules applied to the product of components.
        using _product_components_rules = rules<
            _product_components_rule_zero,
            _product_components_rule_multiply_or_distribute
        >;

        // Implementation of _product<LeftExpression, RightExpression, Mapping> with component<...> and add<component<...>, ...> as arguments.
        template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename Mapping>
        struct _product<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping> :
            apply_rule_for_t<
                _product_components_rules,
                component<LeftCoefficient, LeftBasisBlade>,
                component<RightCoefficient, RightBasisBlade>,
                Mapping
            > {
        };

        template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments, typename Mapping>
        struct _product<component<LeftCoefficient, LeftBasisBlade>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...>, Mapping> :
            apply_rule_for_t<
                _product_components_rules,
                component<LeftCoefficient, LeftBasisBlade>,
                add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...>,
                Mapping
            > {
        };

        template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade, typename Mapping>
        struct _product<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, component<RightCoefficient, RightBasisBlade>, Mapping> :
            apply_rule_for_t<
                _product_components_rules,
                add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>,
                component<RightCoefficient, RightBasisBlade>,
                Mapping
            > {
        };

        template<typename LeftCoefficient, typename LeftBasisBlade, typename... LeftNextArguments, typename RightCoefficient, typename RightBasisBlade, typename... RightNextArguments, typename Mapping>
        struct _product<add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>, add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...>, Mapping> :
            apply_rule_for_t<
                _product_components_rules,
                add<component<LeftCoefficient, LeftBasisBlade>, LeftNextArguments...>,
                add<component<RightCoefficient, RightBasisBlade>, RightNextArguments...>,
                Mapping
            > {
        };

    }

}

#endif // __GA_CORE_EXPRESSION_SIMPLIFICATION_PRODUCT_COMPONENTS_HPP__
