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

#ifndef __GA_CORE_LAZY_CONTEXT_HPP__
#define __GA_CORE_LAZY_CONTEXT_HPP__

namespace ga {

    namespace detail {
    
        // Returns the greater ID found in the given expressions.
        template<typename... Expressions>
        struct greater_id;

        template<typename... Expressions>
        constexpr tag_t greater_id_v = greater_id<Expressions...>::value;

        template<typename Expression, typename... NextExpressions>
        struct greater_id<Expression, NextExpressions...> {
            constexpr static tag_t value = std::max(greater_id_v<Expression>, greater_id_v<NextExpressions...>); // recursion
        };

        template<>
        struct greater_id<> {
            constexpr static tag_t value = 0; // end of recursion
        };

        template<typename Expression>
        struct greater_id<Expression> {
            constexpr static tag_t value = 0; // default
        };

        template<tag_t Tag, std::size_t Index>
        struct greater_id<get_value<Tag, Index> > {
            constexpr static tag_t value = Tag;
        };

        template<tag_t Tag, std::size_t Index>
        struct greater_id<get_map_values<Tag, Index> > {
            constexpr static tag_t value = Tag;
        };

        template<tag_t Tag, std::size_t Index>
        struct greater_id<get_bitset<Tag, Index> > {
            constexpr static tag_t value = Tag;
        };

        template<tag_t Tag, std::size_t Index>
        struct greater_id<get_map_bitsets<Tag, Index> > {
            constexpr static tag_t value = Tag;
        };

        template<bitset_t PossibleGrades, typename Bitset>
        struct greater_id<dynamic_basis_blade<PossibleGrades, Bitset> > {
            constexpr static tag_t value = greater_id_v<Bitset>;
        };

        template<typename Coefficient, typename BasisBlade>
        struct greater_id<component<Coefficient, BasisBlade> > {
            constexpr static tag_t value = std::max(greater_id_v<Coefficient>, greater_id_v<BasisBlade>);
        };

        template<name_t Name, typename... Arguments>
        struct greater_id<function<Name, Arguments...> > {
            constexpr static tag_t value = greater_id_v<Arguments...>;
        };

        // Produces an expression where stored_value, stored_map_values, stored_bitset, and stored_map_bitsets change to get_value<Tag, Index>, get_map_values<Tag, Index>, get_bitset<Tag, Index>, and get_map_bitsets<Tag, Index>, respectively.
        template<typename Expression, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
        struct tag_variables;

        template<typename Expression, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
        using tag_variables_t = typename tag_variables<Expression, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex>::type;

        template<typename Expression, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
        struct tag_variables {
            using type = Expression; // default
        };

        template<tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
        struct tag_variables<stored_value, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
            using type = get_value<Tag, BaseValueIndex>;
        };

