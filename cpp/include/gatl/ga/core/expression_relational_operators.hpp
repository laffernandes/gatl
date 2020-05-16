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

#ifndef __GA_CORE_RELATIONAL_OPERATORS_HPP__
#define __GA_CORE_RELATIONAL_OPERATORS_HPP__

namespace ga {

    namespace detail {

        // Relational operators.
        template<typename LeftType, typename RightType>
        struct lt;

        template<typename LeftType, typename RightType>
        using lt_t = typename lt<LeftType, RightType>::type;

        template<typename LeftType, typename RightType>
        constexpr bool lt_v = lt<LeftType, RightType>::value;

        template<typename LeftType, typename RightType>
        using le_t = std::bool_constant<lt_v<LeftType, RightType> || !lt_v<RightType, LeftType> >;

        template<typename LeftType, typename RightType>
        constexpr bool le_v = le_t<LeftType, RightType>::value;

        template<typename LeftType, typename RightType>
        using eq_t = std::bool_constant<!(lt_v<LeftType, RightType> || lt_v<RightType, LeftType>)>;

        template<typename LeftType, typename RightType>
        constexpr bool eq_v = eq_t<LeftType, RightType>::value;

        template<typename LeftType, typename RightType>
        using ne_t = std::bool_constant<lt_v<LeftType, RightType> || lt_v<RightType, LeftType> >;

        template<typename LeftType, typename RightType>
        constexpr bool ne_v = ne_t<LeftType, RightType>::value;

        template<typename LeftType, typename RightType>
        using gt_t = std::bool_constant<!lt_v<LeftType, RightType> && lt_v<RightType, LeftType> >;

        template<typename LeftType, typename RightType>
        constexpr bool gt_v = gt_t<LeftType, RightType>::value;

        template<typename LeftType, typename RightType>
        using ge_t = std::bool_constant<!lt_v<LeftType, RightType> >;

        template<typename LeftType, typename RightType>
        constexpr bool ge_v = ge_t<LeftType, RightType>::value;

        // Priority value.
        template<typename ValueType, ValueType Value>
        using priority = std::integral_constant<ValueType, Value>;

        using priority_prefix_constant = priority<std::uint8_t, 0x00>;
        using priority_prefix_referenced = priority<std::uint8_t, 0x01>;
        using priority_prefix_stored = priority<std::uint8_t, 0x02>;
        using priority_prefix_function = priority<std::uint8_t, 0x03>;

        // List of priorities.
        template<typename... Priorities>
        struct priority_list {
        };

        template<typename... PriorityLists>
        struct concatenate_priority_lists;

        template<typename... FirstPriorities, typename... SecondPriorities, typename... NextPriorityLists>
        struct concatenate_priority_lists<priority_list<FirstPriorities...>, priority_list<SecondPriorities...>, NextPriorityLists...> {
            using type = typename concatenate_priority_lists<priority_list<FirstPriorities..., SecondPriorities...>, NextPriorityLists...>::type;
        };

        template<typename... Priorities>
        struct concatenate_priority_lists<priority_list<Priorities...> > {
            using type = priority_list<Priorities...>;
        };

        template<>
        struct concatenate_priority_lists<> {
            using type = priority_list<>;
        };

        // Produces the priority_list<...> of a given entry.
        template<typename Entry>
        struct entry_priority;

        // Priority of values.
        template<default_integral_t Value>
        struct entry_priority<constant_value<Value> > {
            using type = priority_list<
                priority_prefix_constant,
                priority<default_integral_t, Value>
            >;
        };

        template<tag_t Tag, std::size_t Index>
        struct entry_priority<get_value<Tag, Index> > {
            using type = priority_list<
                priority_prefix_referenced,
                priority<tag_t, Tag>,
                priority<std::uint8_t, 0x00>,
                priority<std::size_t, Index>
            >;
        };

        template<tag_t Tag, std::size_t Index>
        struct entry_priority<get_map_values<Tag, Index> > {
            using type = priority_list<
                priority_prefix_referenced,
                priority<tag_t, Tag>,
                priority<std::uint8_t, 0x01>,
                priority<std::size_t, Index>
            >;
        };

        template<>
        struct entry_priority<stored_value> {
            using type = priority_list<
                priority_prefix_stored,
                priority<std::uint8_t, 0x00>
            >;
        };

