#ifndef __GA_CORE_EXPRESSION_TRAITS_HPP__
#define __GA_CORE_EXPRESSION_TRAITS_HPP__

namespace ga {

	namespace detail {

		// Returns whether the given expressions can be stored if necessary.
		template<class... Expressions>
		struct can_be_stored;

		template<class... Expressions>
		constexpr bool can_be_stored_v = can_be_stored<Expressions...>::value;

		template<class Expression, class... NextExpressions>
		struct can_be_stored<Expression, NextExpressions...> {
			constexpr static bool value = can_be_stored_v<Expression> && can_be_stored_v<NextExpressions...>; // recursion
		};

		template<>
		struct can_be_stored<> {
			constexpr static bool value = true; // end of recursion
		};

		template<class Expression>
		struct can_be_stored<Expression> {
			constexpr static bool value = false; // default
		};

		template<default_integral_t Value>
		struct can_be_stored<constant_value<Value> > {
			constexpr static bool value = true;
		};

		template<>
		struct can_be_stored<stored_value> {
			constexpr static bool value = true;
		};

		template<>
		struct can_be_stored<stored_map_values> {
			constexpr static bool value = true;
		};

		template<default_bitset_t Bitset>
		struct can_be_stored<constant_bitset<Bitset> > {
			constexpr static bool value = true;
		};

		template<>
		struct can_be_stored<stored_bitset> {
			constexpr static bool value = true;
		};

		template<>
		struct can_be_stored<stored_map_bitsets> {
			constexpr static bool value = true;
		};

		template<default_bitset_t Bitset>
		struct can_be_stored<constant_basis_blade<Bitset> > {
			constexpr static bool value = true;
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct can_be_stored<dynamic_basis_blade<PossibleGrades, Bitset> > {
			constexpr static bool value = can_be_stored_v<Bitset>;
		};

		template<class Coefficient, class BasisBlade>
		struct can_be_stored<component<Coefficient, BasisBlade> > {
			constexpr static bool value = can_be_stored_v<Coefficient> && can_be_stored_v<BasisBlade>;
		};

		template<name_t Name, class... Arguments>
		struct can_be_stored<function<Name, Arguments...> > {
			constexpr static bool value = can_be_stored_v<Arguments...>;
		};

		// Specializations of is_constant_expression<Expressions...>.
		template<class Expression, class... NextExpressions>
		struct is_constant_expression<Expression, NextExpressions...> {
			constexpr static bool value = is_constant_expression_v<Expression> && is_constant_expression_v<NextExpressions...>; // recursion
		};

		template<>
		struct is_constant_expression<> {
			constexpr static bool value = true; // end of recursion
		};

		template<class Expression>
		struct is_constant_expression<Expression> {
			constexpr static bool value = false; // default
		};

		template<default_integral_t Value>
		struct is_constant_expression<constant_value<Value> > {
			constexpr static bool value = true;
		};

		template<default_bitset_t Bitset>
		struct is_constant_expression<constant_bitset<Bitset> > {
			constexpr static bool value = true;
		};

		template<default_bitset_t Bitset>
		struct is_constant_expression<constant_basis_blade<Bitset> > {
			constexpr static bool value = true;
		};

		template<class Coefficient, class BasisBlade>
		struct is_constant_expression<component<Coefficient, BasisBlade> > {
			constexpr static bool value = is_constant_expression_v<Coefficient> && is_constant_expression_v<BasisBlade>;
		};

		template<name_t Name, class... Arguments>
		struct is_constant_expression<function<Name, Arguments...> > {
			constexpr static bool value = is_constant_expression_v<Arguments...>;
		};

		// Returns whether the given expression is a scalar component.
		template<class Expression>
		struct is_scalar_component {
			constexpr static bool value = false;
		};

		template<class Coefficient>
		struct is_scalar_component<component<Coefficient, constant_basis_blade<default_bitset_t(0)> > > {
			constexpr static bool value = true;
		};

