#ifndef __GA_VERSOR_INVERSE_HPP__
#define __GA_VERSOR_INVERSE_HPP__

namespace ga {

	template<class Type, class MetricSpaceType>
	constexpr decltype(auto) inv(Type const &arg, metric_space<MetricSpaceType> const &) {
		return detail::div(detail::cvalue<1>(), arg);
	}

	template<class MetricSpaceType>
	constexpr decltype(auto) inv(detail::empty_expression const &, metric_space<MetricSpaceType> const &) = delete;

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType, class MetricSpaceType>
	constexpr decltype(auto) inv(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg, metric_space<MetricSpaceType> const &mtr) {
		return gp(reversion(arg), inv(rnorm_sqr(arg, mtr), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
	}

	template<class CoefficientType, class MetricSpaceType>
	constexpr decltype(auto) inv(detail::expression<detail::component<CoefficientType, detail::cbasis_blade<0> >, detail::empty_expression, detail::empty_expression> const &arg, metric_space<MetricSpaceType> const &) {
		return detail::div(detail::cvalue<1>(), native(arg));
	}

	template<class CoefficientType, class MetricSpaceType>
	constexpr decltype(auto) inv(detail::expression<detail::component<CoefficientType, detail::dbasis_blade<default_bitset_t(1)> >, detail::empty_expression, detail::empty_expression> const &arg, metric_space<MetricSpaceType> const &) {
		return detail::div(detail::cvalue<1>(), native(arg));
	}

	template<class CoefficientType, class MetricSpaceType>
	constexpr decltype(auto) inv(detail::expression<detail::components<CoefficientType, default_bitset_t(1)>, detail::empty_expression, detail::empty_expression> const &arg, metric_space<MetricSpaceType> const &) {
		return detail::div(detail::cvalue<1>(), native(arg));
	}

}

#endif // __GA_VERSOR_INVERSE_HPP__
