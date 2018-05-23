#ifndef __FUTURE_GA_SCALAR_PRODUCT_HPP__
#define __FUTURE_GA_SCALAR_PRODUCT_HPP__

namespace ga {

	namespace detail {

		struct scp_mapping {
		public:

			template<class LeftGrade, class RightGrade, class ResultGrade>
			struct are_valid_grades {
				typedef equal_t<ResultGrade, constant_value<0> > type;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimension>
			struct possible_grades_result {
				constexpr static default_bitset_t value = (LeftPossibleGrades & RightPossibleGrades) != default_bitset_t(0) ? default_bitset_t(1) : default_bitset_t(0);
			};
		};

	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class MetricSpaceType>
	constexpr decltype(auto) scp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
		auto lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(clifford_expression<std::common_type_t<LeftCoefficientType, RightCoefficientType>, detail::product_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1>, detail::metric_space_mapping_t<MetricSpaceType, detail::scp_mapping> > >());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression> > >
	constexpr decltype(auto) scp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		auto lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(clifford_expression<std::common_type_t<LeftCoefficientType, RightCoefficientType>, detail::product_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1>, detail::metric_space_mapping_t<detail::real_metric_space, detail::scp_mapping> > >());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) scp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return scp(lhs, scalar(rhs));
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) scp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return scp(lhs, scalar(rhs));
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) scp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) {
		return scp(scalar(lhs), rhs);
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) scp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return scp(scalar(lhs), rhs);
	}

	template<class LeftType, class RightType, class MetricSpaceType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) scp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return scp(scalar(lhs), scalar(rhs));
	}

	template<class LeftType, class RightType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) scp(LeftType const &lhs, RightType const &rhs) {
		return scp(scalar(lhs), scalar(rhs));
	}

}

#endif // __FUTURE_GA_SCALAR_PRODUCT_HPP__
