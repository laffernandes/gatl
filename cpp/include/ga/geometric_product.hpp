#ifndef __GA_GEOMETRIC_PRODUCT_HPP__
#define __GA_GEOMETRIC_PRODUCT_HPP__

namespace ga {

	namespace detail {

		class gp_func {
		public:

			constexpr bool operator()(grade_t const lhs_grade, grade_t const rhs_grade, grade_t const result_grade) const {
				return true;
			}

			template<grade_t LeftGrade, grade_t RightGrade, grade_t ResultGrade>
			struct eval {
				constexpr static bool value = true;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct maybe_eval {
				constexpr static bool value = true; //TODO Parei aqui!
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct possible_grades {
				constexpr static default_bitset_t value = ~default_bitset_t(0); //TODO Parei aqui!
			};
		};

	}

	template<class LeftType, class RightType, class MetricType>
	constexpr decltype(auto) gp(LeftType const &lhs, RightType const &rhs, metric<MetricType> const &mtr) {
		return detail::graded_product(detail::begin(lhs), detail::begin(rhs), mtr, detail::gp_func());
	}

}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType>
constexpr decltype(auto) operator*(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_t());
}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, ga::default_integral_t RightValue>
constexpr decltype(auto) operator*(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_t());
}

template<class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator*(ga::detail::empty_expression const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_t());
}

constexpr decltype(auto) operator*(ga::detail::empty_expression const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_t());
}

template<ga::default_integral_t RightValue>
constexpr decltype(auto) operator*(ga::detail::empty_expression const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_t());
}

template<ga::default_integral_t LeftValue, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator*(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_t());
}

template<ga::default_integral_t LeftValue>
constexpr decltype(auto) operator*(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_t());
}

template<ga::default_integral_t LeftValue, ga::default_integral_t RightValue>
constexpr decltype(auto) operator*(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_t());
}

#endif // __GA_GEOMETRIC_PRODUCT_HPP__
