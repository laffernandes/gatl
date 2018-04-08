#ifndef __GA_CLIFFORD_UNARY_PLUS_HPP__
#define __GA_CLIFFORD_UNARY_PLUS_HPP__

namespace ga {

	namespace clifford {

		template<class ValueType>
		constexpr ValueType uplus(ValueType const &rhs) {
			return rhs;
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> uplus(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) {
			return rhs;
		}

		constexpr detail::empty_expression_tree uplus(detail::empty_expression_tree const &) {
			return detail::empty_expression_tree();
		}

		using lazy::operator+;

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> operator+(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) {
			return rhs;
		}

		constexpr detail::empty_expression_tree operator+(detail::empty_expression_tree const &) {
			return detail::empty_expression_tree();
		}

	}

}

#endif // __GA_CLIFFORD_UNARY_PLUS_HPP__