		template<class Expression>
		constexpr bool is_scalar_component_v = is_scalar_component<Expression>::value;

		// Specializations of has_stored_entries<Expressions...>.
		template<class Expression, class... NextExpressions>
		struct has_stored_entries<Expression, NextExpressions...> {
			constexpr static bool value = has_stored_entries_v<Expression> || has_stored_entries_v<NextExpressions...>; // recursion
		};

		template<>
		struct has_stored_entries<> {
			constexpr static bool value = false; // end of recursion
		};

		template<class Expression>
		struct has_stored_entries<Expression> {
			constexpr static bool value = false; // default
		};

		template<>
		struct has_stored_entries<stored_value> {
			constexpr static bool value = true;
		};

		template<>
		struct has_stored_entries<stored_map_values> {
			constexpr static bool value = true;
		};

		template<>
		struct has_stored_entries<stored_bitset> {
			constexpr static bool value = true;
		};

		template<>
		struct has_stored_entries<stored_map_bitsets> {
			constexpr static bool value = true;
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct has_stored_entries<dynamic_basis_blade<PossibleGrades, Bitset> > {
			constexpr static bool value = has_stored_entries_v<Bitset>;
		};

		template<class Coefficient, class BasisBlade>
		struct has_stored_entries<component<Coefficient, BasisBlade> > {
			constexpr static bool value = has_stored_entries_v<Coefficient> || has_stored_entries_v<BasisBlade>;
		};

		template<name_t Name, class... Arguments>
		struct has_stored_entries<function<Name, Arguments...> > {
			constexpr static bool value = has_stored_entries_v<Arguments...>;
		};

		// Returns whether the given expression is an even value for sure.
		template<class Expression>
		struct is_even;

		template<class Expression>
		constexpr bool is_even_v = is_even<Expression>::value;

		template<default_integral_t Value>
		struct is_even<constant_value<Value> > {
			constexpr static bool value = (Value & 1) == 0;
		};

		template<tag_t Tag, std::size_t Index>
		struct is_even<get_value<Tag, Index> > {
			constexpr static bool value = false;
		};

		template<tag_t Tag, std::size_t Index>
		struct is_even<get_map_values<Tag, Index> > {
			constexpr static bool value = false;
		};

		template<>
		struct is_even<stored_value> {
			constexpr static bool value = false;
		};

		template<>
		struct is_even<stored_map_values> {
			constexpr static bool value = false;
		};

		template<class LeftBitset, class RightBitset>
		struct is_even<reordering_sign<LeftBitset, RightBitset> > {
			constexpr static bool value = false;
		};

		template<class Bitset>
		struct is_even<count_one_bits<Bitset> > {
			constexpr static bool value = false;
		};

		template<class Bitset>
		struct is_even<bitwise_uminus<Bitset> > {
			constexpr static bool value = is_even_v<Bitset>;
		};

		template<class Bitset>
		struct is_even<bitwise_dec<Bitset> > {
			constexpr static bool value = !is_even_v<Bitset>;
		};

		template<class LeftType, class RightType>
		struct is_even<bitwise_and<LeftType, RightType> > {
			constexpr static bool value = is_even_v<LeftType> && is_even_v<RightType>;
		};

		template<class LeftType, class RightType>
		struct is_even<bitwise_or<LeftType, RightType> > {
			constexpr static bool value = is_even_v<LeftType> || is_even_v<RightType>;
		};

		template<class LeftType, class RightType>
		struct is_even<bitwise_xor<LeftType, RightType> > {
			constexpr static bool value = false;
		};

		template<class Test, class TrueValue, class FalseValue>
		struct is_even<if_else<Test, TrueValue, FalseValue> > {
			constexpr static bool value = is_even_v<TrueValue> && is_even_v<FalseValue>;
		};

		template<class Value>
		struct is_even<absolute<Value> > {
			constexpr static bool value = is_even_v<Value>;
		};

