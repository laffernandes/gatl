#ifndef __GA_CLIFFORD_TAKE_GRADE_HPP__
#define __GA_CLIFFORD_TAKE_GRADE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ElementType, class... OtherElementTypes, class KeepIfGradeFunc>
			constexpr decltype(auto) keep_grade(clifford_expression<ElementType, OtherElementTypes...> const &arg, KeepIfGradeFunc const &keep) {
				return insert(keep_grade(arg.next(), keep), keep_if_grade_element(arg.element(), keep));
			}

			template<class KeepIfGradeFunc>
			constexpr static decltype(auto) keep_grade(clifford_expression<> const &, KeepIfGradeFunc const &) {
				return clifford_expression<>();
			}

		}

		template<class Type>
		constexpr decltype(auto) take_grade(Type const &arg, grade_t k) {
			return detail::keep_grade(detail::begin(arg), detail::keep_if_grade_func<grade_t>(k));
		}

		template<class Type, grade_t K>
		constexpr decltype(auto) take_grade(Type const &arg, constant<K> const &k) {
			return detail::try_cast_to_native(detail::keep_grade(detail::begin(arg), detail::keep_if_grade_func<constant<K> >()));
		}

	}

}

#endif // __GA_CLIFFORD_TAKE_GRADE_HPP__
