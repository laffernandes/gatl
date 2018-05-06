#ifndef __GA_CLIFFORD_EXPRESSION_LIST_INSERT_HPP__
#define __GA_CLIFFORD_EXPRESSION_LIST_INSERT_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			struct _insert_element_next {
				template<class ElementType, class... OtherElementTypes, class NewElementType>
				constexpr static decltype(auto) bind(expression_list<ElementType, OtherElementTypes...> const &expression, NewElementType const &element) {
					return expression_list<ElementType, NewElementType, OtherElementTypes...>(expression.element(), insert(expression.next(), element));
				}
			};

			struct _insert_element_here {
				template<class ElementType, class... OtherElementTypes, class NewElementType>
				constexpr static decltype(auto) bind(expression_list<ElementType, OtherElementTypes...> const &expression, NewElementType const &element) {
					return expression_list<NewElementType, ElementType, OtherElementTypes...>(element, expression);
				}
			};

			template<class ElementType, class... OtherElementTypes, class NewElementType>
			struct _insert<expression_list<ElementType, OtherElementTypes...>, NewElementType> : std::conditional<
				lt<ElementType, NewElementType>::value,
				_insert_element_next,
				_insert_element_here
			>::type {
			};

			template<class NewElementType>
			struct _insert<expression_list<>, NewElementType> {
				constexpr static decltype(auto) bind(expression_list<> const &, NewElementType const &element) {
					return make_simple_clifford_expression(element);
				}
			};

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_LIST_INSERT_HPP__