		template<class Value>
		struct is_even<exponential<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_even<logarithm<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_even<cosine<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_even<sine<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_even<tangent<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_even<hyperbolic_cosine<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_even<hyperbolic_sine<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_even<hyperbolic_tangent<Value> > {
			constexpr static bool value = false;
		};

		template<class LeftArgument, class RightArgument>
		struct is_even<power<LeftArgument, RightArgument> > {
			constexpr static bool value = is_even_v<RightArgument>;
		};

		template<class... Arguments>
		struct is_even<mul<Arguments...> > {
			constexpr static bool value = false;
		};

		template<class... Arguments>
		struct is_even<add<Arguments...> > {
			constexpr static bool value = false;
		};

		// Specializations of is_function<Expression>.
		template<name_t Name, class Expression>
		struct is_function {
			constexpr static bool value = false;
		};

		template<name_t Name, class... Arguments>
		struct is_function<Name, function<Name, Arguments...> > {
			constexpr static bool value = true;
		};

		// Specializations of is_non_negative<Expression>.
		template<default_integral_t Value>
		struct is_non_negative<constant_value<Value> > {
			constexpr static bool value = Value >= 0;
		};

		template<tag_t Tag, std::size_t Index>
		struct is_non_negative<get_value<Tag, Index> > {
			constexpr static bool value = false;
		};
		
		template<tag_t Tag, std::size_t Index>
		struct is_non_negative<get_map_values<Tag, Index> > {
			constexpr static bool value = false;
		};

		template<>
		struct is_non_negative<stored_value> {
			constexpr static bool value = false;
		};

		template<>
		struct is_non_negative<stored_map_values> {
			constexpr static bool value = false;
		};

		template<class LeftBitset, class RightBitset>
		struct is_non_negative<reordering_sign<LeftBitset, RightBitset> > {
			constexpr static bool value = true;
		};

		template<class Bitset>
		struct is_non_negative<count_one_bits<Bitset> > {
			constexpr static bool value = true;
		};

		template<class Bitset>
		struct is_non_negative<bitwise_uminus<Bitset> > {
			constexpr static bool value = true;
		};

		template<class Bitset>
		struct is_non_negative<bitwise_dec<Bitset> > {
			constexpr static bool value = true;
		};

		template<class LeftType, class RightType>
		struct is_non_negative<bitwise_and<LeftType, RightType> > {
			constexpr static bool value = true;
		};

		template<class LeftType, class RightType>
		struct is_non_negative<bitwise_or<LeftType, RightType> > {
			constexpr static bool value = true;
		};

		template<class LeftType, class RightType>
		struct is_non_negative<bitwise_xor<LeftType, RightType> > {
			constexpr static bool value = true;
		};

		template<class Test, class TrueValue, class FalseValue>
		struct is_non_negative<if_else<Test, TrueValue, FalseValue> > {
			constexpr static bool value = is_non_negative_v<TrueValue> && is_non_negative_v<FalseValue>;
		};

		template<class Value>
		struct is_non_negative<absolute<Value> > {
			constexpr static bool value = true;
		};

		template<class Value>
		struct is_non_negative<exponential<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_non_negative<logarithm<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_non_negative<cosine<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_non_negative<sine<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_non_negative<tangent<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_non_negative<hyperbolic_cosine<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_non_negative<hyperbolic_sine<Value> > {
			constexpr static bool value = false;
		};

		template<class Value>
		struct is_non_negative<hyperbolic_tangent<Value> > {
			constexpr static bool value = false;
		};

		template<class LeftArgument, class RightArgument>
		struct is_non_negative<power<LeftArgument, RightArgument> > {
			constexpr static bool value = is_non_negative_v<LeftArgument> || is_even_v<RightArgument>;
		};

		template<class Argument, class... NextArguments>
		struct is_non_negative<mul<Argument, NextArguments...> > {
			constexpr static bool value = is_non_negative_v<Argument> && is_non_negative_v<mul_t<NextArguments...> >;
		};

