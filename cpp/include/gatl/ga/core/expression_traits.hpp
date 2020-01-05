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

#ifndef __GA_CORE_EXPRESSION_TRAITS_HPP__
#define __GA_CORE_EXPRESSION_TRAITS_HPP__

namespace ga {

    namespace detail {

        // Returns whether the given expressions can be stored if necessary.
        template<typename Expression>
        struct can_be_stored :
            std::false_type { // default
        };

        template<typename Expression>
        constexpr bool can_be_stored_v = can_be_stored<Expression>::value;

        template<default_integral_t Value>
        struct can_be_stored<constant_value<Value> > :
            std::true_type {
        };

        template<>
        struct can_be_stored<stored_value> :
            std::true_type {
        };

        template<>
        struct can_be_stored<stored_map_values> :
            std::true_type {
        };

        template<bitset_t Bitset>
        struct can_be_stored<constant_bitset<Bitset> > :
            std::true_type {
        };

        template<>
        struct can_be_stored<stored_bitset> :
            std::true_type {
        };

        template<>
        struct can_be_stored<stored_map_bitsets> :
            std::true_type {
        };

        template<bitset_t Bitset>
        struct can_be_stored<constant_basis_blade<Bitset> > :
            std::true_type {
        };

        template<bitset_t PossibleGrades, typename Bitset>
        struct can_be_stored<dynamic_basis_blade<PossibleGrades, Bitset> > :
            std::bool_constant<can_be_stored_v<Bitset> > {
        };

        template<typename Coefficient, typename BasisBlade>
        struct can_be_stored<component<Coefficient, BasisBlade> > :
            std::bool_constant<can_be_stored_v<Coefficient> && can_be_stored_v<BasisBlade> > {
        };

        template<name_t Name, typename... Arguments>
        struct can_be_stored<function<Name, Arguments...> > :
            std::conjunction<std::bool_constant<can_be_stored_v<Arguments> >...>::type {
        };

        // Specializations of is_constant_expression<Expression>.
        template<typename Expression>
        struct is_constant_expression :
            std::false_type { // default
        };

        template<default_integral_t Value>
        struct is_constant_expression<constant_value<Value> > :
            std::true_type {
        };

        template<bitset_t Bitset>
        struct is_constant_expression<constant_bitset<Bitset> > :
            std::true_type {
        };

        template<bitset_t Bitset>
        struct is_constant_expression<constant_basis_blade<Bitset> > :
            std::true_type {
        };

        template<typename Coefficient, typename BasisBlade>
        struct is_constant_expression<component<Coefficient, BasisBlade> > :
            std::bool_constant<is_constant_expression_v<Coefficient> && is_constant_expression_v<BasisBlade> > {
        };

        template<name_t Name, typename... Arguments>
        struct is_constant_expression<function<Name, Arguments...> > :
            std::conjunction<std::bool_constant<is_constant_expression_v<Arguments> >...>::type {
        };

        // Returns whether the given expression is a scalar component.
        template<typename Expression>
        struct is_scalar_component :
            std::false_type {
        };

        template<typename Coefficient>
        struct is_scalar_component<component<Coefficient, constant_basis_blade<bitset_t(0)> > > :
            std::true_type {
        };

        template<typename Expression>
        constexpr bool is_scalar_component_v = is_scalar_component<Expression>::value;

        // Specializations of has_stored_entries<Expression>.
        template<typename Expression>
        struct has_stored_entries :
            std::false_type { // default
        };

        template<>
        struct has_stored_entries<stored_value> :
            std::true_type {
        };

        template<>
        struct has_stored_entries<stored_map_values> :
            std::true_type {
        };

        template<>
        struct has_stored_entries<stored_bitset> :
            std::true_type {
        };

        template<>
        struct has_stored_entries<stored_map_bitsets> :
            std::true_type {
        };

        template<bitset_t PossibleGrades, typename Bitset>
        struct has_stored_entries<dynamic_basis_blade<PossibleGrades, Bitset> > :
            std::bool_constant<has_stored_entries_v<Bitset> > {
        };

        template<typename Coefficient, typename BasisBlade>
        struct has_stored_entries<component<Coefficient, BasisBlade> > :
            std::bool_constant<(has_stored_entries_v<Coefficient> || has_stored_entries_v<BasisBlade>)> {
        };

        template<name_t Name, typename... Arguments>
        struct has_stored_entries<function<Name, Arguments...> > :
            std::disjunction<std::bool_constant<has_stored_entries_v<Arguments> >...>::type {
        };