        template<>
        struct entry_priority<stored_map_values> {
            using type = priority_list<
                priority_prefix_stored,
                priority<std::uint8_t, 0x01>
            >;
        };

        // Priority of bitsets.
        template<bitset_t Bitset>
        struct entry_priority<constant_bitset<Bitset> > {
            using type = priority_list<
                priority_prefix_constant,
                priority<bitset_t, Bitset>
            >;
        };

        template<tag_t Tag, std::size_t Index>
        struct entry_priority<get_bitset<Tag, Index> > {
            using type = priority_list<
                priority_prefix_referenced,
                priority<tag_t, Tag>,
                priority<std::uint8_t, 0x00>,
                priority<std::size_t, Index>
            >;
        };

        template<tag_t Tag, std::size_t Index>
        struct entry_priority<get_map_bitsets<Tag, Index> > {
            using type = priority_list<
                priority_prefix_referenced,
                priority<tag_t, Tag>,
                priority<std::uint8_t, 0x01>,
                priority<std::size_t, Index>
            >;
        };

        template<>
        struct entry_priority<stored_bitset> {
            using type = priority_list<
                priority_prefix_stored,
                priority<std::uint8_t, 0x00>
            >;
        };

        template<>
        struct entry_priority<stored_map_bitsets> {
            using type = priority_list<
                priority_prefix_stored,
                priority<std::uint8_t, 0x01>
            >;
        };

        // Priority of basis blades.
        template<bitset_t BasisVectors>
        struct entry_priority<constant_basis_blade<BasisVectors> > {
            using type = priority_list<
                priority<bitset_t, possible_grades_v<constant_basis_blade<BasisVectors> > >,
                priority_prefix_constant,
                priority<bitset_t, BasisVectors>
            >;
        };

        template<bitset_t PossibleGrades, typename Bitset>
        struct entry_priority<dynamic_basis_blade<PossibleGrades, Bitset> > {
            using type = typename concatenate_priority_lists<
                priority_list<
                    priority<bitset_t, PossibleGrades>
                >,
                typename entry_priority<Bitset>::type
            >::type;
        };

        // Priority of function.
        template<typename... Entries>
        struct _set_of_entries {
        };

        template<typename... Arguments>
        struct _make_set_of_non_constant_entries;

        template<typename LeftSetOfEntries, typename RightSetOfEntries, typename Enable = void>
        struct _merge_sets_of_entries;

        template<typename NewEntry, typename SetOfEntries>
        struct _prepend_set_of_entries;
        
        template<default_integral_t Value, typename... NextArguments>
        struct _make_set_of_non_constant_entries<constant_value<Value>, NextArguments...> {
            using type = typename _make_set_of_non_constant_entries<NextArguments...>::type;
        };

        template<default_integral_t Value>
        struct _make_set_of_non_constant_entries<constant_value<Value> > {
            using type = _set_of_entries<>;
        };

        template<bitset_t Bitset, typename... NextArguments>
        struct _make_set_of_non_constant_entries<constant_bitset<Bitset>, NextArguments...> {
            using type = typename _make_set_of_non_constant_entries<NextArguments...>::type;
        };

        template<bitset_t Bitset>
        struct _make_set_of_non_constant_entries<constant_bitset<Bitset> > {
            using type = _set_of_entries<>;
        };

        template<bitset_t BasisVectors, typename... NextArguments>
        struct _make_set_of_non_constant_entries<constant_basis_blade<BasisVectors>, NextArguments...> {
            using type = typename _make_set_of_non_constant_entries<NextArguments...>::type;
        };

        template<bitset_t BasisVectors>
        struct _make_set_of_non_constant_entries<constant_basis_blade<BasisVectors> > {
            using type = _set_of_entries<>;
        };

        template<name_t Name, typename... Arguments, typename... NextArguments>
        struct _make_set_of_non_constant_entries<function<Name, Arguments...>, NextArguments...> {
            using type = typename _merge_sets_of_entries<
                typename _make_set_of_non_constant_entries<Arguments...>::type,
                typename _make_set_of_non_constant_entries<NextArguments...>::type
            >::type;
        };

