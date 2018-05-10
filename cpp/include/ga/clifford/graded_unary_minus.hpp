#ifndef __GA_CLIFFORD_GRADED_UMINUS_HPP__
#define __GA_CLIFFORD_GRADED_UMINUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ElementType, class... OtherElementTypes, class SignChangeIfGradeFunc>
			constexpr decltype(auto) graded_unary_minus(clifford_expression<ElementType, OtherElementTypes...> const &arg, SignChangeIfGradeFunc const &change) {
				return insert(graded_unary_minus(arg.next(), change), graded_unary_minus_element(arg.element(), change));
			}

			template<class SignChangeIfGradeFunc>
			constexpr static decltype(auto) graded_unary_minus(clifford_expression<> const &, SignChangeIfGradeFunc const &) {
				return clifford_expression<>();
			}

		}

	}

}

#endif // __GA_CLIFFORD_GRADED_UMINUS_HPP__
