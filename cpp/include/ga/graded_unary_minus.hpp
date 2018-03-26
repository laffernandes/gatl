#ifndef __GA_GRADED_UMINUS_HPP__
#define __GA_GRADED_UMINUS_HPP__

namespace ga {

	namespace detail {

		template<class ItrType, class SignChangeIfGradeFunc>
		constexpr decltype(auto) graded_unary_minus(ItrType const &arg, SignChangeIfGradeFunc const &change) {
			return insert(graded_unary_minus(next(arg), change), graded_unary_minus_element(arg.element(), change));
		}

		template<class SignChangeIfGradeFunc>
		constexpr static empty_expression graded_unary_minus(itr_end const &, SignChangeIfGradeFunc const &) {
			return empty_expression();
		}

	}

}

#endif // __GA_GRADED_UMINUS_HPP__
