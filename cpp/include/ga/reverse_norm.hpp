#ifndef __GA_REVERSE_NORM_HPP__
#define __GA_REVERSE_NORM_HPP__

namespace ga {

	template<class Type, class MetricType>
	constexpr decltype(auto) rnorm_sqr(Type const &arg, metric<MetricType> const &mtr) {
		return scp(arg, reversion(arg), mtr);
	}

	template<class Type, class MetricType>
	constexpr decltype(auto) rnorm(Type const &arg, metric<MetricType> const &mtr) {
		return sqrt(rnorm_sqr(arg, mtr));
	}

}

#endif // __GA_REVERSE_NORM_HPP__
