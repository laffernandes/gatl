#ifndef __GA_VERSOR_INVERSE_HPP__
#define __GA_VERSOR_INVERSE_HPP__

namespace ga {

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType, class MetricType>
	constexpr decltype(auto) inv(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg, metric<MetricType> const &mtr) {
		return gp(reversion(arg), inv(rnorm_sqr(arg, mtr), euclidean_metric_t()), euclidean_metric_t());
	}

	template<class CoefficientType, class MetricType>
	constexpr decltype(auto) inv(detail::expression<detail::component<CoefficientType, detail::cbasis_blade<0> >, detail::empty_expression, detail::empty_expression> const &arg, metric<MetricType> const &) {
		return detail::div(detail::cvalue<1>(), arg.element().coefficient());
	}

	template<class CoefficientType, class MetricType>
	constexpr decltype(auto) inv(detail::expression<detail::component<CoefficientType, detail::dbasis_blade<default_bitset_t(1)> >, detail::empty_expression, detail::empty_expression> const &arg, metric<MetricType> const &) {
		return detail::div(detail::cvalue<1>(), arg.element().coefficient());
	}

	template<class CoefficientType, class MetricType>
	constexpr decltype(auto) inv(detail::expression<detail::components<CoefficientType, default_bitset_t(1)>, detail::empty_expression, detail::empty_expression> const &arg, metric<MetricType> const &) {
		return detail::div(detail::cvalue<1>(), arg.element().begin()->second);
	}

	template<class Type, class MetricType>
	constexpr decltype(auto) inv(Type const &arg, metric<MetricType> const &) {
		return detail::div(detail::cvalue<1>(), arg);
	}

	template<class MetricType>
	constexpr decltype(auto) inv(detail::empty_expression const &, metric<MetricType> const &) = delete;

}

#endif // __GA_VERSOR_INVERSE_HPP__