		template<class... Arguments>
		struct is_non_negative<add<Arguments...> > {
			constexpr static bool value = false;
		};

		// Returns if the given expression may be positive.
		template<class Expression>
		struct may_be_positive;

		template<class Expression>
		constexpr bool may_be_positive_v = may_be_positive<Expressio>::value;

		template<default_integral_t Value>
		struct may_be_positive<constant_value<Value> > {
			constexpr static bool value = Value > 0;
		};

		template<tag_t Tag, std::size_t Index>
		struct may_be_positive<get_value<Tag, Index> > {
			constexpr static bool value = true;
		};
		
		template<tag_t Tag, std::size_t Index>
		struct may_be_positive<get_map_values<Tag, Index> > {
			constexpr static bool value = true;
		};

		template<>
		struct may_be_positive<stored_value> {
			constexpr static bool value = true;
		};

		template<>
		struct may_be_positive<stored_map_values> {
			constexpr static bool value = true;
		};

		template<class LeftBitset, class RightBitset>
		struct may_be_positive<reordering_sign<LeftBitset, RightBitset> > {
			constexpr static bool value = true;
		};

		template<class Bitset>
		struct may_be_positive<count_one_bits<Bitset> > {
			constexpr static bool value = true;
		};

		template<class Bitset>
		struct may_be_positive<bitwise_uminus<Bitset> > {
			constexpr static bool value = true;
		};

		template<class Bitset>
		struct may_be_positive<bitwise_dec<Bitset> > {
			constexpr static bool value = true;
		};

		template<class LeftType, class RightType>
		struct may_be_positive<bitwise_and<LeftType, RightType> > {
			constexpr static bool value = true;
		};

		template<class LeftType, class RightType>
		struct may_be_positive<bitwise_or<LeftType, RightType> > {
			constexpr static bool value = true;
		};

		template<class LeftType, class RightType>
		struct may_be_positive<bitwise_xor<LeftType, RightType> > {
			constexpr static bool value = true;
		};

		template<class Test, class TrueValue, class FalseValue>
		struct may_be_positive<if_else<Test, TrueValue, FalseValue> > {
			constexpr static bool value = may_be_positive_v<TrueValue> && may_be_positive_v<FalseValue>;
		};

		template<class Value>
		struct may_be_positive<absolute<Value> > {
			constexpr static bool value = true;
		};

		template<class Value>
		struct may_be_positive<cosine<Value> > {
			constexpr static bool value = true;
		};

		template<class Value>
		struct may_be_positive<sine<Value> > {
			constexpr static bool value = true;
		};

		template<class Value>
		struct may_be_positive<tangent<Value> > {
			constexpr static bool value = true;
		};

		template<class Value>
		struct may_be_positive<hyperbolic_cosine<Value> > {
			constexpr static bool value = true;
		};

		template<class Value>
		struct may_be_positive<hyperbolic_sine<Value> > {
			constexpr static bool value = true;
		};

		template<class Value>
		struct may_be_positive<hyperbolic_tangent<Value> > {
			constexpr static bool value = true;
		};

		template<class LeftArgument, class RightArgument>
		struct may_be_positive<power<LeftArgument, RightArgument> > {
			constexpr static bool value = may_be_positive_v<LeftArgument> || is_even_v<RightArgument>;
		};

		template<class Argument, class... NextArguments>
		struct may_be_positive<mul<Argument, NextArguments...> > {
			constexpr static bool value = may_be_positive_v<Argument> && may_be_positive_v<mul_t<NextArguments...> >;
		};

		template<class... Arguments>
		struct may_be_positive<add<Arguments...> > {
			constexpr static bool value = true;
		};
		
		// Specializations of possible_grades<BasisVectors>.
		template<default_bitset_t BasisVectors>
		struct possible_grades<constant_basis_blade<BasisVectors> > {
			constexpr static default_bitset_t value = default_bitset_t(1) << ones(BasisVectors);
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct possible_grades<dynamic_basis_blade<PossibleGrades, Bitset> > {
			constexpr static default_bitset_t value = PossibleGrades;
		};

