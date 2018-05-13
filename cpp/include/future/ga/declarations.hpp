#ifndef __FUTURE_GA_EXPRESSION_TRAITS_DECLARATION_HPP__
#define __FUTURE_GA_EXPRESSION_TRAITS_DECLARATION_HPP__

namespace ga {

	namespace detail {

		// Relational operators.
		template<class LeftType, class RightType>
		struct lt;

		template<class LeftType, class RightType>
		constexpr bool lt_v = lt<LeftType, RightType>::value;

		template<class LeftType, class RightType>
		struct le;

		template<class LeftType, class RightType>
		constexpr bool le_v = le<LeftType, RightType>::value;

		template<class LeftType, class RightType>
		struct eq;

		template<class LeftType, class RightType>
		constexpr bool eq_v = eq<LeftType, RightType>::value;

		template<class LeftType, class RightType>
		struct ne;

		template<class LeftType, class RightType>
		constexpr bool ne_v = ne<LeftType, RightType>::value;

		template<class LeftType, class RightType>
		struct gt;

		template<class LeftType, class RightType>
		constexpr bool gt_v = gt<LeftType, RightType>::value;

		template<class LeftType, class RightType>
		struct ge;

		template<class LeftType, class RightType>
		constexpr bool ge_v = ge<LeftType, RightType>::value;

		// Addition operation.
		template<class LeftExpression, class RightExpression, class Enable = void>
		struct addition;

		template<class LeftExpression, class RightExpression>
		using addition_t = typename addition<LeftExpression, RightExpression>::type;

		// Product operation.
		template<class LeftExpression, class RightExpression, class Mapping, class Enable = void>
		struct product;

		template<class LeftExpression, class RightExpression, class Mapping>
		using product_t = typename product<LeftExpression, RightExpression, Mapping>::type;

		// Exponentiation operation.
		template<class LeftExpression, class RightExpression, class Enable = void>
		struct exponentiation;

		template<class LeftExpression, class RightExpression>
		using exponentiation_t = typename exponentiation<LeftExpression, RightExpression>::type;

		// Make component function.
		template<class Coefficient, class BasisBlade, class Enable = void>
		struct make_component;

		template<class Coefficient, class BasisBlade>
		using make_component_t = typename make_component<Coefficient, BasisBlade>::type;

		// Returns whether the given expression is compile-time defined.
		template<class Expression>
		struct is_constant_expression;

		template<class Expression>
		constexpr bool is_constant_expression_v = is_constant_expression<Expression>::value;

		// Returns whether the given expression is scalar.
		template<class Expression>
		struct is_scalar_expression;

		template<class Expression>
		constexpr bool is_scalar_expression_v = is_scalar_expression<Expression>::value;

		// Returns the possible grades of a given basis blade.
		template<class BasisBlade>
		struct possible_grades;

		template<class BasisBlade>
		constexpr default_bitset_t possible_grades_v = possible_grades<BasisBlade>::value;

	}

}

#endif // __FUTURE_GA_EXPRESSION_TRAITS_DECLARATION_HPP__
