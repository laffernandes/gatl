#ifndef __FUTURE_GA_SCALAR_PRODUCT_HPP__
#define __FUTURE_GA_SCALAR_PRODUCT_HPP__

namespace ga {

	namespace detail {

		struct scp_mapping {
		public:

			template<class LeftLazyGrade, class RightLazyGrade, class ResultLazyGrade>
			struct lazy_are_valid_grades {
				typedef lazy_eq_t<ResultLazyGrade, constant<0> > type;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimension>
			struct possible_grades_result {
				constexpr static default_bitset_t value = (LeftPossibleGrades & RightPossibleGrades) != default_bitset_t(0) ? default_bitset_t(1) : default_bitset_t(0);
			};
		};

	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class MetricSpaceType>
	constexpr decltype(auto) scp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
		typedef detail::lazy_arguments<LeftExpression, RightExpression> lazy;
		return detail::eval<detail::product_t<lazy::argument_expression_t<0>, lazy::argument_expression_t<1>, detail::bind_metric_space_mapping_t<MetricSpaceType, detail::scp_mapping> > >(lhs, rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression> > >
	constexpr decltype(auto) scp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		typedef detail::lazy_arguments<LeftExpression, RightExpression> lazy;
		return detail::eval<detail::product_t<lazy::argument_expression_t<0>, lazy::argument_expression_t<1>, detail::bind_metric_space_mapping_t<detail::real_metric_space, detail::scp_mapping> > >(lhs, rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class MetricSpaceType>
	constexpr decltype(auto) scp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return scp(lhs, scalar(rhs));
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType>
	constexpr decltype(auto) scp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return scp(lhs, scalar(rhs));
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class MetricSpaceType>
	constexpr decltype(auto) scp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) {
		return scp(scalar(lhs), rhs);
	}

	template<class LeftType, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) scp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return scp(scalar(lhs), rhs);
	}

	template<class LeftType, class RightType, class MetricSpaceType>
	constexpr decltype(auto) scp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return scp(scalar(lhs), scalar(rhs));
	}

	template<class LeftType, class RightType>
	constexpr decltype(auto) scp(LeftType const &lhs, RightType const &rhs) {
		return scp(scalar(lhs), scalar(rhs));
	}

}

#endif // __FUTURE_GA_SCALAR_PRODUCT_HPP__
