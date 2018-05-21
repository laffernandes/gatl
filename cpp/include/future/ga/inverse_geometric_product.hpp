#ifndef __FUTURE_GA_INVERSE_GEOMETRIC_PRODUCT_HPP__
#define __FUTURE_GA_INVERSE_GEOMETRIC_PRODUCT_HPP__

namespace ga {

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class MetricSpaceType>
	constexpr decltype(auto) igp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(gp(lazy.argument<0>(), inv(lazy.argument<1>(), mtr), mtr));
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<detail::is_scalar_expression_v<RightExpression> > >
	constexpr decltype(auto) igp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		auto const lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(gp(lazy.argument<0>(), inv(lazy.argument<1>())));
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) igp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return igp(lhs, scalar(rhs));
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) igp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return igp(lhs, scalar(rhs));
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) igp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
		return igp(scalar(lhs), rhs, mtr);
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) igp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return igp(scalar(lhs), rhs);
	}

	template<class LeftType, class RightType, class MetricSpaceType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) igp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return igp(scalar(lhs), scalar(rhs));
	}

	template<class LeftType, class RightType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) igp(LeftType const &lhs, RightType const &rhs) {
		return igp(scalar(lhs), scalar(rhs));
	}

}

#endif // __FUTURE_GA_INVERSE_GEOMETRIC_PRODUCT_HPP__
