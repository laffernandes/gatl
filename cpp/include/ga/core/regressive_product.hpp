#ifndef __GA_CORE_REGRESSIVE_PRODUCT_HPP__
#define __GA_CORE_REGRESSIVE_PRODUCT_HPP__

namespace ga {

	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType>
	constexpr decltype(auto) rp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) {
		auto lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(clifford_expression<default_integral_t, detail::product_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1>, detail::regressive_product_mapping<MetricSpaceType::vector_space_dimensions> > >());
	}

	template<typename LeftCoefficientType, typename LeftExpression, typename RightType, typename MetricSpaceType, typename = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) rp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &mtr) {
		return rp(lhs, scalar(rhs), mtr);
	}

	template<typename LeftType, typename RightCoefficientType, typename RightExpression, typename MetricSpaceType, typename = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) rp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
		return rp(scalar(lhs), rhs, mtr);
	}

	template<typename LeftType, typename RightType, typename MetricSpaceType, typename = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) rp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &mtr) {
		return rp(scalar(lhs), scalar(rhs), mtr);
	}

}

#endif // __GA_CORE_REGRESSIVE_PRODUCT_HPP__
