#ifndef __GA_OUTER_PRODUCT_HPP__
#define __GA_OUTER_PRODUCT_HPP__

namespace ga {

	namespace detail {

		class op_func {
		private:

			struct _iterate_end {
				constexpr static default_bitset_t value = default_bitset_t(0);
			};

			template<grade_t LeftGrade, default_bitset_t RightPossibleGrades, grade_t RightGrade>
			struct _iterate_right {
				constexpr static default_bitset_t value = _iterate_right<
						LeftGrade,
						((LeftGrade + RightGrade + 1) < std::numeric_limits<default_bitset_t>::digits ? (RightPossibleGrades >> 1) : default_bitset_t(0)),
						RightGrade + 1
					>::value | ((RightPossibleGrades & default_bitset_t(1)) != default_bitset_t(0) ? (default_bitset_t(1) << (LeftGrade + RightGrade)) : default_bitset_t(0));
			};

			template<grade_t LeftGrade, grade_t RightGrade>
			struct _iterate_right<LeftGrade, 0, RightGrade> : _iterate_end {
			};

			template<default_bitset_t LeftPossibleGrades, grade_t LeftGrade, default_bitset_t RightPossibleGrades>
			struct _iterate_left {
				constexpr static default_bitset_t value = _iterate_left<(LeftPossibleGrades >> 1), LeftGrade + 1, RightPossibleGrades>::value | std::conditional<(LeftPossibleGrades & default_bitset_t(1)) != default_bitset_t(0), _iterate_right<LeftGrade, RightPossibleGrades, 0>, _iterate_end>::type::value;
			};

			template<grade_t LeftGrade, default_bitset_t RightPossibleGrades>
			struct _iterate_left<0, LeftGrade, RightPossibleGrades> : _iterate_end {
			};

		public:

			constexpr bool operator()(grade_t const lhs_grade, grade_t const rhs_grade, grade_t const result_grade) const {
				return (lhs_grade + rhs_grade) == result_grade;
			}

			template<grade_t LeftGrade, grade_t RightGrade, grade_t ResultGrade>
			struct eval {
				constexpr static bool value = (LeftGrade + RightGrade) == ResultGrade;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct possible_grades : _iterate_left<LeftPossibleGrades, 0, RightPossibleGrades> {
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct maybe_eval {
				constexpr static bool value = possible_grades<LeftPossibleGrades, RightPossibleGrades>::value != default_bitset_t(0);
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
