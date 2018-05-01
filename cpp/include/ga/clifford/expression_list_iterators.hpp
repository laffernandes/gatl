#ifndef __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__
#define __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ElementType, class NextListType>
			constexpr decltype(auto) begin(expression_list<ElementType, NextListType> &root) {
				return make_oitr(&root, begin(root.next()));
			}

			template<class ElementType, class NextListType>
			struct _onext<expression_list<ElementType, NextListType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(oitr<expression_list<ElementType, NextListType>, TailType> const &curr) {
					return curr.tail();
				}
			};

			template<class ElementType, class NextListType>
			constexpr decltype(auto) begin(expression_list<ElementType, NextListType> const &root) {
				return make_coitr(&root, begin(root.next()));
			}

			template<class ElementType, class NextListType>
			struct _conext<expression_list<ElementType, NextListType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(coitr<expression_list<ElementType, NextListType>, TailType> const &curr) {
					return curr.tail();
				}
			};

			template<class ElementType, class NextListType>
			constexpr decltype(auto) obegin(expression_list<ElementType, NextListType> &root) {
				return begin(root);
			}

			template<class ElementType, class NextListType>
			constexpr decltype(auto) obegin(expression_list<ElementType, NextListType> const &root) {
				return begin(root);
			}

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__