        template<name_t Name, typename... Arguments>
        struct _make_set_of_non_constant_entries<function<Name, Arguments...> > {
            using type = typename _make_set_of_non_constant_entries<Arguments...>::type;
        };

        template<typename Argument, typename... NextArguments>
        struct _make_set_of_non_constant_entries<Argument, NextArguments...> {
            using type = typename _merge_sets_of_entries<typename _make_set_of_non_constant_entries<_set_of_entries<Argument> >::type, typename _make_set_of_non_constant_entries<NextArguments...>::type>::type;
        };

        template<typename Argument>
        struct _make_set_of_non_constant_entries<Argument> {
            using type = _set_of_entries<Argument>;
        };

        template<>
        struct _make_set_of_non_constant_entries<> {
            using type = _set_of_entries<>;
        };

        template<typename NewEntry, typename... Entries>
        struct _prepend_set_of_entries<NewEntry, _set_of_entries<Entries...> > {
            using type = _set_of_entries<NewEntry, Entries...>;
        };

        template<typename LeftEntry, typename... LeftNextEntries, typename RightEntry, typename... RightNextEntries>
        struct _merge_sets_of_entries<_set_of_entries<LeftEntry, LeftNextEntries...>, _set_of_entries<RightEntry, RightNextEntries...>, std::enable_if_t<lt_v<LeftEntry, RightEntry> > > {
            using type = typename _prepend_set_of_entries<LeftEntry, typename _merge_sets_of_entries<_set_of_entries<LeftNextEntries...>, _set_of_entries<RightEntry, RightNextEntries...> >::type>::type;
        };

        template<typename LeftEntry, typename... LeftNextEntries, typename RightEntry, typename... RightNextEntries>
        struct _merge_sets_of_entries<_set_of_entries<LeftEntry, LeftNextEntries...>, _set_of_entries<RightEntry, RightNextEntries...>, std::enable_if_t<lt_v<RightEntry, LeftEntry> > > {
            using type = typename _prepend_set_of_entries<RightEntry, typename _merge_sets_of_entries<_set_of_entries<LeftEntry, LeftNextEntries...>, _set_of_entries<RightNextEntries...> >::type>::type;
        };

        template<typename LeftEntry, typename... LeftNextEntries, typename RightEntry, typename... RightNextEntries>
        struct _merge_sets_of_entries<_set_of_entries<LeftEntry, LeftNextEntries...>, _set_of_entries<RightEntry, RightNextEntries...>, std::enable_if_t<eq_v<RightEntry, LeftEntry> > > {
            using type = typename _merge_sets_of_entries<_set_of_entries<LeftNextEntries...>, _set_of_entries<RightEntry, RightNextEntries...> >::type;
        };

        template<typename LeftEntry, typename... LeftNextEntries>
        struct _merge_sets_of_entries<_set_of_entries<LeftEntry, LeftNextEntries...>, _set_of_entries<>, void> {
            using type = _set_of_entries<LeftEntry, LeftNextEntries...>;
        };

        template<typename RightEntry, typename... RightNextEntries>
        struct _merge_sets_of_entries<_set_of_entries<>, _set_of_entries<RightEntry, RightNextEntries...>, void> {
            using type = _set_of_entries<RightEntry, RightNextEntries...>;
        };

        template<>
        struct _merge_sets_of_entries<_set_of_entries<>, _set_of_entries<>, void> {
            using type = _set_of_entries<>;
        };

        template<typename... Entries>
        struct entry_priority<_set_of_entries<Entries...> > {
            using type = typename concatenate_priority_lists<
                typename entry_priority<Entries>::type...
            >::type;
        };

        template<name_t Name, typename... Arguments>
        struct entry_priority<function<Name, Arguments...> > {
            using type = typename concatenate_priority_lists<
                typename entry_priority<typename _make_set_of_non_constant_entries<Arguments...>::type>::type/*TODO [Debug],
                priority_list<
                    priority_prefix_function,
                    priority<name_t, Name>
                >*/
            >::type;
        };

        // Less-than operator.
        template<typename LeftType, typename RightType>
        struct lt :
            lt<typename entry_priority<LeftType>::type, typename entry_priority<RightType>::type> {
        };
        
