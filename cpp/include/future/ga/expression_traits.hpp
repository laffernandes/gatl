#ifndef __FUTURE_GA_EXPRESSION_TESTS_HPP__
#define __FUTURE_GA_EXPRESSION_TESTS_HPP__

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

		// Returns whether the given expression is a function with the given name.
		template<name_t Name, class Expression>
		struct is_function {
			constexpr static bool value = false;
		};

		template<name_t Name, class... Arguments>
		struct is_function<Name, function<Name, Arguments...> > {
			constexpr static bool value = true;
		};

		template<name_t Name, class Expression>
		constexpr bool is_function_v = is_function<Name, Expression>::value;

		// Specializations of possible_grades<BasisVectors>.
		template<default_bitset_t BasisVectors>
		struct possible_grades<constant_basis_blade<BasisVectors> > {
			constexpr static default_bitset_t value = default_bitset_t(1) << ones(BasisVectors);
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct possible_grades<dynamic_basis_blade<PossibleGrades, Bitset> > {
			constexpr static default_bitset_t value = PossibleGrades;
		};

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

		// Product operation.
		template<class LeftExpression, class RightExpression, class Mapping>
		struct _product;

		template<class LeftExpression, class RightExpression, class Mapping>
		using product_t = typename _product<LeftExpression, RightExpression, Mapping>::type;

		// Addition operation.
		template<class LeftExpression, class RightExpression>
		struct _addition;

		template<class LeftExpression, class RightExpression>
		using addition_t = typename _addition<LeftExpression, RightExpression>::type;

	}

}

#endif // __FUTURE_GA_EXPRESSION_TESTS_HPP__
