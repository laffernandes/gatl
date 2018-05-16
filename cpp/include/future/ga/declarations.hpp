#ifndef __FUTURE_GA_EXPRESSION_TRAITS_DECLARATION_HPP__
#define __FUTURE_GA_EXPRESSION_TRAITS_DECLARATION_HPP__

namespace ga {

	namespace detail {

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

		// Returns the possible grades of a given basis blade.
		template<class BasisBlade>
		struct possible_grades;

		template<class BasisBlade>
		constexpr default_bitset_t possible_grades_v = possible_grades<BasisBlade>::value;

	}

}

#endif // __FUTURE_GA_EXPRESSION_TRAITS_DECLARATION_HPP__