		// Returns the basis blade type that best fit input arguments.
		template<default_bitset_t PossibleGrades, class BasisVectors>
		struct deduce_basis_blade {
			typedef dynamic_basis_blade_t<PossibleGrades, BasisVectors> type;
		};

		template<default_bitset_t PossibleGrades, default_bitset_t BasisVectors>
		struct deduce_basis_blade<PossibleGrades, constant_bitset<BasisVectors> > {
			typedef constant_basis_blade<BasisVectors> type;
		};

		template<default_bitset_t PossibleGrades, class BasisVectors>
		using deduce_basis_blade_t = typename deduce_basis_blade<PossibleGrades, BasisVectors>::type;

		// Returns the coefficient of a given set of components.
		template<class Component>
		struct coefficient;

		template<class Coefficient, class BasisBlade>
		struct coefficient<component<Coefficient, BasisBlade> > {
			typedef Coefficient type;
		};

		template<class Component>
		using coefficient_t = typename coefficient<Component>::type;

		// Returns the basis blade of a given components.
		template<class Component>
		struct basis_blade;

		template<class Coefficient, class BasisBlade>
		struct basis_blade<component<Coefficient, BasisBlade> > {
			typedef BasisBlade type;
		};

		template<class Component>
		using basis_blade_t = typename basis_blade<Component>::type;

		// Returns the basis vectors of a given basis blade.
		template<class BasisBlade>
		struct basis_vectors;

		template<default_bitset_t BasisVectors>
		struct basis_vectors<constant_basis_blade<BasisVectors> > {
			typedef constant_bitset<BasisVectors> type;
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct basis_vectors<dynamic_basis_blade<PossibleGrades, Bitset> > {
			typedef Bitset type;
		};

		template<class BasisBlade>
		using basis_vectors_t = typename basis_vectors<BasisBlade>::type;

		// Returns the bitset of the rightmost set bit in the given bitset.
		template<class Bitset>
		using rightmost_one_t = bitwise_and_t<Bitset, bitwise_uminus_t<Bitset> >;

		// Returns the bitset of the i-th set bit in the given bitset (i >= 0).
		template<class Bitset, std::size_t Index>
		struct indirect_element_bitset;

		template<class Bitset, std::size_t Index>
		using indirect_element_bitset_t = typename indirect_element_bitset<Bitset, Index>::type;

		template<class Bitset, std::size_t Index>
		struct indirect_element_bitset {
			typedef indirect_element_bitset_t<bitwise_xor_t<Bitset, rightmost_one_t<Bitset> >, Index - 1> type;
		};

		template<class Bitset>
		struct indirect_element_bitset<Bitset, 0> {
			typedef rightmost_one_t<Bitset> type;
		};

		// Returns the indirect subset of a given bitset.
		template<class Bitset, default_bitset_t IndirectElements>
		struct indirect_subset;

		template<class Bitset, default_bitset_t IndirectElements>
		using indirect_subset_t = typename indirect_subset<Bitset, IndirectElements>::type;

		template<class Bitset, default_bitset_t IndirectElements>
		struct indirect_subset {
		private:

			constexpr static default_bitset_t current_indirect_element = rightmost_set_bit(IndirectElements);
			constexpr static default_integral_t current_indirect_element_index = ones(current_indirect_element - default_bitset_t(1));

			typedef indirect_element_bitset_t<Bitset, current_indirect_element_index> current_element;

		public:

			typedef bitwise_or_t<current_element, indirect_subset_t<Bitset, IndirectElements ^ current_indirect_element> > type;
		};

		template<class Bitset>
		struct indirect_subset<Bitset, default_bitset_t(0)> {
			typedef constant_bitset<default_bitset_t(0)> type;
		};

	}

}

#endif // __GA_CORE_EXPRESSION_TRAITS_HPP__