        template<typename FirstValueType, FirstValueType LeftFirstValue, typename... LeftNextPriorities, FirstValueType RightFirstValue, typename... RightNextPriorities>
        struct lt<priority_list<priority<FirstValueType, LeftFirstValue>, LeftNextPriorities...>, priority_list<priority<FirstValueType, RightFirstValue>, RightNextPriorities...> > :
            std::conditional_t<
                (LeftFirstValue < RightFirstValue),
                std::true_type,
                std::conditional_t<
                    LeftFirstValue == RightFirstValue,
                    lt<priority_list<LeftNextPriorities...>, priority_list<RightNextPriorities...> >,
                    std::false_type
                >
            > {
        };

        template<typename LeftFirstValueType, LeftFirstValueType LeftFirstValue, typename... LeftNextPriorities, typename RightFirstValueType, RightFirstValueType RightFirstValue, typename... RightNextPriorities>
        struct lt<priority_list<priority<LeftFirstValueType, LeftFirstValue>, LeftNextPriorities...>, priority_list<priority<RightFirstValueType, RightFirstValue>, RightNextPriorities...> > :
            std::false_type {
        };

        template<typename... LeftPriorities>
        struct lt<priority_list<LeftPriorities...>, priority_list<> > :
            std::false_type {
        };

        template<typename... RightPriorities>
        struct lt<priority_list<>, priority_list<RightPriorities...> > :
            std::true_type {
        };

