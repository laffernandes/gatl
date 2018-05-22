#ifndef __FUTURE_GA_EXPRESSION_TESTS_HPP__
#define __FUTURE_GA_EXPRESSION_TESTS_HPP__

namespace ga {

	namespace detail {

		// Returns whether the given expressions are compile-time defined.
		template<class... Expressions>
		struct is_constant_expression;

		template<class... Expressions>
		constexpr bool is_constant_expression_v = is_constant_expression<Expressions...>::value;

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

		// Returns whether the given expression is scalar.
		template<class Expression>
		struct is_scalar_expression {
			constexpr static bool value = false; // default
		};

		template<class Coefficient>
		struct is_scalar_expression<component<Coefficient, constant_basis_blade<default_bitset_t(0)> > > {
			constexpr static bool value = true;
		};

		template<class Expression>
		constexpr bool is_scalar_expression_v = is_scalar_expression<Expression>::value;

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

		// Returns the possible grades of a given basis blade.
		template<class BasisBlade>
		struct possible_grades;

		template<default_bitset_t BasisVectors>
		struct possible_grades<constant_basis_blade<BasisVectors> > {
			constexpr static default_bitset_t value = default_bitset_t(1) << ones(BasisVectors);
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct possible_grades<dynamic_basis_blade<PossibleGrades, Bitset> > {
			constexpr static default_bitset_t value = PossibleGrades;
		};

		template<class BasisBlade>
		constexpr default_bitset_t possible_grades_v = possible_grades<BasisBlade>::value;

		// Returns the coefficient of a given component.
		template<class Component>
		struct coefficient;

		template<class Coefficient, class BasisBlade>
		struct coefficient<component<Coefficient, BasisBlade> > {
			typedef Coefficient type;
		};

		template<class Component>
		using coefficient_t = typename coefficient<Component>::type;

		// Returns the basis blade of a given component.
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