        // Returns whether the given expression is an even value for sure.
        template<typename Expression>
        struct is_even;

        template<typename Expression>
        constexpr bool is_even_v = is_even<Expression>::value;

        template<default_integral_t Value>
        struct is_even<constant_value<Value> > :
            std::bool_constant<(Value & 1) == 0> {
        };

        template<tag_t Tag, std::size_t Index>
        struct is_even<get_value<Tag, Index> > :
            std::false_type {
        };

        template<tag_t Tag, std::size_t Index>
        struct is_even<get_map_values<Tag, Index> > :
            std::false_type {
        };

        template<>
        struct is_even<stored_value> :
            std::false_type{
        };

        template<>
        struct is_even<stored_map_values> :
            std::false_type {
        };

        template<typename LeftBitset, typename RightBitset>
        struct is_even<reordering_sign<LeftBitset, RightBitset> > :
            std::false_type {
        };

        template<typename Bitset>
        struct is_even<count_one_bits<Bitset> > :
            std::false_type {
        };

        template<typename Bitset>
        struct is_even<bitwise_uminus<Bitset> > :
            std::bool_constant<is_even_v<Bitset> > {
        };

        template<typename Bitset>
        struct is_even<bitwise_dec<Bitset> > :
            std::bool_constant<!is_even_v<Bitset> > {
        };

        template<typename LeftType, typename RightType>
        struct is_even<bitwise_and<LeftType, RightType> > :
            std::bool_constant<is_even_v<LeftType> && is_even_v<RightType> > {
        };

        template<typename LeftType, typename RightType>
        struct is_even<bitwise_or<LeftType, RightType> > :
            std::bool_constant<is_even_v<LeftType> || is_even_v<RightType> > {
        };

        template<typename LeftType, typename RightType>
        struct is_even<bitwise_xor<LeftType, RightType> > :
            std::false_type {
        };

        template<typename Test, typename TrueValue, typename FalseValue>
        struct is_even<if_else<Test, TrueValue, FalseValue> > :
            std::bool_constant<is_even_v<TrueValue> && is_even_v<FalseValue> > {
        };

        template<typename Value>
        struct is_even<absolute<Value> > :
            std::bool_constant<is_even_v<Value> > {
        };

        template<typename Value>
        struct is_even<exponential<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_even<logarithm<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_even<cosine<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_even<sine<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_even<tangent<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_even<hyperbolic_cosine<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_even<hyperbolic_sine<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_even<hyperbolic_tangent<Value> > :
            std::false_type {
        };

        template<typename LeftArgument, typename RightArgument>
        struct is_even<power<LeftArgument, RightArgument> > :
            std::bool_constant<is_even_v<RightArgument> > {
        };

        template<typename... Arguments>
        struct is_even<mul<Arguments...> > :
            std::false_type {
        };

        template<typename... Arguments>
        struct is_even<add<Arguments...> > :
            std::false_type {
        };

        // Specializations of is_function<Expression>.
        template<name_t Name, typename Expression>
        struct is_function :
            std::false_type {
        };

        template<name_t Name, typename... Arguments>
        struct is_function<Name, function<Name, Arguments...> > :
            std::true_type {
        };

        // Specializations of is_non_negative<Expression>.
        template<default_integral_t Value>
        struct is_non_negative<constant_value<Value> > :
            std::bool_constant<(Value >= 0)> {
        };

        template<tag_t Tag, std::size_t Index>
        struct is_non_negative<get_value<Tag, Index> > :
            std::false_type {
        };
        
        template<tag_t Tag, std::size_t Index>
        struct is_non_negative<get_map_values<Tag, Index> > :
            std::false_type {
        };

        template<>
        struct is_non_negative<stored_value> :
            std::false_type {
        };

        template<>
        struct is_non_negative<stored_map_values> :
            std::false_type {
        };

        template<typename LeftBitset, typename RightBitset>
        struct is_non_negative<reordering_sign<LeftBitset, RightBitset> > :
            std::true_type {
        };

        template<typename Bitset>
        struct is_non_negative<count_one_bits<Bitset> > :
            std::true_type {
        };

        template<typename Bitset>
        struct is_non_negative<bitwise_uminus<Bitset> > :
            std::true_type {
        };

        template<typename Bitset>
        struct is_non_negative<bitwise_dec<Bitset> > :
            std::true_type {
        };

        template<typename LeftType, typename RightType>
        struct is_non_negative<bitwise_and<LeftType, RightType> > :
            std::true_type {
        };

