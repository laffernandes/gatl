#ifndef __GA_PSEUDOSCALAR_HPP__
#define __GA_PSEUDOSCALAR_HPP__

namespace ga {

	template<class MetricSpaceType>
	constexpr decltype(auto) pseudoscalar(metric_space<MetricSpaceType> const &) {
		return clifford_expression<default_integral_t, detail::component_t<detail::constant_value<1>, detail::constant_basis_blade<MetricSpaceType::basis_vectors> > >();
	}

}

#endif // __GA_PSEUDOSCALAR_HPP__
