#ifndef __GA_FUTURE_EXPRESSION_TRAITS_DECLARATION_HPP__
#define __GA_FUTURE_EXPRESSION_TRAITS_DECLARATION_HPP__

namespace future {

	namespace detail {

		// Relational operator for Id's.
		template<id_t... LeftId>
		struct id_cmp;

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
		template<class LeftType, class RightType, class Enable = void>
		struct addition;

		template<class LeftType, class RightType>
		using addition_t = typename addition<LeftType, RightType>::type;

		// Product operation.
		template<class LeftType, class RightType, class Mapping, class Enable = void>
		struct product;

		template<class LeftType, class RightType, class Mapping>
		using product_t = typename product<LeftType, RightType, Mapping>::type;

		// Exponentiation operation.
		template<class LeftType, class RightType, class Enable = void>
		struct exponentiation;

		template<class LeftType, class RightType>
		using exponentiation_t = typename exponentiation<LeftType, RightType>::type;

		// Make component function.
		template<class Coefficient, class BasisBlade, class Enable = void>
		struct make_component;

		template<class Coefficient, class BasisBlade>
		using make_component_t = typename make_component<Coefficient, BasisBlade>::type;

		// Possible grades of a given component.
		template<class Component>
		struct possible_grades;

		template<class Component>
		constexpr default_bitset_t possible_grades_v = possible_grades<Component>::value;

		// Returns whether the given expression is compile-time defined.
		template<class Type>
		struct is_constant_expression;

		template<class Type>
		constexpr bool is_constant_expression_v = is_constant_expression<Type>::value;

	}

}

#endif // __GA_FUTURE_EXPRESSION_TRAITS_DECLARATION_HPP__
