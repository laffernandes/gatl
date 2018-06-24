#ifndef __GA_CORE_ARITHMETIC_OPERATORS_HPP__
#define __GA_CORE_ARITHMETIC_OPERATORS_HPP__

namespace ga {

	template<class RightCoefficientType, class RightExpression>
	constexpr clifford_expression<RightCoefficientType, RightExpression> operator+(clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return rhs;
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator+(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		auto lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(clifford_expression<default_integral_t, detail::addition_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1> > >());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType>
	constexpr decltype(auto) operator+(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return lhs + scalar(rhs);
	}

	template<class LeftType, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator+(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return scalar(lhs) + rhs;
	}

	template<class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator-(clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return gp(c<-1>, rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator-(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		auto const lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(lazy.argument<0>() + gp(c<-1>, lazy.argument<1>()));
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType>
	constexpr decltype(auto) operator-(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return lhs - scalar(rhs);
	}

	template<class LeftType, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator-(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return scalar(lhs) - rhs;
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator*(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return gp(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) operator*(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return gp(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) operator*(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return gp(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) operator*(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return gp(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) operator*(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return gp(scalar(lhs), rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator^(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return op(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) operator^(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return op(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) operator^(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return op(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) operator^(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return op(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) operator^(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return op(scalar(lhs), rhs, detail::real_metric_space());
	}

}

#endif // __GA_CORE_ARITHMETIC_OPERATORS_HPP__
