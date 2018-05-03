#ifndef __GA_CLIFFORD_TAKE_GRADE_HPP__
#define __GA_CLIFFORD_TAKE_GRADE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ItrType, class KeepIfGradeFunc>
			constexpr decltype(auto) keep_grade(ItrType const &arg, KeepIfGradeFunc const &keep) {
				return insert(keep_grade(next(arg), keep), keep_if_grade_element(arg.element(), keep));
			}

			template<class KeepIfGradeFunc>
			constexpr static empty_clifford_expression keep_grade(itr_end const &, KeepIfGradeFunc const &) {
				return empty_clifford_expression();
			}

		}

		template<class Type>
		constexpr decltype(auto) take_grade(Type const &arg, grade_t k) {
			return detail::keep_grade(detail::begin(arg), detail::keep_if_grade_func<grade_t>(k));
		}

		template<class Type, grade_t K>
		constexpr decltype(auto) take_grade(Type const &arg, constant<K> const &k) {
			return detail::try_to_cast_to_native(detail::keep_grade(detail::begin(arg), detail::keep_if_grade_func<constant<K> >()));
		}

	}

}

#endif // __GA_CLIFFORD_TAKE_GRADE_HPP__
