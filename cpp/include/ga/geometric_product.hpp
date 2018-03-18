#ifndef __GA_GEOMETRIC_PRODUCT_HPP__
#define __GA_GEOMETRIC_PRODUCT_HPP__

namespace ga {

	namespace detail {

		class gp_func {
		private:

			struct _iterate_end {
				constexpr static default_bitset_t value = default_bitset_t(0);
			};

			template<grade_t LeftGrade, default_bitset_t RightPossibleGrades, grade_t RightGrade>
			struct _iterate_right {
			private:

				constexpr static grade_t min_grade = LeftGrade <= RightGrade ? (RightGrade - LeftGrade) : (LeftGrade - RightGrade);
				constexpr static grade_t max_grade = (LeftGrade + RightGrade) < std::numeric_limits<default_bitset_t>::digits ? (LeftGrade + RightGrade) : (std::numeric_limits<default_bitset_t>::digits - 1);

			public:

				constexpr static default_bitset_t value = _iterate_right<
						LeftGrade,
						(RightPossibleGrades >> 1),
						RightGrade + 1
					>::value | ((RightPossibleGrades & default_bitset_t(1)) != default_bitset_t(0) ? (((default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - max_grade - 1)) >> min_grade) << min_grade) : default_bitset_t(0));
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
				return true;
			}

			template<grade_t LeftGrade, grade_t RightGrade, grade_t ResultGrade>
			struct eval {
				constexpr static bool value = true;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct possible_grades : _iterate_left<LeftPossibleGrades, 0, RightPossibleGrades> {
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct maybe_eval {
				constexpr static bool value = true;
			};
		};

	}

	template<class LeftType, class RightType, class MetricType>
	constexpr decltype(auto) gp(LeftType const &lhs, RightType const &rhs, metric<MetricType> const &mtr) {
		return detail::graded_product(detail::begin(lhs), detail::begin(rhs), mtr, detail::gp_func());
	}

}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator*(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	static_assert(ga::detail::is_scalar_expression<ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> >::value || ga::detail::is_scalar_expression<ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> >::value, "At least one of the arguments must be a scalar value.");
	return ga::gp(lhs, rhs, ga::euclidean_metric_t());
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
