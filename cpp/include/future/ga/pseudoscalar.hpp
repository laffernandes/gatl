#ifndef __FUTURE_GA_PSEUDOSCALAR_HPP__
#define __FUTURE_GA_PSEUDOSCALAR_HPP__

namespace ga {

	template<class MetricSpaceType>
	constexpr decltype(auto) pseudoscalar(metric_space<MetricSpaceType> const &) {
		return clifford_expression<default_integral_t, detail::make_component_t<detail::constant<1>, detail::constant_basis_blade<MetricSpaceType::basis_vectors> > >();
	}

}

#endif // __FUTURE_GA_PSEUDOSCALAR_HPP__