        template<typename LeftType, typename RightType>
        struct is_non_negative<bitwise_or<LeftType, RightType> > :
            std::true_type {
        };

        template<typename LeftType, typename RightType>
        struct is_non_negative<bitwise_xor<LeftType, RightType> > :
            std::true_type {
        };

        template<typename Test, typename TrueValue, typename FalseValue>
        struct is_non_negative<if_else<Test, TrueValue, FalseValue> > :
            std::bool_constant<is_non_negative_v<TrueValue> && is_non_negative_v<FalseValue> > {
        };

        template<typename Value>
        struct is_non_negative<absolute<Value> > :
            std::true_type {
        };

        template<typename Value>
        struct is_non_negative<exponential<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_non_negative<logarithm<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_non_negative<cosine<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_non_negative<sine<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_non_negative<tangent<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_non_negative<hyperbolic_cosine<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_non_negative<hyperbolic_sine<Value> > :
            std::false_type {
        };

        template<typename Value>
        struct is_non_negative<hyperbolic_tangent<Value> > :
            std::false_type {
        };

        template<typename LeftArgument, typename RightArgument>
        struct is_non_negative<power<LeftArgument, RightArgument> > :
            std::bool_constant<is_non_negative_v<LeftArgument> || is_even_v<RightArgument> > {
        };

        template<typename... Arguments>
        struct is_non_negative<mul<Arguments...> > :
            std::conjunction<std::bool_constant<is_non_negative_v<Arguments> >...>::type {
        };

        template<typename... Arguments>
        struct is_non_negative<add<Arguments...> > :
            std::false_type {
        };

        // Returns if the given expression may be positive.
        template<typename Expression>
        struct may_be_positive;

        template<typename Expression>
        constexpr bool may_be_positive_v = may_be_positive<Expression>::value;

        template<default_integral_t Value>
        struct may_be_positive<constant_value<Value> > :
            std::bool_constant<(Value > 0)> {
        };

        template<tag_t Tag, std::size_t Index>
        struct may_be_positive<get_value<Tag, Index> > :
            std::true_type {
        };
        
        template<tag_t Tag, std::size_t Index>
        struct may_be_positive<get_map_values<Tag, Index> > :
            std::true_type {
        };

        template<>
        struct may_be_positive<stored_value> :
            std::true_type {
        };

        template<>
        struct may_be_positive<stored_map_values> :
            std::true_type {
        };

        template<typename LeftBitset, typename RightBitset>
        struct may_be_positive<reordering_sign<LeftBitset, RightBitset> > :
            std::true_type {
        };

        template<typename Bitset>
        struct may_be_positive<count_one_bits<Bitset> > :
            std::true_type {
        };

        template<typename Bitset>
        struct may_be_positive<bitwise_uminus<Bitset> > :
            std::true_type {
        };

        template<typename Bitset>
        struct may_be_positive<bitwise_dec<Bitset> > :
            std::true_type {
        };

        template<typename LeftType, typename RightType>
        struct may_be_positive<bitwise_and<LeftType, RightType> > :
            std::true_type {
        };

        template<typename LeftType, typename RightType>
        struct may_be_positive<bitwise_or<LeftType, RightType> > :
            std::true_type {
        };

        template<typename LeftType, typename RightType>
        struct may_be_positive<bitwise_xor<LeftType, RightType> > :
            std::true_type {
        };

        template<typename Test, typename TrueValue, typename FalseValue>
        struct may_be_positive<if_else<Test, TrueValue, FalseValue> > :
            std::bool_constant<may_be_positive_v<TrueValue> && may_be_positive_v<FalseValue> > {
        };

        template<typename Value>
        struct may_be_positive<absolute<Value> > :
            std::true_type {
        };

        template<typename Value>
        struct may_be_positive<cosine<Value> > :
            std::true_type {
        };

        template<typename Value>
        struct may_be_positive<sine<Value> > :
            std::true_type {
        };

        template<typename Value>
        struct may_be_positive<tangent<Value> > :
            std::true_type {
        };

        template<typename Value>
        struct may_be_positive<hyperbolic_cosine<Value> > :
            std::true_type {
        };

        template<typename Value>
        struct may_be_positive<hyperbolic_sine<Value> > :
            std::true_type {
        };

        template<typename Value>
        struct may_be_positive<hyperbolic_tangent<Value> > :
            std::true_type {
        };

        template<typename LeftArgument, typename RightArgument>
        struct may_be_positive<power<LeftArgument, RightArgument> > :
            std::bool_constant<may_be_positive_v<LeftArgument> || is_even_v<RightArgument> > {
        };

