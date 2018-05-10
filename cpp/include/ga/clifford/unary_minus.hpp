#ifndef __GA_CLIFFORD_UNARY_MINUS_HPP__
#define __GA_CLIFFORD_UNARY_MINUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) unary_minus(clifford_expression<ElementType, OtherElementTypes...> const &arg) {
				return insert(unary_minus(arg.next()), unary_minus_element(arg.element()));
			}

			//TODO INSERIDO POR CAUSA DE BUG PÓS ATUALIZAÇÃO DO VISUAL STUDIO
			template<class ElementType>
			constexpr decltype(auto) unary_minus(clifford_expression<ElementType> const &arg) {
				return make_simple_clifford_expression(unary_minus_element(arg.element()));
			}

			constexpr decltype(auto) unary_minus(clifford_expression<> const &) {
				return clifford_expression<>();
			}

		}

		using lazy::operator-;

		template<class... RightElementTypes>
		constexpr decltype(auto) operator-(clifford_expression<RightElementTypes...> const &rhs) {
			return detail::unary_minus(rhs);
		}

	}

}

#endif // __GA_CLIFFORD_UNARY_MINUS_HPP__
