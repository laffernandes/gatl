#ifndef __GA_CORE_SCALAR_PRODUCT_HPP__
#define __GA_CORE_SCALAR_PRODUCT_HPP__

namespace ga {

	namespace detail {

		struct sp_mapping {
		public:

			template<typename LeftGrade, typename RightGrade, typename ResultGrade>
			struct are_valid_grades {
				typedef equal_t<ResultGrade, constant_value<0> > type;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimensions>
			struct possible_grades_result {
				constexpr static default_bitset_t value = (LeftPossibleGrades & RightPossibleGrades) != default_bitset_t(0) ? default_bitset_t(1) : default_bitset_t(0);
			};
		};

	}

	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType>
	constexpr decltype(auto) sp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
		auto lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(clifford_expression<default_integral_t, detail::product_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1>, detail::metric_space_mapping_t<MetricSpaceType, detail::sp_mapping> > >());
	}

	template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightExpression>
	constexpr decltype(auto) sp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return sp(lhs, rhs, detail::real_metric_space());
	}

	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightCoefficient>
	constexpr decltype(auto) sp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return sp(lhs, rhs, detail::real_metric_space());
	}

	template<typename LeftCoefficientType, typename LeftCoefficient, typename RightCoefficientType, typename RightCoefficient>
	constexpr decltype(auto) sp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return sp(lhs, rhs, detail::real_metric_space());
	}

	template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename MetricSpaceType, typename = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) sp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return sp(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) sp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return sp(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType, typename = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) sp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) {
		return sp(scalar(lhs), rhs, detail::real_metric_space());
	}

	template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) sp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return sp(scalar(lhs), rhs, detail::real_metric_space());
	}

	template<typename LeftType, typename RightType, typename MetricSpaceType, typename = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) sp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return sp(scalar(lhs), scalar(rhs), detail::real_metric_space());
	}

	template<typename LeftType, typename RightType, typename = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) sp(LeftType const &lhs, RightType const &rhs) {
		return sp(scalar(lhs), scalar(rhs), detail::real_metric_space());
	}

}

#endif // __GA_CORE_SCALAR_PRODUCT_HPP__