        template<typename... Arguments>
        struct may_be_positive<mul<Arguments...> > :
            std::conjunction<std::bool_constant<may_be_positive_v<Arguments> >...>::type {
        };

        template<typename... Arguments>
        struct may_be_positive<add<Arguments...> > :
            std::true_type {
        };
        
        // Specializations of possible_grades<BasisVectors>.
        template<bitset_t BasisVectors>
        struct possible_grades<constant_basis_blade<BasisVectors> > {
            constexpr static bitset_t value = bitset_t(1) << ones(BasisVectors);
        };

        template<bitset_t PossibleGrades, typename Bitset>
        struct possible_grades<dynamic_basis_blade<PossibleGrades, Bitset> > {
            constexpr static bitset_t value = PossibleGrades;
        };

        // Returns the basis blade type that best fit input arguments.
        template<bitset_t PossibleGrades, typename BasisVectors>
        struct deduce_basis_blade {
            using type = dynamic_basis_blade_t<PossibleGrades, BasisVectors>;
        };

        template<bitset_t PossibleGrades, bitset_t BasisVectors>
        struct deduce_basis_blade<PossibleGrades, constant_bitset<BasisVectors> > {
            using type = constant_basis_blade<BasisVectors>;
        };

        template<bitset_t PossibleGrades, typename BasisVectors>
        using deduce_basis_blade_t = typename deduce_basis_blade<PossibleGrades, BasisVectors>::type;

        // Returns the coefficient of a given set of components.
        template<typename Component>
        struct coefficient;

        template<typename Coefficient, typename BasisBlade>
        struct coefficient<component<Coefficient, BasisBlade> > {
            using type = Coefficient;
        };

        template<typename Component>
        using coefficient_t = typename coefficient<Component>::type;

        // Returns the basis blade of a given components.
        template<typename Component>
        struct basis_blade;

        template<typename Coefficient, typename BasisBlade>
        struct basis_blade<component<Coefficient, BasisBlade> > {
            using type = BasisBlade;
        };

        template<typename Component>
        using basis_blade_t = typename basis_blade<Component>::type;

        // Returns the basis vectors of a given basis blade.
        template<typename BasisBlade>
        struct basis_vectors;

        template<bitset_t BasisVectors>
        struct basis_vectors<constant_basis_blade<BasisVectors> > {
            using type = constant_bitset<BasisVectors>;
        };

        template<bitset_t PossibleGrades, typename Bitset>
        struct basis_vectors<dynamic_basis_blade<PossibleGrades, Bitset> > {
            using type = Bitset;
        };

        template<typename BasisBlade>
        using basis_vectors_t = typename basis_vectors<BasisBlade>::type;

        // Returns the bitset of the rightmost set bit in the given bitset.
        template<typename Bitset>
        using rightmost_one_t = bitwise_and_t<Bitset, bitwise_uminus_t<Bitset> >;

        // Returns the bitset of the i-th set bit in the given bitset (i >= 0).
        template<typename Bitset, std::size_t Index>
        struct indirect_element_bitset;

        template<typename Bitset, std::size_t Index>
        using indirect_element_bitset_t = typename indirect_element_bitset<Bitset, Index>::type;

        template<typename Bitset, std::size_t Index>
        struct indirect_element_bitset {
            using type = indirect_element_bitset_t<bitwise_xor_t<Bitset, rightmost_one_t<Bitset> >, Index - 1>;
        };

        template<typename Bitset>
        struct indirect_element_bitset<Bitset, 0> {
            using type = rightmost_one_t<Bitset>;
        };

        // Returns the indirect subset of a given bitset.
        template<typename Bitset, bitset_t IndirectElements>
        struct indirect_subset;

        template<typename Bitset, bitset_t IndirectElements>
        using indirect_subset_t = typename indirect_subset<Bitset, IndirectElements>::type;

        template<typename Bitset, bitset_t IndirectElements>
        struct indirect_subset {
        private:

            constexpr static bitset_t current_indirect_element = rightmost_set_bit(IndirectElements);

            using current_element = indirect_element_bitset_t<Bitset, set_bit_index(current_indirect_element)>;

        public:

            using type = bitwise_or_t<current_element, indirect_subset_t<Bitset, IndirectElements ^ current_indirect_element> >;
        };

        template<typename Bitset>
        struct indirect_subset<Bitset, bitset_t(0)> {
            using type = constant_bitset<bitset_t(0)>;
        };

    }

}

#endif // __GA_CORE_EXPRESSION_TRAITS_HPP__
