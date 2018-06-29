#ifndef __GA_EXTRA_COMMUTATOR_PRODUCT_HPP__
#define __GA_EXTRA_COMMUTATOR_PRODUCT_HPP__

namespace ga {

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class MetricSpaceType>
	constexpr decltype(auto) cp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
		auto lazy = make_lazy_context(lhs, rhs);
		return lazy.eval((gp(lazy.argument<0>(), lazy.argument<1>()) - gp(lazy.argument<1>(), lazy.argument<0>())) / c<2>);
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) cp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return cp(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) cp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return cp(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) cp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return cp(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) cp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return cp(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) cp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return cp(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) cp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) {
		return cp(scalar(lhs), rhs, detail::real_metric_space());
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) cp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return cp(scalar(lhs), rhs, detail::real_metric_space());
	}

	template<class LeftType, class RightType, class MetricSpaceType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) cp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return cp(scalar(lhs), scalar(rhs), detail::real_metric_space());
	}

	template<class LeftType, class RightType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) cp(LeftType const &lhs, RightType const &rhs) {
		return cp(scalar(lhs), scalar(rhs), detail::real_metric_space());
	}

}

#endif // __GA_EXTRA_COMMUTATOR_PRODUCT_HPP__
