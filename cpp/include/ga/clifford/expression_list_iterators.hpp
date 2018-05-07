#ifndef __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__
#define __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class... ElementTypes>
			constexpr decltype(auto) begin(expression_list<ElementTypes...> &arg) {
				return arg;
			}

			template<class... ElementTypes>
			constexpr decltype(auto) begin(expression_list<ElementTypes...> const &arg) {
				return arg;
			}

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__
