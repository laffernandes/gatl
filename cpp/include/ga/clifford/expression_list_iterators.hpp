#ifndef __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__
#define __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) begin(expression_list<ElementType, OtherElementTypes...> &arg) {
				return &arg;
			}

			constexpr decltype(auto) begin(expression_list<> &) {
				return itr_end();
			}

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) next(expression_list<ElementType, OtherElementTypes...> *curr) {
				return &curr->next();
			}

			template<class ElementType>
			constexpr decltype(auto) next(expression_list<ElementType> *) {
				return itr_end();
			}

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) element(expression_list<ElementType, OtherElementTypes...> *curr) {
				return curr->element();
			}

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) begin(expression_list<ElementType, OtherElementTypes...> const &arg) {
				return &arg;
			}

			constexpr decltype(auto) begin(expression_list<> const &) {
				return itr_end();
			}

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) next(expression_list<ElementType, OtherElementTypes...> const *curr) {
				return &curr->next();
			}

			template<class ElementType>
			constexpr decltype(auto) next(expression_list<ElementType> const *) {
				return itr_end();
			}

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) element(expression_list<ElementType, OtherElementTypes...> const *curr) {
				return curr->element();
			}

			template<class... ElementTypes>
			constexpr decltype(auto) obegin(expression_list<ElementTypes...> &arg) {
				return begin(arg);
			}

			template<class... ElementTypes>
			constexpr decltype(auto) obegin(expression_list<ElementTypes...> const &arg) {
				return begin(arg);
			}

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__
