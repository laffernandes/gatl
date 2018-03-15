#ifndef __GA_OUTER_PRODUCT_HPP__
#define __GA_OUTER_PRODUCT_HPP__

namespace ga {

	namespace detail {

		class op_func {
		public:

			constexpr bool operator()(grade_t const lhs_grade, grade_t const rhs_grade, grade_t const result_grade) const {
				return (lhs_grade + rhs_grade) == result_grade;
			}

			template<grade_t LeftGrade, grade_t RightGrade, grade_t ResultGrade>
			struct eval {
				constexpr static bool value = (LeftGrade + RightGrade) == ResultGrade;
			};
		};

	}

	template<class LeftType, class RightType>
	constexpr decltype(auto) op(LeftType const &lhs, RightType const &rhs) {
		return detail::graded_product(detail::begin(lhs), detail::begin(rhs), euclidean_metric_t(), detail::op_func());
	}

}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator^(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::op(lhs, rhs);
}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType>
constexpr decltype(auto) operator^(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::op(lhs, rhs);
}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, ga::default_integral_t RightValue>
constexpr decltype(auto) operator^(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::op(lhs, rhs);
}

template<class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator^(ga::detail::empty_expression const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::op(lhs, rhs);
}

constexpr decltype(auto) operator^(ga::detail::empty_expression const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::op(lhs, rhs);
}

template<ga::default_integral_t RightValue>
constexpr decltype(auto) operator^(ga::detail::empty_expression const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::op(lhs, rhs);
}

template<ga::default_integral_t LeftValue, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator^(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::op(lhs, rhs);
}

template<ga::default_integral_t LeftValue>
constexpr decltype(auto) operator^(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::op(lhs, rhs);
}

template<ga::default_integral_t LeftValue, ga::default_integral_t RightValue>
constexpr decltype(auto) operator^(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::op(lhs, rhs);
}

#endif // __GA_OUTER_PRODUCT_HPP__
