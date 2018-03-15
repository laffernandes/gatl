#ifndef __GA_LEFT_CONTRACTION_HPP__
#define __GA_LEFT_CONTRACTION_HPP__

namespace ga {

	namespace detail {

		class lcont_func {
		public:

			constexpr bool operator()(grade_t const lhs_grade, grade_t const rhs_grade, grade_t const result_grade) const {
				return (rhs_grade - lhs_grade) == result_grade;
			}

			template<grade_t LeftGrade, grade_t RightGrade, grade_t ResultGrade>
			struct eval {
				constexpr static bool value = (RightGrade - LeftGrade) == ResultGrade;
			};
		};

	}

	template<class LeftType, class RightType, class MetricType>
	constexpr decltype(auto) lcont(LeftType const &lhs, RightType const &rhs, metric<MetricType> const &mtr) {
		return detail::graded_product(detail::begin(lhs), detail::begin(rhs), mtr, detail::lcont_func());
	}

}

#endif // __GA_LEFT_CONTRACTION_HPP__
