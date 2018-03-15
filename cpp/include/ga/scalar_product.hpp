#ifndef __GA_SCALAR_PRODUCT_HPP__
#define __GA_SCALAR_PRODUCT_HPP__

namespace ga {

	namespace detail {

		class scp_func {
		public:

			constexpr bool operator()(grade_t const lhs_grade, grade_t const rhs_grade, grade_t const result_grade) const {
				return result_grade == 0;
			}

			template<grade_t LeftGrade, grade_t RightGrade, grade_t ResultGrade>
			struct eval {
				constexpr static bool value = ResultGrade == 0;
			};
		};

	}

	template<class LeftType, class RightType, class MetricType>
	constexpr decltype(auto) scp(LeftType const &lhs, RightType const &rhs, metric<MetricType> const &mtr) {
		return detail::graded_product(detail::begin(lhs), detail::begin(rhs), mtr, detail::scp_func());
	}

}

#endif // __GA_SCALAR_PRODUCT_HPP__
