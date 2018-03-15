#ifndef __GA_RIGHT_CONTRACTION_HPP__
#define __GA_RIGHT_CONTRACTION_HPP__

namespace ga {

	namespace detail {

		class rcont_func {
		public:

			constexpr bool operator()(grade_t const lhs_grade, grade_t const rhs_grade, grade_t const result_grade) const {
				return (lhs_grade - rhs_grade) == result_grade;
			}

			template<grade_t LeftGrade, grade_t RightGrade, grade_t ResultGrade>
			struct eval {
				constexpr static bool value = (LeftGrade - RightGrade) == ResultGrade;
			};
		};

	}

	template<class LeftType, class RightType, class MetricType>
	constexpr decltype(auto) rcont(LeftType const &lhs, RightType const &rhs, metric<MetricType> const &mtr) {
		return detail::graded_product(detail::begin(lhs), detail::begin(rhs), mtr, detail::rcont_func());
	}

}

#endif // __GA_RIGHT_CONTRACTION_HPP__
