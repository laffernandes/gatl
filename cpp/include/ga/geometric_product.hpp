#ifndef __GA_GEOMETRIC_PRODUCT_HPP__
#define __GA_GEOMETRIC_PRODUCT_HPP__

namespace ga {

	namespace detail {

		class gp_func final {
		private:

			struct _iterate_end {
				constexpr static default_bitset_t value = default_bitset_t(0);
			};

			template<grade_t LeftGrade, default_bitset_t RightPossibleGrades, grade_t RightGrade>
			struct _iterate_right {
			private:

				constexpr static default_bitset_t pattern = (default_bitset_t)0x5555555555555555ull;

				constexpr static grade_t min_grade = LeftGrade <= RightGrade ? (RightGrade - LeftGrade) : (LeftGrade - RightGrade);
				constexpr static grade_t max_grade = (LeftGrade + RightGrade) < std::numeric_limits<default_bitset_t>::digits ? (LeftGrade + RightGrade) : (std::numeric_limits<default_bitset_t>::digits - 1);

			public:

				constexpr static default_bitset_t value = _iterate_right<
						LeftGrade,
						(RightPossibleGrades >> 1),
						RightGrade + 1
					>::value | ((RightPossibleGrades & default_bitset_t(1)) != default_bitset_t(0) ? ((((default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - max_grade - 1)) >> min_grade) & pattern) << min_grade) : default_bitset_t(0));
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

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimension>
			struct possible_grades {
				constexpr static default_bitset_t value = _iterate_left<LeftPossibleGrades, 0, RightPossibleGrades>::value & (default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (VectorSpaceDimension + 1)));
			};
		};

	}

	template<class LeftType, class RightType, class MetricSpaceType>
	constexpr decltype(auto) gp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &mtr) {
		return detail::graded_product(detail::begin(lhs), detail::begin(rhs), mtr, detail::gp_func());
	}

}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType, typename std::enable_if<ga::detail::may_cast_to_native<ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> >::value || ga::detail::may_cast_to_native<ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> >::value, int>::type = 0>
constexpr decltype(auto) operator*(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType>
constexpr decltype(auto) operator*(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, ga::default_integral_t RightValue>
constexpr decltype(auto) operator*(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator*(ga::detail::empty_expression const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

constexpr decltype(auto) operator*(ga::detail::empty_expression const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<ga::default_integral_t RightValue>
constexpr decltype(auto) operator*(ga::detail::empty_expression const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<ga::default_integral_t LeftValue, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator*(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<ga::default_integral_t LeftValue>
constexpr decltype(auto) operator*(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<ga::default_integral_t LeftValue, ga::default_integral_t RightValue>
constexpr decltype(auto) operator*(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

#endif // __GA_GEOMETRIC_PRODUCT_HPP__
