#ifndef __GA_CORE_RIGHT_CONTRACTION_HPP__
#define __GA_CORE_RIGHT_CONTRACTION_HPP__

namespace ga {

	namespace detail {

		struct rcont_mapping {
		private:

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct _possible_grades_result {
			private:

				constexpr static default_bitset_t right_grade_bitset = rightmost_set_bit(RightPossibleGrades);
				constexpr static default_bitset_t possible_grades = LeftPossibleGrades / right_grade_bitset;

			public:

				constexpr static default_bitset_t value = _possible_grades_result<LeftPossibleGrades, (possible_grades != default_bitset_t(0) ? RightPossibleGrades ^ right_grade_bitset : default_bitset_t(0))>::value | possible_grades;
			};

			template<default_bitset_t LeftPossibleGrades>
			struct _possible_grades_result<LeftPossibleGrades, default_bitset_t(0)> {
				constexpr static default_bitset_t value = default_bitset_t(0);
			};

		public:

			template<class LeftGrade, class RightGrade, class ResultGrade>
			struct are_valid_grades {
				typedef equal_t<addition_t<LeftGrade, product_t<constant_value<-1>, RightGrade, value_mapping> >, ResultGrade> type;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimensions>
			struct possible_grades_result : _possible_grades_result<LeftPossibleGrades, RightPossibleGrades> {
			};
		};

	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class MetricSpaceType>
	constexpr decltype(auto) rcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
		auto lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(clifford_expression<default_integral_t, detail::product_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1>, detail::metric_space_mapping_t<MetricSpaceType, detail::rcont_mapping> > >());
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) rcont(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return rcont(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) rcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return rcont(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) rcont(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return rcont(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) rcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return rcont(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) rcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return rcont(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) rcont(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) {
		return rcont(scalar(lhs), rhs, detail::real_metric_space());
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) rcont(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return rcont(scalar(lhs), rhs, detail::real_metric_space());
	}

	template<class LeftType, class RightType, class MetricSpaceType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) rcont(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return rcont(scalar(lhs), scalar(rhs), detail::real_metric_space());
	}

	template<class LeftType, class RightType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) rcont(LeftType const &lhs, RightType const &rhs) {
		return rcont(scalar(lhs), scalar(rhs), detail::real_metric_space());
	}

}

#endif // __GA_CORE_RIGHT_CONTRACTION_HPP__
