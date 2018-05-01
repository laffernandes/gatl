#ifndef __GA_CLIFFORD_EXPRESSION_LIST_INSERT_HPP__
#define __GA_CLIFFORD_EXPRESSION_LIST_INSERT_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			struct _insert_element_next {
				template<class ExpressionType, class ElementType>
				constexpr static decltype(auto) bind(ExpressionType const &curr, ElementType const &element) {
					return make_expression_list(curr.element(), insert(curr.next(), element));
				}
			};

			struct _insert_element_here {
				template<class ExpressionType, class ElementType>
				constexpr static decltype(auto) bind(ExpressionType const &curr, ElementType const &element) {
					return make_expression_list(element, curr);
				}
			};

			template<class CurrentElementType, class NextListType, class ElementType>
			struct _insert<expression_list<CurrentElementType, NextListType>, ElementType> : std::conditional<
				lt<CurrentElementType, ElementType>::value,
				_insert_element_next,
				_insert_element_here
			>::type {
			};

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_LIST_INSERT_HPP__
