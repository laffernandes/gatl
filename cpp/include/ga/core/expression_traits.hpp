#ifndef __GA_CORE_EXPRESSION_TRAITS_HPP__
#define __GA_CORE_EXPRESSION_TRAITS_HPP__

namespace ga {

	namespace detail {

		// Returns whether the given expressions can be stored if necessary.
		template<class Expression>
		struct can_be_stored :
			std::false_type { // default
		};

		template<class Expression>
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

		template<default_bitset_t Bitset>
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

		template<default_bitset_t Bitset>
		struct can_be_stored<constant_basis_blade<Bitset> > :
			std::true_type {
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct can_be_stored<dynamic_basis_blade<PossibleGrades, Bitset> > :
			std::bool_constant<can_be_stored_v<Bitset> > {
		};

		template<class Coefficient, class BasisBlade>
		struct can_be_stored<component<Coefficient, BasisBlade> > :
			std::bool_constant<can_be_stored_v<Coefficient> && can_be_stored_v<BasisBlade> > {
		};

		template<name_t Name, class... Arguments>
		struct can_be_stored<function<Name, Arguments...> > :
			std::conjunction<std::bool_constant<can_be_stored_v<Arguments> >...>::type {
		};

		// Specializations of is_constant_expression<Expression>.
		template<class Expression>
		struct is_constant_expression :
			std::false_type { // default
		};

		template<default_integral_t Value>
		struct is_constant_expression<constant_value<Value> > :
			std::true_type {
		};

		template<default_bitset_t Bitset>
		struct is_constant_expression<constant_bitset<Bitset> > :
			std::true_type {
		};

		template<default_bitset_t Bitset>
		struct is_constant_expression<constant_basis_blade<Bitset> > :
			std::true_type {
		};

		template<class Coefficient, class BasisBlade>
		struct is_constant_expression<component<Coefficient, BasisBlade> > :
			std::bool_constant<is_constant_expression_v<Coefficient> && is_constant_expression_v<BasisBlade> > {
		};

		template<name_t Name, class... Arguments>
		struct is_constant_expression<function<Name, Arguments...> > :
			std::conjunction<std::bool_constant<is_constant_expression_v<Arguments> >...>::type {
		};

		// Returns whether the given expression is a scalar component.
		template<class Expression>
		struct is_scalar_component :
			std::false_type {
		};

		template<class Coefficient>
		struct is_scalar_component<component<Coefficient, constant_basis_blade<default_bitset_t(0)> > > :
			std::true_type {
		};

		template<class Expression>
		constexpr bool is_scalar_component_v = is_scalar_component<Expression>::value;

		// Specializations of has_stored_entries<Expression>.
		template<class Expression>
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

		template<default_bitset_t PossibleGrades, class Bitset>
		struct has_stored_entries<dynamic_basis_blade<PossibleGrades, Bitset> > :
			std::bool_constant<has_stored_entries_v<Bitset> > {
		};

		template<class Coefficient, class BasisBlade>
		struct has_stored_entries<component<Coefficient, BasisBlade> > :
			std::bool_constant<(has_stored_entries_v<Coefficient> || has_stored_entries_v<BasisBlade>)> {
		};

		template<name_t Name, class... Arguments>
		struct has_stored_entries<function<Name, Arguments...> > :
			std::disjunction<std::bool_constant<has_stored_entries_v<Arguments> >...>::type {
		};

		// Returns whether the given expression is an even value for sure.
		template<class Expression>
		struct is_even;

		template<class Expression>
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

		template<class LeftBitset, class RightBitset>
		struct is_even<reordering_sign<LeftBitset, RightBitset> > :
			std::false_type {
		};

		template<class Bitset>
		struct is_even<count_one_bits<Bitset> > :
			std::false_type {
		};

		template<class Bitset>
		struct is_even<bitwise_uminus<Bitset> > :
			std::bool_constant<is_even_v<Bitset> > {
		};

		template<class Bitset>
		struct is_even<bitwise_dec<Bitset> > :
			std::bool_constant<!is_even_v<Bitset> > {
		};

		template<class LeftType, class RightType>
		struct is_even<bitwise_and<LeftType, RightType> > :
			std::bool_constant<is_even_v<LeftType> && is_even_v<RightType> > {
		};

		template<class LeftType, class RightType>
		struct is_even<bitwise_or<LeftType, RightType> > :
			std::bool_constant<is_even_v<LeftType> || is_even_v<RightType> > {
		};

		template<class LeftType, class RightType>
		struct is_even<bitwise_xor<LeftType, RightType> > :
			std::false_type {
		};

		template<class Test, class TrueValue, class FalseValue>
		struct is_even<if_else<Test, TrueValue, FalseValue> > :
			std::bool_constant<is_even_v<TrueValue> && is_even_v<FalseValue> > {
		};

		template<class Value>
		struct is_even<absolute<Value> > :
			std::bool_constant<is_even_v<Value> > {
		};

		template<class Value>
		struct is_even<exponential<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_even<logarithm<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_even<cosine<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_even<sine<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_even<tangent<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_even<hyperbolic_cosine<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_even<hyperbolic_sine<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_even<hyperbolic_tangent<Value> > :
			std::false_type {
		};

		template<class LeftArgument, class RightArgument>
		struct is_even<power<LeftArgument, RightArgument> > :
			std::bool_constant<is_even_v<RightArgument> > {
		};

		template<class... Arguments>
		struct is_even<mul<Arguments...> > :
			std::false_type {
		};

		template<class... Arguments>
		struct is_even<add<Arguments...> > :
			std::false_type {
		};

		// Specializations of is_function<Expression>.
		template<name_t Name, class Expression>
		struct is_function :
			std::false_type {
		};

		template<name_t Name, class... Arguments>
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

		template<class LeftBitset, class RightBitset>
		struct is_non_negative<reordering_sign<LeftBitset, RightBitset> > :
			std::true_type {
		};

		template<class Bitset>
		struct is_non_negative<count_one_bits<Bitset> > :
			std::true_type {
		};

		template<class Bitset>
		struct is_non_negative<bitwise_uminus<Bitset> > :
			std::true_type {
		};

		template<class Bitset>
		struct is_non_negative<bitwise_dec<Bitset> > :
			std::true_type {
		};

		template<class LeftType, class RightType>
		struct is_non_negative<bitwise_and<LeftType, RightType> > :
			std::true_type {
		};

		template<class LeftType, class RightType>
		struct is_non_negative<bitwise_or<LeftType, RightType> > :
			std::true_type {
		};

		template<class LeftType, class RightType>
		struct is_non_negative<bitwise_xor<LeftType, RightType> > :
			std::true_type {
		};

		template<class Test, class TrueValue, class FalseValue>
		struct is_non_negative<if_else<Test, TrueValue, FalseValue> > :
			std::bool_constant<is_non_negative_v<TrueValue> && is_non_negative_v<FalseValue> > {
		};

		template<class Value>
		struct is_non_negative<absolute<Value> > :
			std::true_type {
		};

		template<class Value>
		struct is_non_negative<exponential<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_non_negative<logarithm<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_non_negative<cosine<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_non_negative<sine<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_non_negative<tangent<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_non_negative<hyperbolic_cosine<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_non_negative<hyperbolic_sine<Value> > :
			std::false_type {
		};

		template<class Value>
		struct is_non_negative<hyperbolic_tangent<Value> > :
			std::false_type {
		};

		template<class LeftArgument, class RightArgument>
		struct is_non_negative<power<LeftArgument, RightArgument> > :
			std::bool_constant<is_non_negative_v<LeftArgument> || is_even_v<RightArgument> > {
		};

		template<class... Arguments>
		struct is_non_negative<mul<Arguments...> > :
			std::conjunction<std::bool_constant<is_non_negative_v<Arguments> >...>::type {
		};

		template<class... Arguments>
		struct is_non_negative<add<Arguments...> > :
			std::false_type {
		};

		// Returns if the given expression may be positive.
		template<class Expression>
		struct may_be_positive;

		template<class Expression>
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

		template<class LeftBitset, class RightBitset>
		struct may_be_positive<reordering_sign<LeftBitset, RightBitset> > :
			std::true_type {
		};

		template<class Bitset>
		struct may_be_positive<count_one_bits<Bitset> > :
			std::true_type {
		};

		template<class Bitset>
		struct may_be_positive<bitwise_uminus<Bitset> > :
			std::true_type {
		};

		template<class Bitset>
		struct may_be_positive<bitwise_dec<Bitset> > :
			std::true_type {
		};

		template<class LeftType, class RightType>
		struct may_be_positive<bitwise_and<LeftType, RightType> > :
			std::true_type {
		};

		template<class LeftType, class RightType>
		struct may_be_positive<bitwise_or<LeftType, RightType> > :
			std::true_type {
		};

		template<class LeftType, class RightType>
		struct may_be_positive<bitwise_xor<LeftType, RightType> > :
			std::true_type {
		};

		template<class Test, class TrueValue, class FalseValue>
		struct may_be_positive<if_else<Test, TrueValue, FalseValue> > :
			std::bool_constant<may_be_positive_v<TrueValue> && may_be_positive_v<FalseValue> > {
		};

		template<class Value>
		struct may_be_positive<absolute<Value> > :
			std::true_type {
		};

		template<class Value>
		struct may_be_positive<cosine<Value> > :
			std::true_type {
		};

		template<class Value>
		struct may_be_positive<sine<Value> > :
			std::true_type {
		};

		template<class Value>
		struct may_be_positive<tangent<Value> > :
			std::true_type {
		};

		template<class Value>
		struct may_be_positive<hyperbolic_cosine<Value> > :
			std::true_type {
		};

		template<class Value>
		struct may_be_positive<hyperbolic_sine<Value> > :
			std::true_type {
		};

		template<class Value>
		struct may_be_positive<hyperbolic_tangent<Value> > :
			std::true_type {
		};

		template<class LeftArgument, class RightArgument>
		struct may_be_positive<power<LeftArgument, RightArgument> > :
			std::bool_constant<may_be_positive_v<LeftArgument> || is_even_v<RightArgument> > {
		};

		template<class... Arguments>
		struct may_be_positive<mul<Arguments...> > :
			std::conjunction<std::bool_constant<may_be_positive_v<Arguments> >...>::type {
		};

		template<class... Arguments>
		struct may_be_positive<add<Arguments...> > :
			std::true_type {
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

			typedef indirect_element_bitset_t<Bitset, set_bit_index(current_indirect_element)> current_element;

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
