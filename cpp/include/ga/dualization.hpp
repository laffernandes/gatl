#ifndef __GA_DUALIZATION_HPP__
#define __GA_DUALIZATION_HPP__

namespace ga {

	template<class Type, class PseudoscalarType, class MetricType>
	constexpr decltype(auto) dual(Type const &arg, PseudoscalarType const &pseudoscalar, metric<MetricType> const &mtr) {
		return gp(arg, inv(pseudoscalar, mtr), mtr);
	}

	template<class Type, class PseudoscalarType, class MetricType>
	constexpr decltype(auto) undual(Type const &arg, PseudoscalarType const &pseudoscalar, metric<MetricType> const &mtr) {
		return gp(arg, pseudoscalar, mtr);
	}

}

#endif // __GA_DUALIZATION_HPP__
