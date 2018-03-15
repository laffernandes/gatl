#ifndef __GA_TAKE_GRADE_HPP__
#define __GA_TAKE_GRADE_HPP__

namespace ga {

	namespace detail {

		struct _keep_grade_if_grade;
		struct _keep_grade_end;

		template<class ItrType, class KeepIfGradeFunc>
		constexpr decltype(auto) keep_grade(ItrType const &arg, KeepIfGradeFunc const &keep) {
			return std::conditional<!is_end<ItrType>::value, _keep_grade_if_grade, _keep_grade_end>::type::bind(arg, keep);
		}

		struct _keep_grade_if_grade {
			template<class ItrType, class KeepIfGradeFunc>
			constexpr static decltype(auto) bind(ItrType const &arg, KeepIfGradeFunc const &keep) {
				return insert(keep_grade(next(arg), keep), keep_if_grade_element(arg.element(), keep));
			}
		};

		struct _keep_grade_end {
			template<class ItrType, class KeepIfGradeFunc>
			constexpr static empty_expression bind(ItrType const &, KeepIfGradeFunc const &) {
				return empty_expression();
			}
		};

	}

	template<class Type>
	constexpr decltype(auto) take_grade(Type const &arg, grade_t k) {
		return detail::keep_grade(detail::begin(arg), detail::keep_if_grade_func<grade_t>(k));
	}

	template<class Type, grade_t K>
	constexpr decltype(auto) take_grade(Type const &arg, detail::cvalue<K> const &k) {
		return detail::keep_grade(detail::begin(arg), detail::keep_if_grade_func<detail::cvalue<K> >());
	}

}

#endif // __GA_TAKE_GRADE_HPP__
