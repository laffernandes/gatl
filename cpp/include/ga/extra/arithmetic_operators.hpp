#ifndef __GA_EXTRA_ARITHMETIC_OPERATORS_HPP__
#define __GA_EXTRA_ARITHMETIC_OPERATORS_HPP__

namespace ga {

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) operator/(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return igp(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) operator/(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return igp(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<class LeftType, class RightCoefficientType, class RightCoefficient, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) operator/(LeftType const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return igp(scalar(lhs), rhs, detail::real_metric_space());
	}


}

#endif // __GA_EXTRA_ARITHMETIC_OPERATORS_HPP__
