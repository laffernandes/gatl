#ifndef __GA_GRADED_UMINUS_HPP__
#define __GA_GRADED_UMINUS_HPP__

namespace ga {

	namespace detail {

		struct _graded_unary_minus_element;
		struct _graded_unary_minus_end;
		
		template<class ItrType, class SignChangeIfGradeFunc>
		constexpr decltype(auto) graded_unary_minus(ItrType const &arg, SignChangeIfGradeFunc const &change) {
			return std::conditional<!is_end<ItrType>::value, _graded_unary_minus_element, _graded_unary_minus_end>::type::bind(arg, change);
		}

		struct _graded_unary_minus_element {
			template<class ItrType, class SignChangeIfGradeFunc>
			constexpr static decltype(auto) bind(ItrType const &arg, SignChangeIfGradeFunc const &change) {
				return insert(graded_unary_minus(next(arg), change), graded_unary_minus_element(arg.element(), change));
			}
		};

		struct _graded_unary_minus_end {
			template<class ItrType, class SignChangeIfGradeFunc>
			constexpr static empty_expression bind(ItrType const &, SignChangeIfGradeFunc const &) {
				return empty_expression();
			}
		};

	}

}

#endif // __GA_GRADED_UMINUS_HPP__