        template<>
        struct lt<priority_list<>, priority_list<> > :
            std::false_type {
        };
        /*/
        // Relational operators.
        template<typename LeftType, typename RightType>
        struct lt :
            std::false_type {
        };

        template<typename LeftType, typename RightType>
        using lt_t = typename lt<LeftType, RightType>::type;

        template<typename LeftType, typename RightType>
        constexpr bool lt_v = lt<LeftType, RightType>::value;

        template<typename LeftType, typename RightType>
        using le_t = std::bool_constant<lt_v<LeftType, RightType> || !lt_v<RightType, LeftType> >;

        template<typename LeftType, typename RightType>
        constexpr bool le_v = le_t<LeftType, RightType>::value;

        template<typename LeftType, typename RightType>
        using eq_t = std::bool_constant<!lt_v<LeftType, RightType> && !lt_v<RightType, LeftType> >;

        template<typename LeftType, typename RightType>
        constexpr bool eq_v = eq_t<LeftType, RightType>::value;

        template<typename LeftType, typename RightType>
        using ne_t = std::bool_constant<lt_v<LeftType, RightType> || lt_v<RightType, LeftType> >;

        template<typename LeftType, typename RightType>
        constexpr bool ne_v = ne_t<LeftType, RightType>::value;

        template<typename LeftType, typename RightType>
        using gt_t = std::bool_constant<!lt_v<LeftType, RightType> && lt_v<RightType, LeftType> >;

        template<typename LeftType, typename RightType>
        constexpr bool gt_v = gt_t<LeftType, RightType>::value;

        template<typename LeftType, typename RightType>
        using ge_t = std::bool_constant<!lt_v<LeftType, RightType> >;

        template<typename LeftType, typename RightType>
        constexpr bool ge_v = ge_t<LeftType, RightType>::value;

        // Specializations of lt<LeftType, RightType> with values.
        template<default_integral_t LeftValue, default_integral_t RightValue>
        struct lt<constant_value<LeftValue>, constant_value<RightValue> > :
            std::bool_constant<(LeftValue < RightValue)> {
        };

        template<default_integral_t LeftValue, tag_t RightTag, std::size_t RightIndex>
        struct lt<constant_value<LeftValue>, get_value<RightTag, RightIndex> > :
            std::true_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, default_integral_t RightValue>
        struct lt<get_value<LeftTag, LeftIndex>, constant_value<RightValue> > :
            std::false_type {
        };

        template<default_integral_t LeftValue, tag_t RightTag, std::size_t RightIndex>
        struct lt<constant_value<LeftValue>, get_map_values<RightTag, RightIndex> > :
            std::true_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, default_integral_t RightValue>
        struct lt<get_map_values<LeftTag, LeftIndex>, constant_value<RightValue> > :
            std::false_type {
        };

        template<default_integral_t LeftValue>
        struct lt<constant_value<LeftValue>, stored_value> :
            std::true_type {
        };

        template<default_integral_t RightValue>
        struct lt<stored_value, constant_value<RightValue> > :
            std::false_type {
        };

        template<default_integral_t LeftValue>
        struct lt<constant_value<LeftValue>, stored_map_values> :
            std::true_type {
        };

        template<default_integral_t RightValue>
        struct lt<stored_map_values, constant_value<RightValue> > :
            std::false_type {
        };

        template<default_integral_t LeftValue, name_t RightName, typename... RightArguments>
        struct lt<constant_value<LeftValue>, function<RightName, RightArguments...> > :
            std::true_type {
        };

        template<name_t LeftName, typename... LeftArguments, default_integral_t RightValue>
        struct lt<function<LeftName, LeftArguments...>, constant_value<RightValue> > :
            std::false_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
        struct lt<get_value<LeftTag, LeftIndex>, get_value<RightTag, RightIndex> > :
            std::bool_constant<(LeftTag < RightTag || (LeftTag == RightTag && LeftIndex < RightIndex))> {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
        struct lt<get_value<LeftTag, LeftIndex>, get_map_values<RightTag, RightIndex> > :
            std::bool_constant<(LeftTag <= RightTag)> {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
        struct lt<get_map_values<LeftTag, LeftIndex>, get_value<RightTag, RightIndex> > :
            std::bool_constant<(LeftTag < RightTag)> {
        };

        template<tag_t LeftTag, std::size_t LeftIndex>
        struct lt<get_value<LeftTag, LeftIndex>, stored_value> :
            std::true_type {
        };

        template<tag_t RightTag, std::size_t RightIndex>
        struct lt<stored_value, get_value<RightTag, RightIndex> > :
            std::false_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex>
        struct lt<get_value<LeftTag, LeftIndex>, stored_map_values> :
            std::true_type {
        };

        template<tag_t RightTag, std::size_t RightIndex>
        struct lt<stored_map_values, get_value<RightTag, RightIndex> > :
            std::false_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, name_t RightName, typename RightArgument, typename... RightNextArguments>
        struct lt<get_value<LeftTag, LeftIndex>, function<RightName, RightArgument, RightNextArguments...> > :
            le_t<get_value<LeftTag, LeftIndex>, RightArgument> {
        };

        template<name_t LeftName, typename LeftArgument, typename... LeftNextArguments, tag_t RightTag, std::size_t RightIndex>
        struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, get_value<RightTag, RightIndex> > :
            lt_t<LeftArgument, get_value<RightTag, RightIndex> > {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
        struct lt<get_map_values<LeftTag, LeftIndex>, get_map_values<RightTag, RightIndex> > :
            std::bool_constant<(LeftTag < RightTag || (LeftTag == RightTag && LeftIndex < RightIndex))> {
        };

        template<tag_t LeftTag, std::size_t LeftIndex>
        struct lt<get_map_values<LeftTag, LeftIndex>, stored_value> :
            std::true_type {
        };

        template<tag_t RightTag, std::size_t RightIndex>
        struct lt<stored_value, get_map_values<RightTag, RightIndex> > :
            std::false_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex>
        struct lt<get_map_values<LeftTag, LeftIndex>, stored_map_values> :
            std::true_type {
        };

        template<tag_t RightTag, std::size_t RightIndex>
        struct lt<stored_map_values, get_map_values<RightTag, RightIndex> > :
            std::false_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, name_t RightName, typename RightArgument, typename... RightNextArguments>
        struct lt<get_map_values<LeftTag, LeftIndex>, function<RightName, RightArgument, RightNextArguments...> > :
            le_t<get_map_values<LeftTag, LeftIndex>, RightArgument> {
        };

        template<name_t LeftName, typename LeftArgument, typename... LeftNextArguments, tag_t RightTag, std::size_t RightIndex>
        struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, get_map_values<RightTag, RightIndex> > :
            lt_t<LeftArgument, get_map_values<RightTag, RightIndex> > {
        };

        template<>
        struct lt<stored_value, stored_value> :
            std::false_type {
        };

        template<>
        struct lt<stored_value, stored_map_values> :
            std::true_type {
        };

        template<>
        struct lt<stored_map_values, stored_value> :
            std::false_type {
        };

        template<name_t RightName, typename RightArgument, typename... RightNextArguments>
        struct lt<stored_value, function<RightName, RightArgument, RightNextArguments...> > :
            le_t<stored_value, RightArgument> {
        };

        template<name_t LeftName, typename LeftArgument, typename... LeftNextArguments>
        struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, stored_value> :
            lt_t<LeftArgument, stored_value> {
        };

        template<>
        struct lt<stored_map_values, stored_map_values> :
            std::false_type {
        };

        template<name_t RightName, typename RightArgument, typename... RightNextArguments>
        struct lt<stored_map_values, function<RightName, RightArgument, RightNextArguments...> > :
            le_t<stored_map_values, RightArgument> {
        };

        template<name_t LeftName, typename LeftArgument, typename... LeftNextArguments>
        struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, stored_map_values> :
            lt_t<LeftArgument, stored_map_values> {
        };

        // Specializations of lt<LeftType, RightType> with bitsets.
        template<bitset_t LeftBitset, bitset_t RightBitset>
        struct lt<constant_bitset<LeftBitset>, constant_bitset<RightBitset> > :
            std::bool_constant<(LeftBitset < RightBitset)> {
        };

        template<bitset_t LeftBitset, tag_t RightTag, std::size_t RightIndex>
        struct lt<constant_bitset<LeftBitset>, get_bitset<RightTag, RightIndex> > :
            std::true_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, bitset_t RightBitset>
        struct lt<get_bitset<LeftTag, LeftIndex>, constant_bitset<RightBitset> > :
            std::false_type {
        };

        template<bitset_t LeftBitset, tag_t RightTag, std::size_t RightIndex>
        struct lt<constant_bitset<LeftBitset>, get_map_bitsets<RightTag, RightIndex> > :
            std::true_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, bitset_t RightBitset>
        struct lt<get_map_bitsets<LeftTag, LeftIndex>, constant_bitset<RightBitset> > :
            std::false_type {
        };

        template<bitset_t LeftBitset>
        struct lt<constant_bitset<LeftBitset>, stored_bitset> :
            std::true_type {
        };

        template<bitset_t RightBitset>
        struct lt<stored_bitset, constant_bitset<RightBitset> > :
            std::false_type {
        };

        template<bitset_t LeftBitset>
        struct lt<constant_bitset<LeftBitset>, stored_map_bitsets> :
            std::true_type {
        };

        template<bitset_t RightBitset>
        struct lt<stored_map_bitsets, constant_bitset<RightBitset> > :
            std::false_type {
        };

        template<bitset_t LeftBitset, name_t RightName, typename... RightArguments>
        struct lt<constant_bitset<LeftBitset>, function<RightName, RightArguments...> > :
            std::true_type {
        };

        template<name_t LeftName, typename... LeftArguments, bitset_t RightBitset>
        struct lt<function<LeftName, LeftArguments...>, constant_bitset<RightBitset> > :
            std::false_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
        struct lt<get_bitset<LeftTag, LeftIndex>, get_bitset<RightTag, RightIndex> > :
            std::bool_constant<(LeftTag < RightTag || (LeftTag == RightTag && LeftIndex < RightIndex))> {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
        struct lt<get_bitset<LeftTag, LeftIndex>, get_map_bitsets<RightTag, RightIndex> > :
            std::bool_constant<(LeftTag <= RightTag)> {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
        struct lt<get_map_bitsets<LeftTag, LeftIndex>, get_bitset<RightTag, RightIndex> > :
            std::bool_constant<(LeftTag < RightTag)> {
        };

        template<tag_t LeftTag, std::size_t LeftIndex>
        struct lt<get_bitset<LeftTag, LeftIndex>, stored_bitset> :
            std::true_type {
        };

        template<tag_t RightTag, std::size_t RightIndex>
        struct lt<stored_bitset, get_bitset<RightTag, RightIndex> > :
            std::false_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex>
        struct lt<get_bitset<LeftTag, LeftIndex>, stored_map_bitsets> :
            std::true_type {
        };

        template<tag_t RightTag, std::size_t RightIndex>
        struct lt<stored_map_bitsets, get_bitset<RightTag, RightIndex> > :
            std::false_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, name_t RightName, typename RightArgument, typename... RightNextArguments>
        struct lt<get_bitset<LeftTag, LeftIndex>, function<RightName, RightArgument, RightNextArguments...> > :
            le_t<get_bitset<LeftTag, LeftIndex>, RightArgument> {
        };

        template<name_t LeftName, typename LeftArgument, typename... LeftNextArguments, tag_t RightTag, std::size_t RightIndex>
        struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, get_bitset<RightTag, RightIndex> > :
            lt_t<LeftArgument, get_bitset<RightTag, RightIndex> > {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
        struct lt<get_map_bitsets<LeftTag, LeftIndex>, get_map_bitsets<RightTag, RightIndex> > :
            std::bool_constant<(LeftTag < RightTag || (LeftTag == RightTag && LeftIndex < RightIndex))> {
        };

        template<tag_t LeftTag, std::size_t LeftIndex>
        struct lt<get_map_bitsets<LeftTag, LeftIndex>, stored_bitset> :
            std::true_type {
        };

        template<tag_t RightTag, std::size_t RightIndex>
        struct lt<stored_bitset, get_map_bitsets<RightTag, RightIndex> > :
            std::false_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex>
        struct lt<get_map_bitsets<LeftTag, LeftIndex>, stored_map_bitsets> :
            std::true_type {
        };

        template<tag_t RightTag, std::size_t RightIndex>
        struct lt<stored_map_bitsets, get_map_bitsets<RightTag, RightIndex> > :
            std::false_type {
        };

        template<tag_t LeftTag, std::size_t LeftIndex, name_t RightName, typename RightArgument, typename... RightNextArguments>
        struct lt<get_map_bitsets<LeftTag, LeftIndex>, function<RightName, RightArgument, RightNextArguments...> > :
            le_t<get_map_bitsets<LeftTag, LeftIndex>, RightArgument> {
        };

        template<name_t LeftName, typename LeftArgument, typename... LeftNextArguments, tag_t RightTag, std::size_t RightIndex>
        struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, get_map_bitsets<RightTag, RightIndex> > :
            lt_t<LeftArgument, get_map_bitsets<RightTag, RightIndex> > {
        };

        template<>
        struct lt<stored_bitset, stored_bitset> :
            std::false_type {
        };

        template<>
        struct lt<stored_bitset, stored_map_bitsets> :
            std::true_type {
        };

        template<>
        struct lt<stored_map_bitsets, stored_bitset> :
            std::false_type {
        };

        template<name_t RightName, typename RightArgument, typename... RightNextArguments>
        struct lt<stored_bitset, function<RightName, RightArgument, RightNextArguments...> > :
            le_t<stored_bitset, RightArgument> {
        };

        template<name_t LeftName, typename LeftArgument, typename... LeftNextArguments>
        struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, stored_bitset> :
            lt_t<LeftArgument, stored_bitset> {
        };
        template<>
        struct lt<stored_map_bitsets, stored_map_bitsets> :
            std::false_type {
        };

        template<name_t RightName, typename RightArgument, typename... RightNextArguments>
        struct lt<stored_map_bitsets, function<RightName, RightArgument, RightNextArguments...> > :
            le_t<stored_map_bitsets, RightArgument> {
        };

        template<name_t LeftName, typename LeftArgument, typename... LeftNextArguments>
        struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, stored_map_bitsets> :
            lt_t<LeftArgument, stored_map_bitsets> {
        };

        // Specializations of lt<LeftType, RightType> with basis blades.
        template<bitset_t LeftBasisVectors, bitset_t RightBasisVectors>
        struct lt<constant_basis_blade<LeftBasisVectors>, constant_basis_blade<RightBasisVectors> > :
            std::bool_constant<(possible_grades_v<constant_basis_blade<LeftBasisVectors> > < possible_grades_v<constant_basis_blade<RightBasisVectors> > || (possible_grades_v<constant_basis_blade<LeftBasisVectors> > == possible_grades_v<constant_basis_blade<RightBasisVectors> > && LeftBasisVectors < RightBasisVectors))> {
        };

        template<bitset_t LeftBasisVectors, bitset_t RightPossibleGrades, typename RightBitset>
        struct lt<constant_basis_blade<LeftBasisVectors>, dynamic_basis_blade<RightPossibleGrades, RightBitset> > :
            std::bool_constant<(possible_grades_v<constant_basis_blade<LeftBasisVectors> > <= RightPossibleGrades)> {
        };

        template<bitset_t LeftPossibleGrades, typename LeftBitset, bitset_t RightBasisVectors>
        struct lt<dynamic_basis_blade<LeftPossibleGrades, LeftBitset>, constant_basis_blade<RightBasisVectors> > :
            std::bool_constant<(LeftPossibleGrades < possible_grades_v<constant_basis_blade<RightBasisVectors> >)> {
        };

        template<bitset_t LeftPossibleGrades, typename LeftBitset, bitset_t RightPossibleGrades, typename RightBitset>
        struct lt<dynamic_basis_blade<LeftPossibleGrades, LeftBitset>, dynamic_basis_blade<RightPossibleGrades, RightBitset> > :
            std::bool_constant<(LeftPossibleGrades < RightPossibleGrades || (LeftPossibleGrades == RightPossibleGrades && lt_v<LeftBitset, RightBitset>))> {
        };

        // Specializations of lt<LeftType, RightType> with components.
        template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade>
        struct lt<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > :
            std::bool_constant<(lt_v<LeftBasisBlade, RightBasisBlade> || (eq_v<LeftBasisBlade, RightBasisBlade> && lt_v<LeftCoefficient, RightCoefficient>))> {
        };

        // Specializations of lt<LeftType, RightType> with functions.
        template<typename... Arguments>
        struct _arguments_list {
        };

        template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
        struct lt<_arguments_list<LeftArgument, LeftNextArguments...>, _arguments_list<RightArgument, RightNextArguments...> > :
            std::conditional_t<
                is_constant_expression_v<LeftArgument>,
                std::conditional_t<
                    is_constant_expression_v<RightArgument>,
                    lt_t<_arguments_list<LeftNextArguments...>, _arguments_list<RightNextArguments...> >,
                    lt_t<_arguments_list<LeftNextArguments...>, _arguments_list<RightArgument, RightNextArguments...> >
                >,
                std::conditional_t<
                    is_constant_expression_v<RightArgument>,
                    lt_t<_arguments_list<LeftArgument, LeftNextArguments...>, _arguments_list<RightNextArguments...> >,
                    std::bool_constant<(lt_v<LeftArgument, RightArgument> || (eq_v<LeftArgument, RightArgument> && lt_v<_arguments_list<LeftNextArguments...>, _arguments_list<RightNextArguments...> >))>
                >
            > {
        };

        template<typename LeftArgument, typename RightArgument, typename... RightNextArguments>
        struct lt<_arguments_list<LeftArgument>, _arguments_list<RightArgument, RightNextArguments...> > :
            std::conditional_t<
                is_constant_expression_v<LeftArgument>,
                std::true_type,
                std::conditional_t<
                    is_constant_expression_v<RightArgument>,
                    lt_t<_arguments_list<LeftArgument>, _arguments_list<RightNextArguments...> >,
                    le_t<LeftArgument, RightArgument>
                >
            > {
        };

        template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument>
        struct lt<_arguments_list<LeftArgument, LeftNextArguments...>, _arguments_list<RightArgument> > :
            std::conditional_t<
                is_constant_expression_v<LeftArgument>,
                std::conditional_t<
                    is_constant_expression_v<RightArgument>,
                    lt_t<LeftArgument, RightArgument>,
                    lt_t<_arguments_list<LeftNextArguments...>, _arguments_list<RightArgument> >
                >,
                std::conditional_t<
                    is_constant_expression_v<RightArgument>,
                    std::false_type,
                    lt_t<LeftArgument, RightArgument>
                >
            > {
        };

        template<typename LeftArgument, typename RightArgument>
        struct lt<_arguments_list<LeftArgument>, _arguments_list<RightArgument> > :
            lt_t<LeftArgument, RightArgument> {
        };

        template<name_t LeftName, typename... LeftArguments, name_t RightName, typename... RightArguments>
        struct lt<function<LeftName, LeftArguments...>, function<RightName, RightArguments...> > :
            std::bool_constant<(LeftName < RightName || (LeftName == RightName && lt_v<_arguments_list<LeftArguments...>, _arguments_list<RightArguments...> >))> {
        };
        /**/

    }

}

#endif // __GA_CORE_RELATIONAL_OPERATORS_HPP__
