#ifndef __GA_CLIFFORD_GRADED_UMINUS_HPP__
#define __GA_CLIFFORD_GRADED_UMINUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ItrType, class SignChangeIfGradeFunc>
			constexpr decltype(auto) graded_unary_minus(ItrType const &arg, SignChangeIfGradeFunc const &change) {
				return insert(graded_unary_minus(next(arg), change), graded_unary_minus_element(element(arg), change));
			}

			template<class SignChangeIfGradeFunc>
			constexpr static decltype(auto) graded_unary_minus(itr_end const &, SignChangeIfGradeFunc const &) {
				return make_empty_clifford_expression();
			}

		}

	}

}

#endif // __GA_CLIFFORD_GRADED_UMINUS_HPP__