        template<tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
        struct tag_variables<stored_bitset, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
            using type = get_bitset<Tag, BaseBitsetIndex>;
        };

        template<bitset_t PossibleGrades, typename Bitset, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
        struct tag_variables<dynamic_basis_blade<PossibleGrades, Bitset>, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
            using type = dynamic_basis_blade_t<PossibleGrades, tag_variables_t<Bitset, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> >;
        };

        template<typename Coefficient, typename BasisBlade, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
        struct tag_variables<component<Coefficient, BasisBlade>, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
            using type = component_t<tag_variables_t<Coefficient, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex>, tag_variables_t<BasisBlade, Tag, BaseValueIndex + count_stored_values_v<Coefficient>, BaseBitsetIndex + count_stored_bitsets_v<Coefficient>, BaseMapIndex + count_stored_maps_v<Coefficient> > >;
        };

        template<bitset_t PossibleGrades, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
        struct tag_variables<component<stored_map_values, dynamic_basis_blade<PossibleGrades, stored_map_bitsets> >, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
            using type = component_t<get_map_values<Tag, BaseMapIndex>, dynamic_basis_blade<PossibleGrades, get_map_bitsets<Tag, BaseMapIndex> > >;
        };

        template<tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex, typename Function, typename... Arguments>
        struct _tag_variables_in_function;

        template<tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex, name_t Name, typename... FunctionArguments, typename Argument, typename... NextArguments>
        struct _tag_variables_in_function<Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex, function<Name, FunctionArguments...>, Argument, NextArguments...> {
            using type = typename _tag_variables_in_function<Tag, BaseValueIndex + count_stored_values_v<Argument>, BaseBitsetIndex + count_stored_bitsets_v<Argument>, BaseMapIndex + count_stored_maps_v<Argument>, function<Name, FunctionArguments..., tag_variables_t<Argument, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> >, NextArguments...>::type;
        };

        template<tag_t Tag, std::size_t ValueIndexEnd, std::size_t BitsetIndexEnd, std::size_t MapIndexEnd, name_t Name, typename... FunctionArguments>
        struct _tag_variables_in_function<Tag, ValueIndexEnd, BitsetIndexEnd, MapIndexEnd, function<Name, FunctionArguments...> > {
            using type = function<Name, FunctionArguments...>;
        };

        template<name_t Name, typename... Arguments, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
        struct tag_variables<function<Name, Arguments...>, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
            using type = typename _tag_variables_in_function<Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex, function<Name>, Arguments...>::type;
        };

        // Evaluates the given (or the collection of) clifford_expression<...>.
        template<tag_t LowerTag, tag_t UpperTag, typename Expression>
        struct eval_clifford_expression;

        template<tag_t LowerTag, tag_t UpperTag, typename Expression, typename... InputTypes>
        using eval_coefficient_t = typename eval_clifford_expression<LowerTag, UpperTag, Expression>::template coefficient_type<InputTypes...>::type;

        template<tag_t LowerTag, tag_t UpperTag, typename Expression>
        using eval_expression_t = typename eval_clifford_expression<LowerTag, UpperTag, Expression>::expression_type;

        template<tag_t LowerTag, tag_t UpperTag, typename Expression, typename... NextExpressions>
        struct eval_clifford_expressions {
            template<typename... InputTypes>
            struct coefficient_type {
                using type = std::common_type_t<typename eval_clifford_expression<LowerTag, UpperTag, Expression>::template coefficient_type<InputTypes...>::type, typename eval_clifford_expressions<LowerTag, UpperTag, NextExpressions...>::template coefficient_type<InputTypes...>::type>;
            };

            // expression_type is not defined here.

            template<typename ValueItr, typename BitsetItr, typename MapIts, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static void run(ValueItr &value_itr, BitsetItr &bitset_itr, MapIts &map_itr, std::tuple<InputTypes...> const &args) {
                eval_clifford_expression<LowerTag, UpperTag, Expression>::run(value_itr, bitset_itr, map_itr, args);
                eval_clifford_expressions<LowerTag, UpperTag, NextExpressions...>::run(value_itr, bitset_itr, map_itr, args);
            }
        };

        template<tag_t LowerTag, tag_t UpperTag, typename Expression>
        struct eval_clifford_expressions<LowerTag, UpperTag, Expression> {
            template<typename... InputTypes>
            struct coefficient_type {
                using type = typename eval_clifford_expression<LowerTag, UpperTag, Expression>::template coefficient_type<InputTypes...>::type;
            };

            // expression_type is not defined here.

            template<typename ValueItr, typename BitsetItr, typename MapIts, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static void run(ValueItr &value_itr, BitsetItr &bitset_itr, MapIts &map_itr, std::tuple<InputTypes...> const &args) {
                eval_clifford_expression<LowerTag, UpperTag, Expression>::run(value_itr, bitset_itr, map_itr, args);
            }
        };

        template<typename Expression>
        struct _eval_clifford_expression_do_nothing {
            template<typename... InputTypes>
            struct coefficient_type {
                using type = default_integral_t;
            };

            using expression_type = Expression ;

            template<typename ValueItr, typename BitsetItr, typename MapIts, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static void run(ValueItr const &, BitsetItr const &, MapIts const &, std::tuple<InputTypes...> const &) GA_NOEXCEPT {
                // Do nothing.
            }
        };

        template<tag_t LowerTag, tag_t UpperTag, typename ExpressionType, typename... Expressions>
        struct _eval_clifford_expression_move {
            template<typename... InputTypes>
            struct coefficient_type {
                using type = typename eval_clifford_expressions<LowerTag, UpperTag, Expressions...>::template coefficient_type<InputTypes...>::type;
            };

            using expression_type = ExpressionType;

            template<typename ValueItr, typename BitsetItr, typename MapIts, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static void run(ValueItr &value_itr, BitsetItr &bitset_itr, MapIts &map_itr, std::tuple<InputTypes...> const &args) {
                eval_clifford_expressions<LowerTag, UpperTag, Expressions...>::run(value_itr, bitset_itr, map_itr, args);
            }
        };

        template<tag_t LowerTag, tag_t UpperTag, typename Expression>
        struct _eval_clifford_expression_store_value {
            template<typename... InputTypes>
            struct coefficient_type {
                using type = decltype(Expression::template eval<LowerTag, UpperTag>(std::declval<std::tuple<InputTypes...> >()));
            };

            using expression_type = stored_value;

#pragma warning( push )
#pragma warning( disable : 4244 )

            template<typename ValueItr, typename BitsetItr, typename MapIts, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static void run(ValueItr &value_itr, BitsetItr const &, MapIts const &, std::tuple<InputTypes...> const &args) GA_NOEXCEPT {
                *value_itr = Expression::template eval<LowerTag, UpperTag>(args);
                std::advance(value_itr, 1);
            }

#pragma warning( pop )
        };

        template<tag_t LowerTag, tag_t UpperTag, typename Expression>
        struct _eval_clifford_expression_store_map_values {
            template<typename... InputTypes>
            struct coefficient_type {
                using type = std::nullptr_t; //TODO Not supported yet (map)
            };

            using expression_type = stored_map_values;

            template<typename ValueItr, typename BitsetItr, typename MapIts, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static void run(ValueItr const &, BitsetItr const &, MapIts &map_itr, std::tuple<InputTypes...> const &args) GA_NOEXCEPT {
                //TODO Not supported yet (map)
                throw not_implemented_error("Sorry! The use of ga::clifford_expresion<CoefficientType, Expression> with ga::associative_container_t<ValueType> is not supported yet.");
            }
        };

        template<tag_t LowerTag, tag_t UpperTag, typename Expression>
        struct _eval_clifford_expression_store_bitset {
            template<typename... InputTypes>
            struct coefficient_type {
                using type = default_integral_t;
            };

            using expression_type = stored_bitset;

            template<typename ValueItr, typename BitsetItr, typename MapIts, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static void run(ValueItr const &, BitsetItr &bitset_itr, MapIts const &, std::tuple<InputTypes...> const &args) GA_NOEXCEPT {
                *bitset_itr = Expression::template eval<LowerTag, UpperTag>(args);
                std::advance(bitset_itr, 1);
            }
        };

        template<tag_t LowerTag, tag_t UpperTag, typename Expression>
        struct _eval_clifford_expression_store_map_bitsets {
            template<typename... InputTypes>
            struct coefficient_type {
                using type = std::nullptr_t; //TODO Not supported yet (map)
            };

            using expression_type = stored_map_bitsets;

            template<typename ValueItr, typename BitsetItr, typename MapIts, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static void run(ValueItr const &, BitsetItr const &, MapIts &map_itr, std::tuple<InputTypes...> const &args) GA_NOEXCEPT {
                //TODO Not supported yet (map)
                throw not_implemented_error("Sorry! The use of ga::clifford_expresion<CoefficientType, Expression> with ga::associative_container_t<ValueType> is not supported yet.");
            }
        };

        template<tag_t LowerTag, tag_t UpperTag, typename Expression>
        struct eval_clifford_expression : _eval_clifford_expression_do_nothing<Expression> {
        };

        template<tag_t LowerTag, tag_t UpperTag, tag_t Tag, std::size_t Index>
        struct eval_clifford_expression<LowerTag, UpperTag, get_value<Tag, Index> > :
            std::conditional_t<
                (LowerTag <= Tag && Tag <= UpperTag),
                _eval_clifford_expression_store_value<LowerTag, UpperTag, get_value<Tag, Index> >,
                _eval_clifford_expression_do_nothing<get_value<Tag, Index> >
            > {
        };

        template<tag_t LowerTag, tag_t UpperTag, tag_t Tag, std::size_t Index>
        struct eval_clifford_expression<LowerTag, UpperTag, get_map_values<Tag, Index> > :
            std::conditional_t<
                (LowerTag <= Tag && Tag <= UpperTag),
                _eval_clifford_expression_store_map_values<LowerTag, UpperTag, get_map_values<Tag, Index> >,
                _eval_clifford_expression_do_nothing<get_map_values<Tag, Index> >
            > {
        };

        template<tag_t LowerTag, tag_t UpperTag, tag_t Tag, std::size_t Index>
        struct eval_clifford_expression<LowerTag, UpperTag, get_bitset<Tag, Index> > :
            std::conditional_t<
                (LowerTag <= Tag && Tag <= UpperTag),
                _eval_clifford_expression_store_bitset<LowerTag, UpperTag, get_bitset<Tag, Index> >,
                _eval_clifford_expression_do_nothing<get_bitset<Tag, Index> >
            > {
        };

        template<tag_t LowerTag, tag_t UpperTag, tag_t Tag, std::size_t Index>
        struct eval_clifford_expression<LowerTag, UpperTag, get_map_bitsets<Tag, Index> > :
            std::conditional_t<
                (LowerTag <= Tag && Tag <= UpperTag),
                _eval_clifford_expression_store_map_bitsets<LowerTag, UpperTag, get_map_bitsets<Tag, Index> >,
                _eval_clifford_expression_do_nothing<get_map_bitsets<Tag, Index> >
            > {
        };

        template<tag_t LowerTag, tag_t UpperTag, bitset_t PossibleGrades, typename Bitset>
        struct eval_clifford_expression<LowerTag, UpperTag, dynamic_basis_blade<PossibleGrades, Bitset> > :
            _eval_clifford_expression_move<LowerTag, UpperTag, dynamic_basis_blade_t<PossibleGrades, eval_expression_t<LowerTag, UpperTag, Bitset> >, Bitset> {
        };

        template<tag_t LowerTag, tag_t UpperTag, typename Coefficient, typename BasisBlade>
        struct eval_clifford_expression<LowerTag, UpperTag, component<Coefficient, BasisBlade> > :
            _eval_clifford_expression_move<LowerTag, UpperTag, component_t<eval_expression_t<LowerTag, UpperTag, Coefficient>, eval_expression_t<LowerTag, UpperTag, BasisBlade> >, Coefficient, BasisBlade> {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, name_t Name, typename Argument>
        struct eval_clifford_expression<LowerTag, UpperTag, function<Name, Argument> > :
            std::conditional_t<
                std::is_same_v<eval_expression_t<LowerTag, UpperTag, Argument>, stored_value>,
                _eval_clifford_expression_store_value<LowerTag, UpperTag, function<Name, Argument> >,
                std::conditional_t<
                    std::is_same_v<eval_expression_t<LowerTag, UpperTag, Argument>, stored_bitset>,
                    _eval_clifford_expression_store_bitset<LowerTag, UpperTag, function<Name, Argument> >,
                    _eval_clifford_expression_move<LowerTag, UpperTag, typename function<Name, eval_expression_t<LowerTag, UpperTag, Argument> >::type, Argument>
                >
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, name_t Name, typename LeftArgument, typename RightArgument>
        struct eval_clifford_expression<LowerTag, UpperTag, function<Name, LeftArgument, RightArgument> > :
            std::conditional_t<
                (std::is_same_v<eval_expression_t<LowerTag, UpperTag, LeftArgument>, stored_value> && can_be_stored_v<eval_expression_t<LowerTag, UpperTag, RightArgument> >) || (can_be_stored_v<eval_expression_t<LowerTag, UpperTag, LeftArgument> > && std::is_same_v<eval_expression_t<LowerTag, UpperTag, RightArgument>, stored_value>),
                _eval_clifford_expression_store_value<LowerTag, UpperTag, function<Name, LeftArgument, RightArgument> >,
                std::conditional_t<
                    (std::is_same_v<eval_expression_t<LowerTag, UpperTag, LeftArgument>, stored_bitset> && can_be_stored_v<eval_expression_t<LowerTag, UpperTag, RightArgument> >) || (can_be_stored_v<eval_expression_t<LowerTag, UpperTag, LeftArgument> > && std::is_same_v<eval_expression_t<LowerTag, UpperTag, RightArgument>, stored_bitset>),
                    _eval_clifford_expression_store_bitset<LowerTag, UpperTag, function<Name, LeftArgument, RightArgument> >,
                    _eval_clifford_expression_move<LowerTag, UpperTag, typename function<Name, eval_expression_t<LowerTag, UpperTag, LeftArgument>, eval_expression_t<LowerTag, UpperTag, RightArgument> >::type, LeftArgument, RightArgument>
                >
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, typename Argument, typename... NextArguments>
        struct eval_clifford_expression<LowerTag, UpperTag, add<Argument, NextArguments...> > :
            std::conditional_t<
                (std::is_same_v<eval_expression_t<LowerTag, UpperTag, Argument>, stored_value> && can_be_stored_v<eval_expression_t<LowerTag, UpperTag, add_t<NextArguments...> > >) || (can_be_stored_v<eval_expression_t<LowerTag, UpperTag, Argument> > && std::is_same_v<eval_expression_t<LowerTag, UpperTag, add_t<NextArguments...> >, stored_value>),
                _eval_clifford_expression_store_value<LowerTag, UpperTag, add<Argument, NextArguments...> >,
                _eval_clifford_expression_move<LowerTag, UpperTag, addition_t<eval_expression_t<LowerTag, UpperTag, Argument>, eval_expression_t<LowerTag, UpperTag, add_t<NextArguments...> > >, Argument, add_t<NextArguments...> >
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, typename LeftArgument, typename RightArgument>
        struct eval_clifford_expression<LowerTag, UpperTag, add<LeftArgument, RightArgument> > :
            std::conditional_t<
                (std::is_same_v<eval_expression_t<LowerTag, UpperTag, LeftArgument>, stored_value> && can_be_stored_v<eval_expression_t<LowerTag, UpperTag, RightArgument> >) || (can_be_stored_v<eval_expression_t<LowerTag, UpperTag, LeftArgument> > && std::is_same_v<eval_expression_t<LowerTag, UpperTag, RightArgument>, stored_value>),
                _eval_clifford_expression_store_value<LowerTag, UpperTag, add<LeftArgument, RightArgument> >,
                _eval_clifford_expression_move<LowerTag, UpperTag, addition_t<eval_expression_t<LowerTag, UpperTag, LeftArgument>, eval_expression_t<LowerTag, UpperTag, RightArgument> >, LeftArgument, RightArgument>
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, typename Argument, typename... NextArguments>
        struct eval_clifford_expression<LowerTag, UpperTag, mul<Argument, NextArguments...> > :
            std::conditional_t<
                (std::is_same_v<eval_expression_t<LowerTag, UpperTag, Argument>, stored_value> && can_be_stored_v<eval_expression_t<LowerTag, UpperTag, mul_t<NextArguments...> > >) || (can_be_stored_v<eval_expression_t<LowerTag, UpperTag, Argument> > && std::is_same_v<eval_expression_t<LowerTag, UpperTag, mul_t<NextArguments...> >, stored_value>),
                _eval_clifford_expression_store_value<LowerTag, UpperTag, mul<Argument, NextArguments...> >,
                _eval_clifford_expression_move<LowerTag, UpperTag, product_t<eval_expression_t<LowerTag, UpperTag, Argument>, eval_expression_t<LowerTag, UpperTag, mul_t<NextArguments...> >, value_mapping>, Argument, mul_t<NextArguments...> >
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, typename LeftArgument, typename RightArgument>
        struct eval_clifford_expression<LowerTag, UpperTag, mul<LeftArgument, RightArgument> > :
            std::conditional_t<
                (std::is_same_v<eval_expression_t<LowerTag, UpperTag, LeftArgument>, stored_value> && can_be_stored_v<eval_expression_t<LowerTag, UpperTag, RightArgument> >) || (can_be_stored_v<eval_expression_t<LowerTag, UpperTag, LeftArgument> > && std::is_same_v<eval_expression_t<LowerTag, UpperTag, RightArgument>, stored_value>),
                _eval_clifford_expression_store_value<LowerTag, UpperTag, mul<LeftArgument, RightArgument> >,
                _eval_clifford_expression_move<LowerTag, UpperTag, product_t<eval_expression_t<LowerTag, UpperTag, LeftArgument>, eval_expression_t<LowerTag, UpperTag, RightArgument>, value_mapping>, LeftArgument, RightArgument>
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, typename LeftArgument, typename RightArgument>
        struct eval_clifford_expression<LowerTag, UpperTag, power<LeftArgument, RightArgument> > :
            std::conditional_t<
                (std::is_same_v<eval_expression_t<LowerTag, UpperTag, LeftArgument>, stored_value> && can_be_stored_v<eval_expression_t<LowerTag, UpperTag, RightArgument> >) || (can_be_stored_v<eval_expression_t<LowerTag, UpperTag, LeftArgument> > && std::is_same_v<eval_expression_t<LowerTag, UpperTag, RightArgument>, stored_value>),
                _eval_clifford_expression_store_value<LowerTag, UpperTag, power<LeftArgument, RightArgument> >,
                _eval_clifford_expression_move<LowerTag, UpperTag, power_t<eval_expression_t<LowerTag, UpperTag, LeftArgument>, eval_expression_t<LowerTag, UpperTag, RightArgument> >, LeftArgument, RightArgument>
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, typename LeftBitset, typename RightBitset>
        struct eval_clifford_expression<LowerTag, UpperTag, reordering_sign<LeftBitset, RightBitset> > :
            std::conditional_t<
                (std::is_same_v<eval_expression_t<LowerTag, UpperTag, LeftBitset>, stored_bitset> && can_be_stored_v<eval_expression_t<LowerTag, UpperTag, RightBitset> >) || (can_be_stored_v<eval_expression_t<LowerTag, UpperTag, LeftBitset> > && std::is_same_v<eval_expression_t<LowerTag, UpperTag, RightBitset>, stored_bitset>),
                _eval_clifford_expression_store_value<LowerTag, UpperTag, reordering_sign<LeftBitset, RightBitset> >,
                _eval_clifford_expression_move<LowerTag, UpperTag, reordering_sign_t<eval_expression_t<LowerTag, UpperTag, LeftBitset>, eval_expression_t<LowerTag, UpperTag, RightBitset> >, LeftBitset, RightBitset>
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, typename Bitset>
        struct eval_clifford_expression<LowerTag, UpperTag, count_one_bits<Bitset> > :
            std::conditional_t<
                std::is_same_v<eval_expression_t<LowerTag, UpperTag, Bitset>, stored_bitset>,
                _eval_clifford_expression_store_value<LowerTag, UpperTag, count_one_bits<Bitset> >,
                _eval_clifford_expression_move<LowerTag, UpperTag, count_one_bits_t<eval_expression_t<LowerTag, UpperTag, Bitset> >, Bitset>
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, typename LeftBitset, typename RightValue>
        struct eval_clifford_expression<LowerTag, UpperTag, bitwise_left_shift<LeftBitset, RightValue> > :
            std::conditional_t<
                (std::is_same_v<eval_expression_t<LowerTag, UpperTag, LeftBitset>, stored_bitset> && can_be_stored_v<eval_expression_t<LowerTag, UpperTag, RightValue> >) || (can_be_stored_v<eval_expression_t<LowerTag, UpperTag, LeftBitset> > && std::is_same_v<eval_expression_t<LowerTag, UpperTag, RightValue>, stored_value>),
                _eval_clifford_expression_store_bitset<LowerTag, UpperTag, bitwise_left_shift<LeftBitset, RightValue> >,
                _eval_clifford_expression_move<LowerTag, UpperTag, bitwise_left_shift_t<eval_expression_t<LowerTag, UpperTag, LeftBitset>, eval_expression_t<LowerTag, UpperTag, RightValue> >, LeftBitset, RightValue>
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, typename Bitset>
        struct eval_clifford_expression<LowerTag, UpperTag, bitwise_uminus<Bitset> > :
            std::conditional_t<
                std::is_same_v<eval_expression_t<LowerTag, UpperTag, Bitset>, stored_bitset>,
                _eval_clifford_expression_store_value<LowerTag, UpperTag, bitwise_uminus<Bitset> >,
                _eval_clifford_expression_move<LowerTag, UpperTag, bitwise_uminus_t<eval_expression_t<LowerTag, UpperTag, Bitset> >, Bitset>
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, typename Bitset>
        struct eval_clifford_expression<LowerTag, UpperTag, bitwise_dec<Bitset> > :
            std::conditional_t<
                std::is_same_v<eval_expression_t<LowerTag, UpperTag, Bitset>, stored_bitset>,
                _eval_clifford_expression_store_value<LowerTag, UpperTag, bitwise_dec<Bitset> >,
                _eval_clifford_expression_move<LowerTag, UpperTag, bitwise_dec_t<eval_expression_t<LowerTag, UpperTag, Bitset> >, Bitset>
            > {
        };

        //TODO Not supported yet (map)
        template<tag_t LowerTag, tag_t UpperTag, typename Test, typename TrueValue, typename FalseValue>
        struct eval_clifford_expression<LowerTag, UpperTag, if_else<Test, TrueValue, FalseValue> > :
            std::conditional_t<
                can_be_stored_v<eval_expression_t<LowerTag, UpperTag, Test> > && can_be_stored_v<eval_expression_t<LowerTag, UpperTag, TrueValue> > && can_be_stored_v<eval_expression_t<LowerTag, UpperTag, TrueValue> >,
                _eval_clifford_expression_store_value<LowerTag, UpperTag, if_else<Test, TrueValue, FalseValue> >,
                _eval_clifford_expression_move<LowerTag, UpperTag, if_else_t<eval_expression_t<LowerTag, UpperTag, Test>, eval_expression_t<LowerTag, UpperTag, TrueValue>, eval_expression_t<LowerTag, UpperTag, TrueValue> >, Test, TrueValue, FalseValue>
            > {
        };
        
        template<tag_t LowerTag, tag_t UpperTag, typename CoefficientType, typename Expression, typename... InputTypes, std::enable_if_t<(LowerTag <= UpperTag), int> = 0>
        GA_ALWAYS_INLINE constexpr static decltype(auto) eval(clifford_expression<CoefficientType, Expression> const &, std::tuple<InputTypes...> const &args) {
            using result_type = clifford_expression<eval_coefficient_t<LowerTag, UpperTag, Expression, std::remove_const_t<std::remove_reference_t<InputTypes> >...>, eval_expression_t<LowerTag, UpperTag, Expression> >;

            typename result_type::value_storage_type values;
            typename result_type::bitset_storage_type bitsets;
            typename result_type::map_storage_type maps;

            auto value_itr = values.begin();
            auto bitset_itr = bitsets.begin();
            auto map_itr = maps.begin();

            eval_clifford_expression<LowerTag, UpperTag, Expression>::run(value_itr, bitset_itr, map_itr, args);

            return result_type(std::move(values), std::move(bitsets), std::move(maps));
        }

        template<tag_t LowerTag, tag_t UpperTag, typename CoefficientType, typename Expression, typename... InputTypes, std::enable_if_t<(LowerTag > UpperTag), int> = 0>
        GA_ALWAYS_INLINE constexpr static decltype(auto) eval(clifford_expression<CoefficientType, Expression> const &, std::tuple<InputTypes...> const &) {
            return clifford_expression<CoefficientType, Expression>();
        }

        // Superclass for ga::lazy_context<InputTypes...>.
        template<tag_t BaseTag, typename... InputTypes>
        class _super_lazy_context;

        template<size_t ReverseIndex, typename InputCoefficientType, typename InputExpression, bool StoredReference = has_stored_entries_v<InputExpression> >
        class _super_lazy_context_input {
        public:

            using input_type = clifford_expression<InputCoefficientType, InputExpression>;

            constexpr _super_lazy_context_input(_super_lazy_context_input const &) = default;
            constexpr _super_lazy_context_input(_super_lazy_context_input &&) = default;

            constexpr _super_lazy_context_input(input_type const &input) GA_NOEXCEPT :
                input_(input) {
            }

            constexpr _super_lazy_context_input & operator=(_super_lazy_context_input const &) = delete;
            constexpr _super_lazy_context_input & operator=(_super_lazy_context_input &&) = delete;

            constexpr decltype(auto) get_as_tuple() const GA_NOEXCEPT {
                return std::tie(input_);
            }

            constexpr static bool is_stored() GA_NOEXCEPT {
                return true;
            }

        private:

            input_type const &input_;
        };

        template<std::size_t ReverseIndex, typename InputCoefficientType, typename InputExpression>
        class _super_lazy_context_input<ReverseIndex, InputCoefficientType, InputExpression, false> {
        public:

            using input_type = clifford_expression<InputCoefficientType, InputExpression>;

            constexpr _super_lazy_context_input(_super_lazy_context_input const &) = default;
            constexpr _super_lazy_context_input(_super_lazy_context_input &&) = default;

            constexpr _super_lazy_context_input(clifford_expression<InputCoefficientType, InputExpression> const &) GA_NOEXCEPT {
            }

            constexpr _super_lazy_context_input & operator=(_super_lazy_context_input const &) = delete;
            constexpr _super_lazy_context_input & operator=(_super_lazy_context_input &&) = delete;

            constexpr decltype(auto) get_as_tuple() const GA_NOEXCEPT {
                return std::make_tuple();
            }

            constexpr static bool is_stored() GA_NOEXCEPT {
                return false;
            }
        };

        template<tag_t BaseTag, typename InputCoefficientType, typename InputExpression, typename... OtherInputCoefficientTypes, typename... OtherInputExpressions>
        class _super_lazy_context<BaseTag, clifford_expression<InputCoefficientType, InputExpression>, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions>...> :
            private _super_lazy_context_input<sizeof...(OtherInputExpressions), InputCoefficientType, InputExpression>,
            private _super_lazy_context<_super_lazy_context_input<sizeof...(OtherInputExpressions), InputCoefficientType, InputExpression>::is_stored() ? BaseTag + 1 : BaseTag, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions>...> {
        private:

            using super_input = _super_lazy_context_input<sizeof...(OtherInputExpressions), InputCoefficientType, InputExpression>;
            using super_recursive = _super_lazy_context<super_input::is_stored() ? BaseTag + 1 : BaseTag, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions>...>;

        public:

            template<std::size_t Index, typename _Dummy = void>
            struct argument {
                using type = typename super_recursive::template argument<Index - 1>::type;
            };

            template<typename _Dummy>
            struct argument<0, _Dummy> {
                using type = std::conditional_t<
                    super_input::is_stored(),
                    clifford_expression<InputCoefficientType, tag_variables_t<InputExpression, BaseTag + 1, 0, 0, 0> >,
                    typename super_input::input_type
                >;
            };

            constexpr _super_lazy_context(_super_lazy_context const &) = default;
            constexpr _super_lazy_context(_super_lazy_context &&) = default;

            constexpr _super_lazy_context(clifford_expression<InputCoefficientType, InputExpression> const &input, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions> const &... other_inputs) GA_NOEXCEPT :
                super_input(input),
                super_recursive(other_inputs...) {
            }

            constexpr _super_lazy_context & operator=(_super_lazy_context const &) = delete;
            constexpr _super_lazy_context & operator=(_super_lazy_context &&) = delete;

            constexpr decltype(auto) stored_inputs_tuple() const GA_NOEXCEPT {
                return std::tuple_cat(super_input::get_as_tuple(), super_recursive::stored_inputs_tuple());
            }

            constexpr static std::size_t stored_inputs_count() GA_NOEXCEPT {
                return (super_input::is_stored() ? 1 : 0) + super_recursive::stored_inputs_count();
            }
        };

        template<tag_t BaseTag>
        class _super_lazy_context<BaseTag> {
        public:

            constexpr _super_lazy_context() = default;
            constexpr _super_lazy_context(_super_lazy_context const &) = default;
            constexpr _super_lazy_context(_super_lazy_context &&) = default;

            constexpr _super_lazy_context & operator=(_super_lazy_context const &) = delete;
            constexpr _super_lazy_context & operator=(_super_lazy_context &&) = delete;

            constexpr decltype(auto) stored_inputs_tuple() const GA_NOEXCEPT {
                return std::make_tuple();
            }

            constexpr static std::size_t stored_inputs_count() GA_NOEXCEPT {
                return 0;
            }
        };
    
    }

    // Helper structure to define lazy arguments for lazy evaluation of Clifford expressions.
    template<typename... InputTypes>
    class lazy_context;

    template<typename... InputCoefficientTypes, typename... InputExpressions>
    class lazy_context<clifford_expression<InputCoefficientTypes, InputExpressions>...> final :
        private detail::_super_lazy_context<detail::greater_id_v<InputExpressions...>, clifford_expression<InputCoefficientTypes, InputExpressions>...> {
    private:

        constexpr static detail::tag_t base_id = detail::greater_id_v<InputExpressions...>;
        
        using super = detail::_super_lazy_context<base_id, clifford_expression<InputCoefficientTypes, InputExpressions>...>;

    public:

        template<std::size_t Index>
        using argument_t = typename super::template argument<Index>::type;

        template<std::size_t Index>
        using argument_coefficient_t = typename argument_t<Index>::coefficient_type;

        template<std::size_t Index>
        using argument_expression_t = typename argument_t<Index>::expression_type;

        constexpr lazy_context(lazy_context const &) = default;
        constexpr lazy_context(lazy_context &&) = default;

        constexpr lazy_context(clifford_expression<InputCoefficientTypes, InputExpressions> const &... inputs) GA_NOEXCEPT :
            super(inputs...) {
        }

        constexpr lazy_context & operator=(lazy_context const &) = delete;
        constexpr lazy_context & operator=(lazy_context &&) = delete;

        template<std::size_t Index>
        constexpr static decltype(auto) argument() GA_NOEXCEPT {
            return argument_t<Index>();
        }

        constexpr static decltype(auto) arguments() GA_NOEXCEPT {
            return arguments_tuple(std::make_index_sequence<sizeof...(InputExpressions)>());
        }

        template<typename CoefficientType, typename Expression>
        constexpr decltype(auto) eval(clifford_expression<CoefficientType, Expression> const &expression) const {
            return detail::eval<base_id + 1, base_id + (detail::tag_t)super::stored_inputs_count()>(expression, super::stored_inputs_tuple());
        }

    private:

        template<std::size_t... Indices>
        constexpr static decltype(auto) arguments_tuple(std::index_sequence<Indices...>) GA_NOEXCEPT {
            return std::make_tuple(argument<Indices>()...);
        }
    };

    template<typename... InputTypes>
    constexpr decltype(auto) make_lazy_context(InputTypes const &... inputs) GA_NOEXCEPT {
        return lazy_context<InputTypes...>(inputs...);
    }

    template<typename... InputTypes>
    constexpr decltype(auto) make_lazy_context_tuple(InputTypes const &... inputs) GA_NOEXCEPT {
        lazy_context<InputTypes...> lazy(inputs...);
        return std::tuple_cat(std::make_tuple(lazy), lazy.arguments());
    }

}

#endif // __GA_CORE_LAZY_CONTEXT_HPP__
