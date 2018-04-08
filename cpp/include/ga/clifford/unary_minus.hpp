#ifndef __GA_CLIFFORD_UNARY_MINUS_HPP__
#define __GA_CLIFFORD_UNARY_MINUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			struct _unary_minus_neg;
			struct _unary_minus_end;

			template<class ItrType>
			constexpr decltype(auto) unary_minus(ItrType const &arg) {
				return insert(unary_minus(next(arg)), unary_minus_element(arg.element()));
			}

			constexpr empty_expression_tree unary_minus(itr_end const &) {
				return empty_expression_tree();
			}

		}

		template<class RightType>
		constexpr decltype(auto) uminus(RightType const &rhs) {
			return detail::unary_minus(detail::begin(rhs));
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) uminus(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) {
			return detail::unary_minus(detail::begin(rhs));
		}

		constexpr detail::empty_expression_tree uminus(detail::empty_expression_tree const &) {
			return detail::empty_expression_tree();
		}

		using lazy::operator-;

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) operator-(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) {
			return uminus(rhs);
		}

		constexpr detail::empty_expression_tree operator-(detail::empty_expression_tree const &) {
			return detail::empty_expression_tree();
		}

	}

}

#endif // __GA_CLIFFORD_UNARY_MINUS_HPP__
