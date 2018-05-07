#ifndef __GA_CLIFFORD_UNARY_MINUS_HPP__
#define __GA_CLIFFORD_UNARY_MINUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) unary_minus(expression_list<ElementType, OtherElementTypes...> const &arg) {
				return insert(unary_minus(arg.next()), unary_minus_element(arg.element()));
			}

			constexpr decltype(auto) unary_minus(expression_list<> const &) {
				return make_empty_clifford_expression();
			}

		}

		using lazy::operator-;

		template<class RightExpressionType>
		constexpr decltype(auto) operator-(clifford_expression<RightExpressionType> const &rhs) {
			return detail::unary_minus(detail::begin(rhs()));
		}

	}

}

#endif // __GA_CLIFFORD_UNARY_MINUS_HPP__
