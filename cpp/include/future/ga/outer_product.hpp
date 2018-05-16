#ifndef __FUTURE_GA_OUTER_PRODUCT_HPP__
#define __FUTURE_GA_OUTER_PRODUCT_HPP__

namespace ga {

	namespace detail {

		struct op_mapping {
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

			template<class LeftLazyGrade, class RightLazyGrade, class ResultLazyGrade>
			struct lazy_are_valid_grades {
				typedef lazy_eq_t<lazy_plus_t<LeftLazyGrade, RightLazyGrade>, ResultLazyGrade> type;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimension>
			struct possible_grades_result {
				constexpr static default_bitset_t value = _iterate_left<LeftPossibleGrades, 0, RightPossibleGrades>::value & (default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (VectorSpaceDimension + 1)));
			};
		};

	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class MetricSpaceType>
	constexpr decltype(auto) op(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
		typedef detail::lazy_arguments<LeftExpression, RightExpression> lazy;
		return detail::eval<detail::product_t<lazy::argument_expression_t<0>, lazy::argument_expression_t<1>, detail::metric_space_mapping_t<MetricSpaceType, detail::op_mapping> > >(lhs, rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression> > >
	constexpr decltype(auto) op(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		typedef detail::lazy_arguments<LeftExpression, RightExpression> lazy;
		return detail::eval<detail::product_t<lazy::argument_expression_t<0>, lazy::argument_expression_t<1>, detail::metric_space_mapping_t<detail::real_metric_space, detail::op_mapping> > >(lhs, rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class MetricSpaceType>
	constexpr decltype(auto) op(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return op(lhs, scalar(rhs));
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType>
	constexpr decltype(auto) op(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return op(lhs, scalar(rhs));
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class MetricSpaceType>
	constexpr decltype(auto) op(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) {
		return op(scalar(lhs), rhs);
	}

	template<class LeftType, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) op(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return op(scalar(lhs), rhs);
	}

	template<class LeftType, class RightType, class MetricSpaceType>
	constexpr decltype(auto) op(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return op(scalar(lhs), scalar(rhs));
	}

	template<class LeftType, class RightType>
	constexpr decltype(auto) op(LeftType const &lhs, RightType const &rhs) {
		return op(scalar(lhs), scalar(rhs));
	}

}

#endif // __FUTURE_GA_OUTER_PRODUCT_HPP__